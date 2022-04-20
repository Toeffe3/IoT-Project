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
  init_IR ( );
  // Loop
  while (1) {
	if (read_ir ( )) {
	  led_on ( );
	} else
	  led_off ( );
  }
}
