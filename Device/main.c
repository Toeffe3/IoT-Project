/*
 * Device.cpp
 *
 */
#include "src/header.h"

int main (void) {
  // Setup
  ticks_init();
  LED_init ( );
  // Loop
  while (1) {
	SSD_write(1);
}
}