#ifndef _STATUS_LED_H
#define _STATUS_LED_H

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "FreeRTOS.h"
#include "Task.h"

#define SLED		6

void status_led_task(void* pvParameters);

#endif

