/******************************************************************************/
/* Project:    Hub                                                            */
/* File:       status_led.h                                                   */
/* Decription: Hub status LED header file                                     */
/******************************************************************************/

#ifndef _STATUS_LED_H
#define _STATUS_LED_H

/***************************** Include files *******************************/
#include <stdint.h>
//
#include "FreeRTOS.h"
#include "tm4c123gh6pm.h"
//
#include "Task.h"

/*****************************    Defines    *******************************/
#define SLED		6

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/
void status_led_task(void* pvParameters);

#endif

