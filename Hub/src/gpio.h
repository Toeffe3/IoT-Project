/*
 * gpio.h
 *
 * Created: 05-04-2022 10:03:53
 *  Author: Rainbow Dash
 */ 

// Define --------------------------------------------------------

#ifndef GPIO_H_
#define GPIO_H_

#define ALL_PORTS_ON = 0xFFFF;
#define ALL_PERIPHERALS_0_A = 0b0;
#define ALL_PERIPHERALS_1_A = 0b0;
#define ALL_ODER_ENABLE = 0xFFFF;
#define ALL_ODER_DISABLE = 0x0000;
#define ALL_OVR_1 = 0xFFFF;
#define ALL_OVR_1 = 0x0000;
#define ALL_PUER_UP_ALL = 0xFFFF;
#define ALL_PUER_OFF = 0x0000;
#define ALL_GFER_OFF = 0x0000;
#define ALL_Interrupts_OFF = 0x0000;
#define ALL_Interrupts_ON = 0xFFFF;
#define IMR0_0 = 0x0000;
#define IMR1_0 = 0x0000;


#endif /* GPIO_H_ */


// Function ---------------------------------------------------
// Setting up GPIO
void gpio_init (void);

// Turn off GPIO interrups
void gpio_interrupt_off(void);

// Turn off GPIO interrups
void gpio_interrupt_on(void);

