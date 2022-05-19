/*
 * Device.cpp
 *
 */
#include "src/header.h"

int main (void) {
  // Setup
  power_init (POWER_SAVE, true, PWR_ADC | PWR_USI | PWR_TI0 | PWR_TI1 | PWR_LIN); // Save power, disable BOD and the listed modules
  LED_init ( );
  ticks_init ( );
  LDR_init ( );
  com_init ( );

  // After setup; power down the chip and let interupts re-acctivate it
  power_down ( );

  // Loop
  uint8_t i = 0;
  while (1) {
	// com_send_char('a' + i++);
	uint16_t data = LDR_read ( );
	com_send_num (data);
	_delay_ms (1000);

	// PORTA = 0xff;
	//_delay_ms(1000);
	// PORTA = 0x00;
	// SSD_write (i++ % 16);
	//_delay_ms (1000);
  }
}
