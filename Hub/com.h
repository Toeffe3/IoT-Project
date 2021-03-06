/******************************************************************************/
/* Project:    Hub                                                            */
/* File:       com.h                                                          */
/* Decription: Hub communication header                                       */
/******************************************************************************/

#ifndef COM_H_
#define COM_H_

/***************************** Include files *******************************/
#include <stdbool.h>
#include <string.h>
#include "FreeRTOS.h"
#include "tm4c123gh6pm.h"
//
#include "task.h"
#include "stream_buffer.h"

/*****************************    Defines    *******************************/
#define PIN_COM 4
#define PIN_COM_0 0b00000100 // PB2 (tiva)
#define PIN_COM_1 0b00001000 // PB3 (tiva)
// bits types
#define COM_SIGNAL 0b11
#define COM_FLAT 0b00
#define COM_ONE 0b10
#define COM_ZERO 0b01
// Modes
#define COM_IDLE 0
#define COM_WRITE 1
#define COM_WAIT_FOR_RESPONSE 2

#define COM_SPEED 20

#define SENSOR_UNKNOWN 0
#define SENSOR_LDR 1
#define SENSOR_IRD 2
#define SENSOR_CNY 3
#define SENSOR_MIC 4

/*****************************   Variables   *******************************/
StreamBufferHandle_t com_in;
StreamBufferHandle_t com_out;

uint8_t device_type;

/*****************************   Functions   *******************************/
void com_task(void*);
void com_init(void);
size_t com_write_buffer(const char* data);

#endif /* COM_H_ */
