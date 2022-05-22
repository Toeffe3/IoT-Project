/*
 * header.h
 *
 * Created: 11-05-2022 10:16:34
 *  Author: dense
 */

#ifndef HEADER_H_
#define HEADER_H_

#define SENSOR PORTA
#define DEVICE PORTA
#define ESP32 PORTB
#define F_CPU 1000000

// Standard libraries
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

// Custom functions
#include "LED.h"
#include "Output.h"
#include "com.h"
#include "power.h"
#include "sensor.h"

#endif /* HEADER_H_ */
