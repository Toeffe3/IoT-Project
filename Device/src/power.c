/******************************************************************************/
/* Project:    Device                                                         */
/* File:       src/power.c                                                    */
/* Decription: Device power control                                           */
/******************************************************************************/

/***************************** Include files *******************************/
#include "power.h"

/*****************************   Functions   *******************************/
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
