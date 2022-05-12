/*
 * Device.cpp
 *
 */
#include "src/header.h"

int main (void) {
  // Setup
  LED_init ( );
  // Loop
  while (1) {
	if (ticks > 100) {
	  ticks = 0;
	  LED_toggle ( );
	}
  }
}
