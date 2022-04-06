/*
 * Hub.cpp
 *
 *
 */


#include "gpio.h"
#include "header.h"
#include "rtc.h"
#include "usb.h"

void init (void);

int main (void) {
  uint32_t ticks;

  // Init
  init ( );

  // Loop
  while (1) {}
}

void init ( ) { 
	tc_init();
	usb_init();
	gpio_init ();
	rtc_init (OSC_32KHZ, PRESCALER, TOP_VAL); }


// Mayby AVR32_RTC_ISR
ISR (AVR32_RTC_IRQ) { ticks++; }
