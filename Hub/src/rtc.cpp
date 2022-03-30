/*
 * rtc.cpp
 *
 * Created: 30-03-2022 13:15:36
 *  Author: Tobia
 */ 

#include "rtc.h"


void rtc_init(bool souceclock, int prescaler, int top_val){
		// Source clock
		// = 1 << EN; // RTC on 1 or off 0
		AVR32_RTC_CTRL = OSC_32KHZ << AVR32_RTC_CTRL_EN; // Use 32 KHz oscillator 1 or use RC oscillator 0
		AVR32_RTC_CTRL = prescaler << AVR32_RTC_CTRL_PCLR; // Select Prescaler 4 bit value where f_RTC = f_input / (2^(PSEL+1))
		// Counter operation
		// When enabled, the RTC will increment until it reaches TOP, and then wraps to 0x0.
		// The status bit TOPI in Interrupt Status Register (ISR) is set to one when this occurs.
		AVR32_RTC_VAL = top_val; // TOP value
		rtc_endable_interrupt(); // Enable RTC interrupt 1
}

void rtc_disable_interrupt(void){
		AVR32_RTC_IDR = DISABLE_RTC_INTERRUPT << AVR32_RTC_IER_TOPI // Disable RTC interrupt 1
}

void rtc_endable_interrupt(void){
	AVR32_RTC_IER = ENDABLE_RTC_INTERRUPT << AVR32_RTC_IER_TOPI; // Enable RTC interrupt 1	
}










