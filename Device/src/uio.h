/*
 * io.h
 *
 */

#ifndef UIO_H_
#define UIO_H_


#include <avr/iotn167.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define SENSOR PORTA
#define DEVICE PORTA
#define ESP32 PORTB

//TWI
#define DDR_USI             DDRB
#define PORT_USI			PORTB
#define PIN_USI_SDA         PINB0
#define PIN_USI_SCL         PINB2
#define TWI_FREQ 1000000L
#define TWI_BITRATE ((F_CPU / TWI_FREQ - 16) / 2)
#define SAMPLE_THD 8

#ifdef I2C_FAST_MODE
#define I2C_TLOW	1.3
#define I2C_THIGH	0.6

//I2C Bus Specification v2.1 STANDARD mode timing limits
#else
#define I2C_TLOW	4.7
#define I2C_THIGH	4.0
#endif

//WIFI








#endif /* UIO_H_ */
