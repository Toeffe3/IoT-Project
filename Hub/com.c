/******************************************************************************/
/* Project:    Hub                                                            */
/* File:       com.c                                                          */
/* Decription: Hub communication file                                         */
/******************************************************************************/

/***************************** Include files *******************************/
#include "com.h"
#include "uart0.h"

/*****************************   Variables   *******************************/
bool signal_flag = false;

/*****************************   Functions   *******************************/
void com_init (void) {
  // SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2;
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB; // Enable the clock to the port by
										// setting the appropriate bits
  vTaskDelay (10 / portTICK_RATE_MS);
  GPIO_PORTB_DIR_R &= ~(PIN_COM_0 | PIN_COM_1); // A write a 1 = output and a
												// write of a 0 = input.
  GPIO_PORTB_DEN_R |= (PIN_COM_0 | PIN_COM_1);	// The digital functions for the
											   // corresponding pin are enabled.
  GPIO_PORTB_PDR_R |= (PIN_COM_0 | PIN_COM_1); // Enable Pull down on the pins.
  GPIO_PORTB_AFSEL_R &= ~(PIN_COM_0 | PIN_COM_1);
  GPIO_PORTB_DATA_R = 0;
}

void com_send_signal (void) {
  signal_flag = !signal_flag;
  if (signal_flag)
	GPIO_PORTB_DIR_R |= (PIN_COM_0 | PIN_COM_1);

  GPIO_PORTB_DATA_R |= (PIN_COM_0 | PIN_COM_1);
  vTaskDelay (COM_SPEED / portTICK_RATE_MS);
  GPIO_PORTB_DATA_R &= ~(PIN_COM_0 | PIN_COM_1);
  vTaskDelay (COM_SPEED / portTICK_RATE_MS);

  if (!signal_flag)
	GPIO_PORTB_DIR_R &= ~(PIN_COM_0 | PIN_COM_1);
}

uint8_t com_get_data (void) {
  switch (GPIO_PORTB_DATA_R & (PIN_COM_0 | PIN_COM_1)) {
	case (PIN_COM_1 | PIN_COM_0):
	  vTaskDelay (COM_SPEED / 10 / portTICK_RATE_MS);
	  return COM_SIGNAL;
	case PIN_COM_0:
	  vTaskDelay (COM_SPEED / 10 / portTICK_RATE_MS);
	  return COM_ZERO;
	case PIN_COM_1:
	  vTaskDelay (COM_SPEED / 10 / portTICK_RATE_MS);
	  return COM_ONE;
	default:
	  vTaskDelay (COM_SPEED / 10 / portTICK_RATE_MS);
	  return COM_FLAT;
  }
}

void com_wait_for_next ( ) {
  while (com_get_data ( ) != COM_FLAT)
	;
  while (com_get_data ( ) == COM_FLAT)
	;
}

void com_wait_for_signal ( ) {
  while (com_get_data ( ) == COM_SIGNAL)
	;
  while (com_get_data ( ) == COM_FLAT)
	;
}

bool com_check_for_signal ( ) {
  if (com_get_data ( ) == COM_SIGNAL)
	return true;
  else
	return false;
}

size_t com_get_string (char* str) {

  uint8_t i	   = 8;
  uint8_t next = 0;
  size_t  sz   = 0;

  do {

	com_wait_for_next ( );
	next = com_get_data ( );

	if (next == COM_ONE) {
	  *str |= (1 << --i);
	  GPIO_PORTD_DATA_R |= 0x40;
	} else if (next == COM_ZERO) {
	  *str &= ~(1 << --i);
	  GPIO_PORTD_DATA_R &= ~0x40;
	}
	if (i == 0) {
	  i = 8;
	  str++;
	  sz++;
	}

  } while (next != COM_SIGNAL);

  str++;
  *str = '\0';

  return sz++;
}

void com_send_bit (bool bit, bool passthrough) {
  if (!passthrough)
	com_send_signal ( );

  if (bit)
	GPIO_PORTB_DATA_R |= PIN_COM_1;
  else
	GPIO_PORTB_DATA_R |= PIN_COM_0;
  vTaskDelay (COM_SPEED / portTICK_RATE_MS);
  GPIO_PORTB_DATA_R = ~(PIN_COM_1 | PIN_COM_0);
  vTaskDelay (COM_SPEED / portTICK_RATE_MS);

  if (!passthrough)
	com_send_signal ( );
}

void com_send_char (char c, bool passthrough) {
  if (!passthrough)
	com_send_signal ( );
  uint8_t i;
  for (i = 8; i > 0; i--)
	com_send_bit (c & (1 << (i - 1)), true);
  if (!passthrough)
	com_send_signal ( );
}

void com_send_string (const char* str, bool passthrough) {
  if (!passthrough)
	com_send_signal ( );
  do
	com_send_char (*str, true);
  while (str++ && *str != '\0');
  if (!passthrough)
	com_send_signal ( );
}

size_t com_write_buffer (const char* data) {
  return xStreamBufferSend (com_out, data, strlen (data), 0);
}

void com_task (void* pvParameters) {
  com_init ( );

  uint8_t com_mode = COM_IDLE;
  com_in		   = xStreamBufferGenericCreate (32, 1, pdFALSE);
  com_out		   = xStreamBufferGenericCreate (32, 1, pdFALSE);
  size_t len	   = 0;
  char	 str[32];
  device_type = SENSOR_UNKNOWN;

  while (1) {
	char data[32];

	switch (com_mode) {
	  case COM_IDLE: {
		if (xStreamBufferReceive (com_out, &data, 1, 250) == pdPASS)
		  str[len++] = *data;
		else if (len > 0)
		  com_mode = COM_WRITE;
		vTaskDelay (COM_SPEED / portTICK_RATE_MS);
		break;
	  }

	  case COM_WRITE: {
		uart0_print ("COM_WRITE: ");
		uart0_println (str);
		com_send_string (str, false);
		while (len-- > 0)
		  str[len] = '\0';

		com_mode = COM_WAIT_FOR_RESPONSE;
		break;
	  }

	  case COM_WAIT_FOR_RESPONSE: {
		com_wait_for_signal ( );
		uart0_print ("COM_READ: ");
		char tmp[32] = {'\0'};
		len			 = com_get_string (tmp);
		uart0_println (tmp);
		xStreamBufferReset (com_in);
		xStreamBufferSend (com_in, &tmp, len, 250);
		vTaskDelay (COM_SPEED * 10 / portTICK_RATE_MS);
		com_mode = COM_IDLE;
		len		 = 0;
		break;
	  }
	}
	vTaskDelay (1 / portTICK_RATE_MS);
  }
}
