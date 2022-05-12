/*
 * ticks.c
 *
 * Created: 12-05-2022 10:40:22
 *  Author: dense
 */

uint32_t ticks = 0;

ticks_init (void) {
  ASSR = (1 << AS0);
  TIMSK0 |= (1 << OCIE0A);
  TCCR0A |= (1 << COM0A1) | (1 << COM0A0) | (1 << WGM01); // Set OCR1A, CTC
  TCCR0B |= (0 << CS02) | (0 << CS01) | (1 << CS00);	  // 1
  OCR1A = 499;
}

ISR (TIMER0_OVF_vect) { ticks++; }
