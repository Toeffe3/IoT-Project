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
  uint8_t i = 0;
  while (1) {
	//PORTA = 0xff;
	//_delay_ms(1000);
	//PORTA = 0x00;
	SSD_write(i++%16);
	_delay_ms(1000);
}
}