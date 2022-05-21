#include "status_led.h"

void status_led_init(void) {
	// Enable the GPIO port that is used for the on-board LED.
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD;
	GPIO_PORTD_DIR_R |= (1 << SLED);
	GPIO_PORTD_DEN_R |= (1 << SLED);
}

void status_led_task(void* pvParameters) {
	status_led_init();
	while ( 1 ) {
		GPIO_PORTD_DATA_R ^= (1 << SLED);  // Toggle status led
		vTaskDelay(500 / portTICK_RATE_MS);  // wait 500 ms.
	}
}

