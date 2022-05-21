/*
 * University ofSoutheren Denmark
 * Embedded C Programming (ECP)
 *
 * Assignment 4 - UART
 * uart0.c
 *
 * Functions to handle UART communication
 *
 * Authors:
 * Oskar Palinko
 *
 * Modified by:
 * Victor
 */
#include "FreeRTOS.h"
#include "task.h"
#include "uart0.h"

void uart0_init(uint32_t baud_rate, uint8_t databits, uint8_t stopbits, char parity) {
	uint32_t BRD;

#ifndef E_PORTA
#define E_PORTA
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;				// Enable clock for Port A
#endif

#ifndef E_UART0
#define E_UART0
	SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0;				// Enable clock for UART 0
#endif

	GPIO_PORTA_AFSEL_R |= (RX | TX);					// set PA0 and PA1 to alternative function (RX and TX) (uart0)
	GPIO_PORTA_DIR_R &= ~(RX);							// set PA0 (uart0 RX) to input
	GPIO_PORTA_DIR_R |= (TX);							// set PA1 (uart0 TX) to output
	GPIO_PORTA_DEN_R |= (RX | TX);						// enable digital operation of PA0 and PA1
	//GPIO_PORTA_PUR_R   |= 0x00000002;

	BRD = 64000000 / baud_rate;							// X-sys*64/(16*baudrate) = 16M*4/baudrate
	UART0_IBRD_R = BRD / 64;
	UART0_FBRD_R = BRD & 0x0000003F;

	UART0_LCRH_R = uart0_lcrh_databits(databits);
	UART0_LCRH_R += uart0_lcrh_stopbits(stopbits);
	UART0_LCRH_R += uart0_lcrh_parity(parity);

	uart0_fifos_disable();

	UART0_CTL_R |= (UART_CTL_UARTEN | UART_CTL_TXE);	// Enable UART
}

uint32_t uart0_lcrh_databits(uint8_t databits) {
	if ( (databits < 5) || (databits > 8) ) databits = 8;
	return (((uint8_t) databits - 5) << 5);				// Control bit 5-6, WLEN
}

uint32_t uart0_lcrh_stopbits(uint8_t stopbits) {
	if ( stopbits == 2 ) return (1 << 3);				// return bit 3 = 1
	else return 0;										// return all zeros
}

//@formatter:off
uint32_t uart0_lcrh_parity(char parity) {
	switch ( parity ) {
		case 'e': return 0x06;
		case 'o': return 0x02;
		case '0': return 0x86;
		case '1': return 0x82;
		case 'n':
		default:  return 0x00;
	}
}
//@formatter:on
void uart0_fifos_enable(void) {
	UART0_LCRH_R |= TX;
}

void uart0_fifos_disable(void) {
	UART0_LCRH_R &= ~(RX);
}

bool uart0_rx_ready(void) {
	return (UART0_FR_R & UART_FR_RXFF);
}

char uart0_get_char(void) {
	return (UART0_DR_R);
}

uint8_t uart0_get(void) {
	return (uint8_t) (UART0_DR_R - '0');
}

bool uart0_tx_ready(void) {
	return (UART0_FR_R & UART_FR_TXFE);
}

void uart0_put(char ch) {
	UART0_DR_R = ch;
}

void uart0_print(const char* str) {
	while ( *str != '\0' ) {
		while ( !uart0_tx_ready() );
		uart0_put(*str);
		str++;
	}
}

void uart0_println(const char* str) {
	uart0_print(str);
	uart0_print("\n\r");
}

void uart0_printnum(const uint8_t num) {
	while ( !uart0_tx_ready() );
	if ( num >= 100 ) uart0_put(((num % 1000) / 100) + '0');
	if ( num >= 10 ) uart0_put(((num % 100) / 10) + '0');
	if ( num < 10 ) uart0_put('0');  // Pad with '0'
	while ( !uart0_tx_ready() );
	uart0_put((num % 10) + '0');
}

void uart0_printnum_no_pad(const uint8_t num) {
	while ( !uart0_tx_ready() );
	if ( num >= 100 ) uart0_put(((num % 1000) / 100) + '0');
	if ( num >= 10 ) uart0_put(((num % 100) / 10) + '0');
	while ( !uart0_tx_ready() );
	uart0_put((num % 10) + '0');
}

void uart0_printnum16(const uint16_t num) {
	while ( !uart0_tx_ready() );
	if ( num >= 100000 ) uart0_put(((num % 1000000) / 100000) + '0');
	while ( !uart0_tx_ready() );
	if ( num >= 10000 ) uart0_put(((num % 100000) / 10000) + '0');
	while ( !uart0_tx_ready() );
	if ( num >= 1000 ) uart0_put(((num % 10000) / 1000) + '0');
	while ( !uart0_tx_ready() );
	if ( num >= 100 ) uart0_put(((num % 1000) / 100) + '0');
	while ( !uart0_tx_ready() );
	if ( num >= 10 ) uart0_put(((num % 100) / 10) + '0');
	while ( !uart0_tx_ready() );
	if ( num < 10 ) uart0_put('0');  // Pad with '0'
	while ( !uart0_tx_ready() );
	uart0_put((num % 10) + '0');

}

void uart_init(void) {
	uart0_init(19200, 8, 1, 'n');
	uart0_println("");
	uart0_println("UART Startup Done");
}

