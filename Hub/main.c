/**
 * main.c
 */
#include <stdint.h>
#include "FreeRTOS.h"
#include "tm4c123gh6pm.h"
#include "task.h"
#include "systick_frt.h"
#include "status_led.h"

#include "stream_buffer.h"
#include "uart0.h"
#include "com.h"
#include "lcd.h"
//#include "i2c.h"

#define USERTASK_STACK_SIZE configMINIMAL_STACK_SIZE

//@formatter:off
char sensor_text [4] [16] = {
		{ "Unknown sensor  " },
		{ "Light value:    " },
		{ "IR detector:    " },
		{ "Color intensity:" }
};
//@formatter:on

void controller_task(void* pvParameters) {

	size_t i = 0;
	char data [32];
	char str [32];
	uint16_t timeout;

	vTaskDelay(1000 / portTICK_RATE_MS);

	while ( 1 ) {
		if ( xStreamBufferReceive(com_in, &data, 1, COM_SPEED * 2) == pdPASS ) {
			str [i++] = *data;
		} else if ( i > 0 ) {
			if ( device_type != SENSOR_UNKNOWN ) {
				uart0_print("Got data: ");
				uart0_println(str);
			} else uart0_println("Please RESET device to get its type");

			lcd_write_buffer(SCREEN_CLEAR);
			lcd_write_buffer_size(sensor_text [device_type], 16);
			lcd_write_buffer(str);
			while ( i > 0 )
				str [i--] = '\0';
			timeout = 5;
		} else if ( device_type != SENSOR_UNKNOWN && timeout == 0 ) {
			xStreamBufferReset(com_out);
			uart0_println("Send request: REQ");
			com_write_buffer("REQ");
			timeout = 5;
		}
		vTaskDelay(1000 / portTICK_RATE_MS);
		timeout--;
	}
}

static void setupHardware(void) {
	uart_init();
	init_systick();
}

int main(void) {
	static uint8_t priority = 10;
	setupHardware();
	xTaskCreate(com_task, "COM", USERTASK_STACK_SIZE, NULL, --priority, NULL);
	xTaskCreate(status_led_task, "LED", USERTASK_STACK_SIZE, NULL, --priority, NULL);
	xTaskCreate(controller_task, "CONT", USERTASK_STACK_SIZE, NULL, --priority, NULL);
	xTaskCreate(lcd_task, "LCD", USERTASK_STACK_SIZE, NULL, --priority, NULL);
	vTaskStartScheduler();
	return 0;
}
