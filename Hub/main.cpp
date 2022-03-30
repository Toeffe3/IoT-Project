/*
 * Hub.cpp
 *
 *
 */

#include "header.h"
#include "rtc.h"

void init(void);

int main (void) {
	int ticks;
	
	
  // Init
	init();

  // Loop
  while (1) {}
}

void init(){
	rtc_init(true);	
}


// Mayby AVR32_RTC_ISR
ISR(AVR32_RTC_IRQ ){
	ticks++;
}
