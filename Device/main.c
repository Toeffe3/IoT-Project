/*
 * Device.cpp
 *
 */
#include "src/header.h"

#define SENSOR_LDR "LDR"
//#define SENSOR_IRD "IRD"
//#define SENSOR_CNY "CNY"

int main (void) {

  char	str[4];
  uint8_t mode = 0;

  // Setup
  com_init ( );
  LED_init ( );

  _delay_ms (COM_SPEED * 10);

#ifdef SENSOR_LDR
  LDR_init ( );
  com_send_string (SENSOR_LDR);
#endif
#ifdef SENSOR_IRD
  IRD_init ( );
  com_send_string (SENSOR_IRD);
#endif
#ifdef SENSOR_CNY
  CNY_init ( );
  com_send_string (SENSOR_CNY);
#endif

  // Loop
  while (1) {

	com_wait_for_signal ( );
	LED_on ( );
	com_get_string (str);

	LED_off ( );
	_delay_ms (COM_SPEED * 10);

	if (STRCMP (str) == STRCMP ("REQ")) {

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

	} else // Echo unknown commands
	  com_send_string (str);

	_delay_ms (COM_SPEED * 10);
  }
}
