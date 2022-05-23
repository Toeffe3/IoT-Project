/******************************************************************************/
/* Project:    Device                                                         */
/* File:       src/LED.h                                                      */
/* Decription: Device LED control header                                      */
/******************************************************************************/

#ifndef LED_H_
#define LED_H_

/***************************** Include files *******************************/
#include "header.h"

/*****************************    Defines    *******************************/
#define PORT_LED PORTB
#define DDR_LED DDRB
#define PIN_LED PINB6
#define LED PINB

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/
void LED_on (void);
void LED_off (void);
void LED_toggle (void);
void LED_init (void);
void LED_blink (void);
void binary8 (uint8_t val);
void binary16 (uint16_t val);

#endif /* LED_H_ */
