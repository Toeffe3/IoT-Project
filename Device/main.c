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
  init_LDR ( );
  // Loop
  while (1) {
	if (read_LDR ( )) {
	  led_on ( );
	} else
	  led_off ( );
  }
}
