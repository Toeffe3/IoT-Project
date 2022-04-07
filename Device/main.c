/*
 * Device.cpp
 *
 */
#include "src/header.h"
#include "src/USI.h"

int main (void) {
  // Setup 
  twi_init();
  // Loop
  while (1) {
    twi_transfer('a');
    _delay_ms(10);

  }
}
