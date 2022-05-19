/*
 * com.h
 *
 * Created: 18-05-2022 09:53:03
 *  Author: dense
 */

#ifndef COM_H_
#define COM_H_

#include "header.h"

#define DDR_COM DDRB
#define PORT_COM PORTB
#define COM PINB

#define PIN_COM_0 PINB0
#define PIN_COM_1 PINB2

#define COM_IDLE 0
#define COM_READ 1
#define COM_WRITE 2
#define COM_DONE 3

#define COM_FLAT 0b00
#define COM_ZERO 0b01
#define COM_ONE 0b10
#define COM_SIGNAL 0b11

#define COM_SPEED 20

void	com_init ( );
void	com_send_signal (void);
uint8_t com_get_data (void);
uint8_t com_wait_for_next (void);
void	com_get_string (char* str);
void	com_send_bit (bool b);
void	com_send_char (char c);
void	com_send_string (const char* str);
void	com_send_num (uint16_t num);

#endif /* COM_H_ */
