/*
 * Device.cpp
 *
 */
#include "src/header.h"

int main (void) {
  // Setup
  LED_init ( );
  MIC_init ( );
  // Loop
  while (1) {
	if (MIC_read ( ) > 80)
	  LED_on ( );
	else
	  LED_off ( );
  }
}
