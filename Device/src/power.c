/*
 * power.c
 *
 * Created: 14-05-2022 15:31:25
 *  Author: dense
 */

#include "power.h"

void power_init (uint8_t mode, bool bod_detection, uint8_t reduce_module) {

  if (bod_detection) {
	cli ( );
	MCUCR |= (1 << BODS) | (1 << BODSE);
	MCUCR &= (1 << BODSE);
	sei ( );
  }

  if (mode != POWER_HIGH)
	SMCR = mode;

  // Reduced modules are shut down and has to be started again by enabling them
  PRR = reduce_module;
}

void power_down (void) {
  sei ( ); // Cannot wake by software if interupts are disabled
  sleep ( );
}
