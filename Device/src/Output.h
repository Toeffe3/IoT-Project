/*
 * Output.h
 *
 * Created: 12-05-2022 12:41:45
 *  Author: sylle
 */ 


#ifndef OUTPUT_H_
#define OUTPUT_H_
#include "header.h"
#define DDR_SSD DDRA
#define PORT_SSD PORTA
#define SSD PINA
#define PIN_SSD PINA0
#define PINS_SSD 0b01111111
#define SSD_0 0b01110111
#define SSD_1 0b00100001
#define SSD_2 0b01011011
#define SSD_3 0b01101011
#define SSD_4 0b00101101
#define SSD_5 0b01101110
#define SSD_6 0b01111110
#define SSD_7 0b00100011
#define SSD_8 0b01111111
#define SSD_9 0b00101111
#define SSD_A 0b00111111
#define SSD_B 0b01111001
#define SSD_C 0b01010101
#define SSD_D 0b01111001
#define SSD_E 0b01011110
#define SSD_F 0b00011110

void SSD_write(uint8_t num);

#endif /* OUTPUT_H_ */