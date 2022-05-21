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

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
//
#include "LED.h"
#include "Output.h"
#include "com.h"
#include "sensor.h"
#include "ticks.h"

#define STRCMP(s) ((s[0] - 'A') + (s[1] - 'A') * 26 + (s[2] - 'A') * 260)

#endif /* HEADER_H_ */
