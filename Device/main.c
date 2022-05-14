/*
 * Device.cpp
 *
 */
#include "src/header.h"

int main (void) {
  // Setup
  power_init (POWER_SAVE, true, PWR_ADC | PWR_USI | PWR_TI0 | PWR_TI1 | PWR_LIN); // Save power, disable BOD and the listed modules
  LED_init ( );

  // After setup; power down the chip and let interupts re-acctivate it
  power_down ( );

  // Loop
  while (1) {
	if (ticks > 100) {
	  ticks = 0;
	  LED_toggle ( );
	}
  }
}
