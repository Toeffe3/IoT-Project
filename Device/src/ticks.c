/*
 * ticks.c
 *
 * Created: 12-05-2022 10:40:22
 *  Author: dense
 */

#include "header.h"

uint32_t ticks = 0;

ticks_init (void) {
  TCCR0A |= (1 << OCR01) | (1 << OCR00) | (1 << WGM01); // CTC, HIGH on match
  TCCR0B = (0 << CS02) | (0 << CS01) | (1 << CS00);		// Prescale 1
  TIMSK0 |= (1 << OCIE0A) | (1 << TOIE0);				// Enable interupts
  ASSR  = (0 << AS0);									// No Async operation
  OCR0A = 499;											// 1ms
}

ISR (TIMER0_COMPA_vect) {
  ticks++; // 1 ms has elapsed
  TIFR0 = (1 << OCF0A);
}

ISR (TIMER0_OVF_vect) { TIFR0 = (1 << TOV0); }
