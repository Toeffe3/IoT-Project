/*
 * Device.cpp
 *
 */
#include "src/header.h"

int main (void) {
  // Setup
  ticks_init ( );
  LED_init ( );
  LDR_init();
  com_init();
  // Loop
  uint8_t i = 0;
  while (1) {
	  
	  if (LDR_read() > 512) LED_off();
	  else LED_on();
	// PORTA = 0xff;
	//_delay_ms(1000);
	// PORTA = 0x00;
	//SSD_write (i++ % 16);
	//_delay_ms (1000);
  }
}
