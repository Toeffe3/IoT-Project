/*
 * Hub.cpp
 *
 *
 */

#include "header.h"
#include "gpio.h"
#include "rtc.h"

void init (void);

int main (void) {
  int ticks;

  // Init
  init ( );

  // Loop
  while (1) {}
}

void init ( ) { 
	gpio_init ();
	rtc_init (OSC_32KHZ, PRESCALER, TOP_VAL); }

// Mayby AVR32_RTC_ISR
ISR (AVR32_RTC_IRQ) { ticks++; }
