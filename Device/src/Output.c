/*
 * Output.c
 *
 * Created: 12-05-2022 12:41:18
 *  Author: sylle
 */ 
#include "Output.h"
void SSD_init(){
	DDR_SSD |= (PINS_SSD << PIN_SSD);
	
}
void SSD_write(uint8_t num){
	DDR_SSD = 0;
	MCUCR &= ~(1<<PUD);
	switch(num){
		case 0x0:
		PORT_SSD = SSD_0;
		break;
		case 0x1:
		PORT_SSD = SSD_1;
		break;
		case 0x2:
		PORT_SSD = SSD_2;
		break;
		case 0x3:
		PORT_SSD =SSD_3;
		break;
		case 0x4:
		PORT_SSD = SSD_4;
		break;
		case 0x5:
		PORT_SSD = SSD_5;
		break;
		case 0x6:
		PORT_SSD = SSD_6;
		break;
		case 0x7:
		PORT_SSD = SSD_7;
		break;
		case 0x8:
		PORT_SSD = SSD_8;
		break;
		case 0x9:
		PORT_SSD = SSD_9;
		break;
		case 0xA:
		PORT_SSD = SSD_A;
		break;
		case 0xB:
		PORT_SSD = SSD_B;
		break;
		case 0xC:
		PORT_SSD = SSD_C;
		break;
		case 0xD:
		PORT_SSD = SSD_D;
		break;
		case 0xE:
		PORT_SSD = SSD_E;
		break;
		case 0xF:
		PORT_SSD = SSD_F;
		break;
	}
}