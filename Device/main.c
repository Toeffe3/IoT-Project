 */
#include "src/header.h"

// Select which sensor the processor should be used for
#define SENSOR_LDR "LDR"
//#define SENSOR_IRD "IRD"
//#define SENSOR_CNY "CNY"

int main (void) {

#ifdef SENSOR_LDR
#define USING_ADC
#define USING_ADC
#endif

#include "src/header.h"

int main (void) {

  // Setup
  uint8_t power_down_modules = PWR_USI | PWR_LIN | PWR_TI0;

#ifndef USING_DELAY
  power_down_modules |= PWR_TI1;
#endif
#ifndef USING_ADC
  power_down_modules |= PWR_ADC;
#endif

  power_init (			   // Minimize power usage
	  POWER_HIGH,		   // Decides which clocks keeps running
	  false,			   // Do not Disable Brown out detection
	  power_down_modules); // Modules that should be turned off

  LED_init ( );
  LDR_init ( );
  com_init ( );

#ifdef SENSOR_LDR
  LDR_init ( );
  char str[4] = SENSOR_LDR;
#endif
#ifdef SENSOR_IRD
  IRD_init ( );
  char str[4] = SENSOR_IRD;
#endif
#ifdef SENSOR_CNY
  CNY_init ( );
  char str[4] = SENSOR_CNY;
#endif
  com_send_string (str);

  _delay_ms (COM_SPEED * 10);

  // Loop
  while (1) {

	com_wait_for_signal ( );
	com_get_string (str);
	if (STRCMP (str) == STRCMP ("REQ")) {

	  _delay_ms (COM_SPEED * 10);

#ifdef SENSOR_LDR
	  uint16_t data = LDR_read ( );
	  com_send_num (data);
#endif

#ifdef SENSOR_IRD
	  if (IRD_read ( ))
		com_send_string ("Detected!");
	  else
		com_send_string ("No movement!");
#endif

#ifdef SENSOR_IRD
	  uint16_t data = CNY_read ( );
	  com_send_num (data);
#endif

	} else {
	  // Echo unknown commands
	  com_send_string ("UC");
	}
	_delay_ms (COM_SPEED * 10);
  }
}
