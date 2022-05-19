/*
 * com.c
 *
 *  Created on: 17. maj 2022
 *      Author: Tobia
 */
#include "com.h"
#include "FreeRTOS.h"
#include "stream_buffer.h"
#include "task.h"
#include "tm4c123gh6pm.h"
#include <stdbool.h>

#define PIN_COM 4
#define PIN_COM_0 0b00010000 // PC4 (tiva)
#define PIN_COM_1 0b00100000 // PC5 (tiva)
// bits types
#define COM_SIGNAL 0b11
#define COM_FLAT 0b00
#define COM_ONE 0b10
#define COM_ZERO 0b01
// Modes
#define COM_IDLE 0
#define COM_WRITE 1
#define COM_READ 2
#define COM_RESPOND 3
#define COM_DENY 4

#define COM_SPEED 20

bool signal_flag = false;

void com_init (void) {

  //  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2;
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC; // Enable the clock to the port by
										// setting the appropriate bits
  vTaskDelay (10 / portTICK_RATE_MS);
  GPIO_PORTC_DIR_R &= ~(PIN_COM_0 | PIN_COM_1); // A write a 1 = output and a
												// write of a 0 = input.
  GPIO_PORTC_DEN_R |= (PIN_COM_0 | PIN_COM_1);	// The digital functions for the
											   // corresponding pin are enabled.
  GPIO_PORTC_PDR_R |= (PIN_COM_0 | PIN_COM_1); // Enable Pull down on the pins.
  GPIO_PORTC_AFSEL_R &= ~(PIN_COM_0 | PIN_COM_1);
  GPIO_PORTC_DATA_R = 0;
}

void com_send_signal (void) {
  signal_flag = !signal_flag;
  if (signal_flag)
	GPIO_PORTC_DIR_R |= (PIN_COM_0 | PIN_COM_1);

  GPIO_PORTC_DATA_R |= (PIN_COM_0 | PIN_COM_1);
  vTaskDelay (COM_SPEED / portTICK_RATE_MS);
  GPIO_PORTC_DATA_R &= ~(PIN_COM_0 | PIN_COM_1);
  vTaskDelay (COM_SPEED / portTICK_RATE_MS);

  if (!signal_flag)
	GPIO_PORTC_DIR_R &= ~(PIN_COM_0 | PIN_COM_1);
}

