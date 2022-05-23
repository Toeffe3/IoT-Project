/******************************************************************************/
/* Project:    Device                                                         */
/* File:       src/USI.h                                                      */
/* Decription: Device USI header                                              */
/******************************************************************************/

#ifndef USI_H_
#define USI_H_

// TWI
#define DDR_USI DDRB
#define PORT_USI PORTB
#define PIN_USI_SDA PINB0
#define PIN_USI_SCL PINB2
#define TWI_FREQ 1000000L
#define TWI_BITRATE ((F_CPU / TWI_FREQ - 16) / 2)
#define SAMPLE_THD 8

#ifdef I2C_FAST_MODE
#define I2C_TLOW 1.3
#define I2C_THIGH 0.6

// I2C Bus Specification v2.1 STANDARD mode timing limits
#else
#define I2C_TLOW 4.7
#define I2C_THIGH 4.0
#endif

// WIFI

#define USISR_TRANSFER_8_BIT 0b11110000 | (0x00 << USICNT0)
#define USISR_TRANSFER_1_BIT 0b11110000 | (0x0E << USICNT0)

#define USICR_CLOCK_STROBE_MASK                                                \
  (1 << USISIE) | (1 << USIWM0) | (1 << USIWM1) | (1 << USICS1)

#define USI_CLOCK_STROBE( )                                                    \
  { USICR = USICR_CLOCK_STROBE_MASK; }

#define USI_SET_SDA_OUTPUT( )                                                  \
  { DDR_USI |= (1 << PIN_USI_SDA); }
#define USI_SET_SDA_INPUT( )                                                   \
  { DDR_USI &= ~(1 << PIN_USI_SDA); }

#define USI_SET_SDA_HIGH( )                                                    \
  { PORT_USI |= (1 << PIN_USI_SDA); }
#define USI_SET_SDA_LOW( )                                                     \
  { PORT_USI &= ~(1 << PIN_USI_SDA); }

#define USI_SET_SCL_OUTPUT( )                                                  \
  { DDR_USI |= (1 << PIN_USI_SCL); }
#define USI_SET_SCL_INPUT( )                                                   \
  { DDR_USI &= ~(1 << PIN_USI_SCL); }

#define USI_SET_SCL_HIGH( )                                                    \
  { PORT_USI |= (1 << PIN_USI_SCL); }
#define USI_SET_SCL_LOW( )                                                     \
  { PORT_USI &= ~(1 << PIN_USI_SCL); }

#define USI_I2C_WAIT_HIGH( )                                                   \
  { _delay_us (I2C_THIGH); }
#define USI_I2C_WAIT_LOW( )                                                    \
  { _delay_us (I2C_TLOW); }

void twi_init ( );
char twi_transfer (char USISR_temp);
char twi_transmission (char *msg, char msg_size);

#endif /* USI_H_ */
