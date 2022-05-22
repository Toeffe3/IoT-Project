/*
 * uart0.h
 *
 *  Created on: 13. mar. 2022
 *      Author: dense
 */

#ifndef UART0_H_
#define UART0_H_

#include <stdint.h>
#include <stdbool.h>
//
#include "tm4c123gh6pm.h"

#define F_CPU		8000000

#define LCD_CTRL	GPIO_PORTD_DATA_R
#define LCD_RW		0b00000010
#define LCD_RS		0b00000100
#define LCD_EN		0b00001000

#define LCD_DATA	GPIO_PORTC_DATA_R
#define LCD_D4		0b00010000
#define LCD_D5		0b00100000
#define LCD_D6		0b01000000
#define LCD_D7		0b10000000

#define TIVA_SW1	0b00010000

#define RX			0b00000001
#define TX			0b00000010

void uart0_init(uint32_t baud_rate, uint8_t databits, uint8_t stopbits, char parity);
uint32_t uart0_lcrh_databits(uint8_t databits);
uint32_t uart0_lcrh_stopbits(uint8_t stopbits);
uint32_t uart0_lcrh_parity(char parity);
void uart0_fifos_enable(void);
void uart0_fifos_disable(void);
bool uart0_rx_ready(void);
char uart0_get_char(void);
uint8_t uart0_get(void);
bool uart0_tx_ready(void);
void uart0_put(char ch);
void uart0_print(const char* str);
void uart0_println(const char* str);
void uart0_printnum(const uint8_t);
void uart0_printnum16(const uint16_t);

void uart_init(void);
void uart_task(void*);

#endif /* UART0_H_ */
