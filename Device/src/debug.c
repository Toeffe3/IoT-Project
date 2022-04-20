/*
 * debug.c
 *
 * Created: 12-04-2022 12:44:05
 *  Author: sylle
 */
#include "debug.h"
#include "header.h"
void init_debug ( ) { DDRB |= (1 << LED); }
void blink ( ) {
  PINB |= (1 << LED);
  _delay_ms (500);
}

void binary8 (uint8_t val) {
  uint8_t i;
  for (i = 0; i < 8; i++) {
	if (val & (1 << i))
	  PORTB |= (1 << LED);
	else
	  PORTB &= ~(1 << LED);
	_delay_ms (500);
  }
}

void binary16 (uint16_t val) {
  uint8_t i;
  for (i = 0; i < 16; i++) {
	if (val & (1 << i))
	  PORTB |= (1 << LED);
	else
	  PORTB &= ~(1 << LED);
	_delay_ms (500);
  }
}
void led_on ( ) { PORTB |= (1 << LED); }

void led_off ( ) { PORTB &= ~(1 << LED); }
