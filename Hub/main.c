/**
 * main.c
 */
#include <stdint.h>
//
#include "FreeRTOS.h"
#include "tm4c123gh6pm.h"
//
#include "stream_buffer.h"
#include "systick_frt.h"
#include "task.h"
//
#include "com.h"
#include "lcd.h"
#include "status_led.h"
#include "uart0.h"

#define USERTASK_STACK_SIZE configMINIMAL_STACK_SIZE

//@formatter:off
char sensor_text[5][16] = {{"Unknown sensor  "},
						   {"Light value:    "},
						   {"IR detector:    "},
						   {"Color intensity:"},
						   {"Sound level:    "}};
//@formatter:on

bool init_mode = false;

void controller_task (void* pvParameters) {

  size_t   i = 0;
  char	   data[32];
  char	   str[32];
  uint16_t timeout;

  lcd_write_buffer (SCREEN_CLEAR);
  vTaskDelay (500 / portTICK_RATE_MS);

  uart0_println ("Press 'I' for setup");
  lcd_write_buffer ("Please setup                    ");

  vTaskDelay (1000 / portTICK_RATE_MS);

  while (1) {
	if (uart0_rx_ready ( ) && uart0_get_char ( ) == 'I') {
	  uart0_println ("Please type sensor CODE (3 uppercase letters):");
	  char tmp[3] = {'\0'};

	  while (!uart0_rx_ready ( ))
		;
	  tmp[0] = uart0_get_char ( );

	  while (!uart0_rx_ready ( ))
		;
	  tmp[1] = uart0_get_char ( );

	  while (!uart0_rx_ready ( ))
		;
	  tmp[2] = uart0_get_char ( );

	  uart0_print ("Send command: ");
	  uart0_println (tmp);
	  com_write_buffer (tmp);

	  /* */ if (strncmp (tmp, "LDR", 3) == 0)
		device_type = SENSOR_LDR;
	  else if (strncmp (tmp, "IRD", 3) == 0)
		device_type = SENSOR_IRD;
	  else if (strncmp (tmp, "CNY", 3) == 0)
		device_type = SENSOR_CNY;
	  else if (strncmp (tmp, "MIC", 3) == 0)
		device_type = SENSOR_MIC;

	  init_mode = true;

	  vTaskDelay (1000 / portTICK_RATE_MS);

	} else if (xStreamBufferReceive (com_in, &data, 1, COM_SPEED * 2) == pdPASS) {
	  str[i++] = *data;
	} else if (i > 0) {

	  if (init_mode) {
		uart0_print ("Got command: ");
		uart0_println (str);
		if (!(strncmp (str, "OK!", 3) == 0))
		  device_type = SENSOR_UNKNOWN;
		else
		  init_mode = false;
		timeout = 10;
	  } else if (device_type != SENSOR_UNKNOWN) {
		uart0_print ("Got data: ");
		uart0_println (str);
		lcd_write_buffer (SCREEN_CLEAR);
		lcd_write_buffer_size (sensor_text[device_type], 16);
		lcd_write_buffer (str);
	  }

	  timeout = 5;
	  while (i > 0)
		str[i--] = '\0';

	} else if (device_type != SENSOR_UNKNOWN && timeout == 0) {
	  xStreamBufferReset (com_out);
	  uart0_println ("Send command: REQ");
	  com_write_buffer ("REQ");
	  timeout = 3;
	}
	vTaskDelay (1000 / portTICK_RATE_MS);
	timeout--;
  }
}

static void setupHardware (void) {
  uart_init ( );
  init_systick ( );
}

int main (void) {
  static uint8_t priority = 10;
  setupHardware ( );
  xTaskCreate (com_task, "COM", USERTASK_STACK_SIZE, NULL, --priority, NULL);
  xTaskCreate (status_led_task, "LED", USERTASK_STACK_SIZE, NULL, --priority, NULL);
  xTaskCreate (controller_task, "CONT", USERTASK_STACK_SIZE, NULL, --priority, NULL);
  xTaskCreate (lcd_task, "LCD", USERTASK_STACK_SIZE, NULL, --priority, NULL);
  vTaskStartScheduler ( );
  return 0;
}
