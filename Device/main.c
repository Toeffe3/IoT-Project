/*
 * Device.cpp
 *
 */
#include "src/Sensor.h"
#include "src/debug.h"
#include "src/header.h"

int main (void) {
  // Setup
  init_debug ( );
  init_MIC();
  // Loop
  while (1) {
	if (read_mic ( ) > 80) {
	  led_on ( );
	} else
	  led_off ( );
  }
}
