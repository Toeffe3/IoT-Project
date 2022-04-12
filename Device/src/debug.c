/*
 * debug.c
 *
 * Created: 12-04-2022 12:44:05
 *  Author: sylle
 */ 
#include "debug.h"
void init_debug(){
	DDRB |= (1 << LED); 
	
}

void binary( uint8_t val){
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		if (val & (1<<i)) PINB |= (1<<LED);
		else PINB &= ~(1<<LED);
		 
	}
}

void binary( uint16_t val){
	uint8_t i;
	for (i = 0; i < 16; i++)
	{
		if (val & (1<<i)) PINB |= (1<<LED);
		else PINB &= ~(1<<LED);
		
	}
}