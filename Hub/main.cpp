/*
 * Hub.cpp
 *
 *
 */

#include "header.h"
#include "rtc.h"
#include "gpio.h"


void init (void);

int main (void) {
  int ticks;

  // Init
  init ( );

  // Loop
  while (1) {}
}

void init ( ) { 
	gpio_init(true) 
	rtc_init (OSC_32KHZ, PRESCALER, TOP_VAL);
	}

// Mayby AVR32_RTC_ISR
ISR (AVR32_RTC_IRQ) { ticks++; }
