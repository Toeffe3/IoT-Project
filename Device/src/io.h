/*
 * io.h
 *
 */

#ifndef IO_H_
#define IO_H_


#include <avr/io.h>


#define SENSOR PORTA
#define DEVICE PORTA
#define ESP32 PORTB

//TWI
#define SCL 0
#define SDA 1
#define TWI_FREQ 1000000L
#define TWI_BITRATE ((F_CPU / TWI_FREQ - 16) / 2)
#define SAMPLE_THD 8








#endif /* IO_H_ */
