/*
 * debug.h
 *
 * Created: 12-04-2022 12:57:53
 *  Author: sylle
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#define LED PINB6

#include "header.h"

void init_debug ( );
void blink ( );
void binary8 (uint8_t val);
void binary16 (uint16_t val);
void led_on ( );
void led_off ( );

#endif /* DEBUG_H_ */
