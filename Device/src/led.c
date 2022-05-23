/******************************************************************************/
/* Project:    Device                                                         */
/* File:       src/led.c                                                      */
/* Decription: Device LED control                                             */
/******************************************************************************/

/***************************** Include files *******************************/
#include "led.h"

/*****************************   Functions   *******************************/
void LED_on (void) { PORT_LED |= (1 << PIN_LED); }
void LED_off (void) { PORT_LED &= ~(1 << PIN_LED); }
void LED_toggle (void) { LED |= (1 << PIN_LED); }

void LED_init (void) {
  DDR_LED |= (1 << PIN_LED);
  LED_off ( );
}

void LED_blink (void) {
  LED_toggle ( );
  _delay_ms (500);
}

void binary8 (uint8_t val) {
  for (uint8_t i = 0; i < 8; i++) {
	if (val & (1 << i))
	  LED_on ( );
	else
	  LED_off ( );
	_delay_ms (500);
  }
}

void binary16 (uint16_t val) {
  binary8 (val >> 8);
  binary8 (val);
}
