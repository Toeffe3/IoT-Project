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
	//com_send_char('a' + i++);
	uint16_t data = LDR_read();
	com_send_num(data);
	_delay_ms(1000);
	  
	// PORTA = 0xff;
	//_delay_ms(1000);
	// PORTA = 0x00;
	//SSD_write (i++ % 16);
	//_delay_ms (1000);
  }
}
