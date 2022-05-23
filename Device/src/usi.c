/******************************************************************************/
/* Project:    Device                                                         */
/* File:	   src/USI.c                                                      */
/* Decription: Universal Serial Interface                                     */
/******************************************************************************/

/***************************** Include files *******************************/
#include "header.h"

/*****************************   Variables   *******************************/
enum { USI_MASTER_ADDRESS, USI_MASTER_WRITE, USI_MASTER_READ } USI_Master_State;

/*****************************   Functions   *******************************/
void twi_init ( ) {
  PORTB |= (1 << PIN_USI_SCL); // Set SCL high
  PORTB |= (1 << PIN_USI_SDA); // Set SDA high
  DDRB |= (1 << PIN_USI_SCL);  // Set SCL as output
  DDRB &= ~(1 << PIN_USI_SDA); // Set SDA as input

  USICR = (1 << USISIE) | (1 << USIWM0) // Set up control register
        | (1 << USIWM1) | (1 << USICS1); 
  USISR = 0xF0; // clear all flags
}

char twi_transfer (char USISR_temp) {
  USISR = USISR_temp;
  do {
	USI_I2C_WAIT_LOW ( );
	USI_CLOCK_STROBE ( );
	while (!(PORT_USI & (1 << PIN_USI_SCL)))
	  ;
	USI_I2C_WAIT_HIGH ( );
	USI_CLOCK_STROBE ( );
  } while (!(USISR & (1 << USIOIF)));
  USI_I2C_WAIT_LOW ( );

  return USIDR;
}

char twi_transmission (char *msg, char msg_size) {
  USI_Master_State = USI_MASTER_ADDRESS;

  USI_SET_SCL_HIGH ( );

  while (!(PORT_USI & (1 << PIN_USI_SCL)))
	;

#ifdef I2C_FAST_MODE
  USI_I2C_WAIT_HIGH ( );
#else
  USI_I2C_WAIT_LOW ( );
#endif
  USI_SET_SDA_OUTPUT ( );
  USI_SET_SCL_OUTPUT ( );
  USI_SET_SDA_LOW ( );
  USI_I2C_WAIT_HIGH ( );
  USI_SET_SCL_LOW ( );
  USI_I2C_WAIT_LOW ( );
  USI_SET_SDA_HIGH ( );
  do {
	switch (USI_Master_State) {
	  case USI_MASTER_ADDRESS:
		if (!(*msg & 0x01)) {
		  USI_Master_State = USI_MASTER_WRITE;
		} else {
		  USI_Master_State = USI_MASTER_READ;
		}
		// Fall through to write to transmit the address bit

	  case USI_MASTER_WRITE:
		USI_SET_SCL_LOW ( );
		USIDR = *(msg); // Load data
		msg++;
		twi_transfer (USISR_TRANSFER_8_BIT);
		USI_SET_SDA_INPUT ( );
		if (twi_transfer (USISR_TRANSFER_1_BIT) & 0x01) {
		  USI_SET_SCL_HIGH ( );
		  USI_SET_SDA_HIGH ( );
		  return 0;
		}
		USI_SET_SDA_OUTPUT ( );
		break;

	  case USI_MASTER_READ:
		USI_SET_SDA_INPUT ( );
		(*msg) = twi_transfer (USISR_TRANSFER_8_BIT);
		msg++;
		USI_SET_SDA_OUTPUT ( );
		if (msg == 1)
		  USIDR = 0xFF; // Load NACK to end transmission
		else
		  USIDR = 0x00; // Load ACK

		twi_transfer (USISR_TRANSFER_1_BIT);
		break;
	}
  } while (--msg_size); // Do until all data is read/written
  USI_SET_SDA_LOW ( );  // Pull SDA low.
  USI_I2C_WAIT_LOW ( );
  USI_SET_SCL_INPUT ( ); // Release SCL.
  while (!(PORT_USI & (1 << PIN_USI_SCL)))
	; // Wait for SCL to go high.
  USI_I2C_WAIT_HIGH ( );
  USI_SET_SDA_INPUT ( ); // Release SDA.
  while (!(PORT_USI & (1 << PIN_USI_SDA)))
	; // Wait for SDA to go high.

  return 1;
}
