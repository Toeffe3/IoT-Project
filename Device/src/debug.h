/*
 * debug.h
 *
 * Created: 12-04-2022 12:57:53
 *  Author: sylle
 */ 


#ifndef DEBUG_H_
#define DEBUG_H_

#define LED PINB6
void init_debug();
void binary( uint8_t val);
void binary( uint16_t val);



#endif /* DEBUG_H_ */