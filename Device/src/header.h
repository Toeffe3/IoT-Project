/******************************************************************************/
/* Project:    Device                                                         */
/* File:       src/header.h                                                   */
/* Decription: General header file                                            */
/******************************************************************************/

#ifndef HEADER_H_
#define HEADER_H_

#define F_CPU 1000000

/***************************** Include files *******************************/
// Standard libraries
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

// Custom functions
#include "led.h"
#include "output.h"
#include "com.h"
#include "power.h"
#include "sensor.h"

/*****************************    Defines    *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

#endif /* HEADER_H_ */
