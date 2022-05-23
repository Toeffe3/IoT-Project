/******************************************************************************/
/* Project:    Device                                                         */
/* File:       main.c                                                         */
/* Decription: Device main file                                               */
/******************************************************************************/

/***************************** Include files *******************************/
#include "src/header.h"

/*****************************    Defines    *******************************/
// Select which if any modules should be reduced to save power
#define USING_DELAY // Use delay ms requires timer 1
#define USING_ADC

#define MODE_LDR 1
#define MODE_IRD 2
#define MODE_CNY 3
#define MODE_MIC 4

/*****************************   Functions   *******************************/
int main (void) {

  // Setup
  uint8_t mode				 = 0;
  uint8_t power_down_modules = PWR_USI | PWR_LIN | PWR_TI0;

#ifndef USING_DELAY
  power_down_modules |= PWR_TI1;
#endif

  power_init (			   // Minimize power usage
	  POWER_HIGH,		   // Decides which clocks keeps running
	  false,			   // Do not Disable Brown out detection
	  power_down_modules); // Modules that should be turned off

  LED_init ( );
  com_init ( );

  _delay_ms (COM_SPEED * 10);

  // Loop
  while (1) {

	char str[4] = {'\0'};
	com_wait_for_signal ( );
	com_get_string (str);

	_delay_ms (COM_SPEED * 10);

	if (strncmp (str, "REQ", 2) == 0) {

	  LED_on ( );
	  _delay_ms (COM_SPEED * 10);

	  switch (mode) {
		case MODE_LDR:
		  com_send_num (LDR_read ( ));
		  break;

		case MODE_IRD:
		  if (IRD_read ( ))
			com_send_string ("1");
		  else
			com_send_string ("0");
		  break;

		case MODE_CNY:
		  com_send_num (CNY_read ( ));
		  break;

		case MODE_MIC:
		  com_send_num (MIC_read ( ));
		  break;

		default:
		  com_send_string ("UD!"); // Unknown device
	  }							   // END SWITCH MODE
	  LED_off ( );
	} else if (strncmp (str, "LDR", 2) == 0) {
	  LDR_init ( );
	  mode = MODE_LDR;
	  com_send_string ("OK!");
	} else if (strncmp (str, "IRD", 2) == 0) {

	  IRD_init ( );
	  mode = MODE_IRD;
	  com_send_string ("OK!");
	} else if (strncmp (str, "CNY", 2) == 0) {

	  CNY_init ( );
	  mode = MODE_CNY;
	  com_send_string ("OK!");
	} else if (strncmp (str, "MIC", 2) == 0) {
	  MIC_init ( );
	  mode = MODE_MIC;
	  com_send_string ("OK!");
	} else {
	  com_send_string (str); // Unknown command
	}

	_delay_ms (COM_SPEED * 10);
  }
}
