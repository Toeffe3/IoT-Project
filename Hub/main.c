

/**
 * main.c
 */
#include "FreeRTOS.h"
#include "com.h"
#include "emp_type.h"
#include "status_led.h"
#include "systick_frt.h"
#include "task.h"
#include "tm4c123gh6pm.h"
#include "uart0.h"
#include <stdint.h>
//#include "i2c.h"

#define USERTASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define IDLE_PRIO 0
#define LOW_PRIO 1
#define MED_PRIO 2
#define HIGH_PRIO 3

static void setupHardware (void)
/*****************************************************************************
 *   Input    :  -
 *   Output   :  -
 *   Function :
 *****************************************************************************/
{
  // TODO: Put hardware configuration and initialisation in here

  // Warning: If you do not initialize the hardware clock, the timings will be
  // inaccurate
  init_systick ( );
  status_led_init ( );
}

int main (void) {
  static uint8_t priority = 10;
  setupHardware ( );
  xTaskCreate (status_led_task, "Status_led", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL);
  xTaskCreate (com_task, "COM", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL);
  xTaskCreate (uart_task, "UART", configMINIMAL_STACK_SIZE, NULL, --priority, NULL); // baud_rate: 19200
  vTaskStartScheduler ( );
  return 0;
}