uint8_t com_get_data (void) {
  switch (GPIO_PORTC_DATA_R & (PIN_COM_0 | PIN_COM_1)) {
	case (PIN_COM_0 | PIN_COM_1):
	  // uart0_println("SIGNAL");
	  vTaskDelay (1);
	  return COM_SIGNAL;
	case PIN_COM_0:
	  vTaskDelay (1);
	  // uart0_print("0");
	  return COM_ZERO;
	case PIN_COM_1:
	  vTaskDelay (1);
	  // uart0_print("1");
	  return COM_ONE;
	default:
	  vTaskDelay (1);
	  // uart0_println("FLAT");
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

void com_get_string (char *str) {

  char	  temp = 0;
  uint8_t i	   = 8;
  uint8_t max  = 0;
  uint8_t next = 0;

  while (next != COM_SIGNAL) {

	if (next == COM_ONE) {
	  temp |= (1 << --i);
	  GPIO_PORTD_DATA_R |= 0x40;
	} else if (next == COM_ZERO) {
	  i--;
	  GPIO_PORTD_DATA_R &= ~0x40;
	}
	if (i == 0) {
	  i	   = 8;
	  *str = temp;
	  str++;
	  max++;

	  temp = 0;
	}

	com_wait_for_next ( );
	next = com_get_data ( );
  }

  *str = '\0';

  uart0_println (str);
  return;
}

void com_send_bit (bool bit, bool passthrough) {
  if (!passthrough)
	com_send_signal ( );

  if (bit)
	GPIO_PORTC_DATA_R |= PIN_COM_1;
  else
	GPIO_PORTC_DATA_R |= PIN_COM_0;
  vTaskDelay (COM_SPEED / portTICK_RATE_MS);
  GPIO_PORTC_DATA_R = ~(PIN_COM_1 | PIN_COM_0);
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

void com_send_string (const char *str, bool passthrough) {
  if (!passthrough)
	com_send_signal ( );
  do
	com_send_char (*str, true);
  while (str++ && *str != '\0');
  if (!passthrough)
	com_send_signal ( );
}

void com_get_string_better (char *str) {
  uint8_t i = 8;
  com_wait_for_signal ( );

  while (1) {
	com_wait_for_next ( );
	uint8_t next = com_get_data ( );

	if (i == 0) {
	  i = 8;
	  str++;
	}

	switch (next) {
	  case COM_ZERO:
		vTaskDelay (5 / portTICK_RATE_MS);
		i--;
		*str &= ~(1 << (i));
		break;
	  case COM_ONE:
		vTaskDelay (5 / portTICK_RATE_MS);
		i--;
		*str |= (1 << (i));
		break;
	  case COM_SIGNAL:
		return;
	}
  }
}

void com_get_message (char *str) {
  // make srt[x] before funktion in "main"
  com_get_string_better (str);
  uart0_print ("Got message: ");
  uart0_println (str);
  vTaskDelay (10 * COM_SPEED / portTICK_RATE_MS);
}

void com_send_message (char *str) {
  com_send_string (str, false);
  uart0_print ("Sending message: ");
  uart0_println (str);
}

void com_echo_message (char *str) {
  com_get_message (str);
  com_send_message (str);
}

void com_task (void *pvParameters) {
  com_init ( );
  // Variables
  uint8_t  com_mode = COM_IDLE;
  uint8_t  raw_data[5];
  uint8_t  sensor_i = 0, data_i = 0, avg_i = 0;
  uint16_t data_block[10] = {0};
  // StreamBufferHandle_t com_buff = xStreamBufferGenericCreate(8, 1, pdFALSE);

  while (1) {
	//        switch (com_mode)
	//        {
	//        case COM_IDLE:
	//            GPIO_PORTD_DATA_R |= 0x40;
	//            com_wait_for_signal();
	//            com_mode = COM_READ;
	//            uart0_println("Got start signal");
	//            break;
	//
	//        case COM_RESPOND:
	//            com_send_string("OK!", false);
	//            vTaskDelay(2000 / portTICK_RATE_MS);
	//            com_mode = COM_IDLE;
	//            break;
	//
	//        case COM_DENY:
	//            com_send_string("UH?", false);
	//            vTaskDelay(2000 / portTICK_RATE_MS);
	//            com_mode = COM_IDLE;
	//            break;
	//
	//        case COM_READ:
	//        {
	//            char str[8] = {0};
	//            com_get_message(str);
	//            do
	//            {
	//                raw_data[sensor_i++] = (uint8_t) (*str - '0');
	//                str++;
	//
	//            }
	//            while (*str != "\0");
	//
	//            uint16_t sensor_data = 0;
	//            for (sensor_i; sensor_i > 0; sensor_i--)
	//            {
	//                sensor_data += raw_data[sensor_i] * pow(10, 4 - sensor_i);
	//            }
	//
	//            data_block[data_i++] = sensor_data;
	//            data_i %= 10;
	//
	//            uint16_t avg_output = 0;
	//            for (avg_i = 0; avg_i < 10; avg_i++)
	//            {
	//                avg_output += data_block[avg_i];
	//            }
	//            avg_output = avg_output / 10;
	//            uart0_print("The avg of the last 10 reading is: ")
	//            uart0_printnum16(avg_output);
	//            uart0_println(" ")
	//
	//            com_mode = COM_IDLE;
	//        }
	//            //else xStreamBufferSend(com_buff, &str, 1, 10);
	//        }
	char str[8] = {0};
	com_get_message (str);

	vTaskDelay (20 / portTICK_RATE_MS);
  }
}
