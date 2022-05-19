/*
 * LED.h
 *
 * Created: 11-05-2022 10:29:36
 *  Author: dense
 */

#ifndef LED_H_
#define LED_H_

#include "header.h"

#define PORT_LED PORTB
#define DDR_LED DDRB
#define PIN_LED PINB6
#define LED PINB

void LED_on (void);
void LED_off (void);
void LED_toggle (void);
void LED_init (void);
void LED_blink (void);
void binary8 (uint8_t val);
void binary16 (uint16_t val);

#endif /* LED_H_ */
