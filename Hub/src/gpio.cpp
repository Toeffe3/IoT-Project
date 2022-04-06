/*
 * gpio.cpp
 *
 * Created: 05-04-2022 10:04:19
 *  Author: Rainbow Dash
 */ 

#include "gpio.h"


// Note til senere: 
//	GPIO interrupts can only be triggered when the CLK_GPIO is enabled.
//	Interrupt Flag Clear Register (IFRC)

void gpio_init(){
	
	AVR32_GPIO_GFER = ALL_PORTS_ON;			// Setting all pins too GPIO
	AVR32_GPIO_PMR0 = ALL_PERIPHERALS_0_A;	// PMR 0-1 is choosing what peripheral is used if peripheral is chosen, PMR0 is bit 0, and PMR1 is bit 1 
	AVR32_GPIO_PMR1 = ALL_PERIPHERALS_1_A;	// The options for Peripheral is A, B, C and D. 00 -> A, 01 -> B, 10 -> C and 11 -> D
	AVR32_GPIO_ODER = ALL_ODER_ENABLE;		// The output driver is enabled for the corresponding pin
	AVR32_GPIO_OVR = ALL_OVR_1;				// The value to be driven on the I/O line is 1.
	AVR32_GPIO_PUER = ALL_PUER_OFF;			// Setting Pull-ups for GPIO-Pins
	AVR32_GPIO_IER = ALL_Interrupts_OFF;	// Setting If Interrupts is on for the pin
	AVR32_GPIO_GFER = ALL_GFER_OFF;			// Input glitch filter (Only changed when IER is ‘0’. !!!)
	AVR32_GPIO_IMR0 = IMR0_0				// Setting Interrupt mode with IMR0 and IMR1
	AVR32_GPIO_IMR1 = IMR1_0				// IMR0 is bit 0, and IMR1 is bit 1; 00 -> Pin Change, 01 -> Rising Edge; 10 -> Falling Edge
	
}

void gpio_interrupt_off(){
		AVR32_GPIO_IER = ALL_Interrupts_OFF;	// Setting If Interrupts is on for the pin
}

void gpio_interrupt_on(){
		AVR32_GPIO_IER = ALL_Interrupts_ON;	// Setting If Interrupts is on for the pin
}