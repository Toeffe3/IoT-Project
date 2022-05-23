/******************************************************************************/
/* Project:    Device                                                         */
/* File:       src/output.h                                                   */
/* Decription: Device output control header                                   */
/******************************************************************************/

#ifndef OUTPUT_H_
#define OUTPUT_H_

/***************************** Include files *******************************/
#include "header.h"

/*****************************    Defines    *******************************/
#define DDR_SSD DDRA
#define PORT_SSD PORTA
#define SSD PINA
#define PIN_SSD PINA0
#define PINS_SSD 0b01111111
#define SSD_0 0b01111101
#define SSD_1 0b00110000
#define SSD_2 0b01011110
#define SSD_3 0b01111010
#define SSD_4 0b00110011
#define SSD_5 0b01101011
#define SSD_6 0b00101111
#define SSD_7 0b01110000
#define SSD_8 0b01111111
#define SSD_9 0b01111011
#define SSD_A 0b01110111
#define SSD_B 0b00101111
#define SSD_C 0b01001101
#define SSD_D 0b00111110
#define SSD_E 0b01001111
#define SSD_F 0b01000111

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/
void SSD_write(uint8_t num);

#endif /* OUTPUT_H_ */