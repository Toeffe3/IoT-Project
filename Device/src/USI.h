/*
 * USI.h
 *
 * Created: 07/04/2022 12.26.34
 *  Author: victor
 */ 


#ifndef USI_H_
#define USI_H_


/*
 * CPPFile1.cpp
 *
 * Created: 30-03-2022 10:34:49
 *  Author: sylle
 */ 

#define USISR_TRANSFER_8_BIT 		0b11110000 | (0x00<<USICNT0)
#define USISR_TRANSFER_1_BIT 		0b11110000 | (0x0E<<USICNT0)

#define USICR_CLOCK_STROBE_MASK		(1<<USISIE)|(1<<USIWM0)|(1<<USIWM1)|(1<<USICS1)

#define USI_CLOCK_STROBE()			{ USICR = USICR_CLOCK_STROBE_MASK; }

#define USI_SET_SDA_OUTPUT()		{ DDR_USI |=  (1 << PIN_USI_SDA); }
#define USI_SET_SDA_INPUT() 		{ DDR_USI &= ~(1 << PIN_USI_SDA); }

#define USI_SET_SDA_HIGH()			{ PORT_USI |=  (1 << PIN_USI_SDA); }
#define USI_SET_SDA_LOW()			{ PORT_USI &= ~(1 << PIN_USI_SDA); }

#define USI_SET_SCL_OUTPUT()		{ DDR_USI |=  (1 << PIN_USI_SCL); }
#define USI_SET_SCL_INPUT() 		{ DDR_USI &= ~(1 << PIN_USI_SCL); }

#define USI_SET_SCL_HIGH()			{ PORT_USI |=  (1 << PIN_USI_SCL); }
#define USI_SET_SCL_LOW()			{ PORT_USI &= ~(1 << PIN_USI_SCL); }

#define USI_I2C_WAIT_HIGH()			{ _delay_us(I2C_THIGH); }
#define USI_I2C_WAIT_LOW()			{ _delay_us(I2C_TLOW);  }

void twi_init();
char twi_transfer(char USISR_temp);
char twi_transmission(char *msg, char msg_size);


#endif /* USI_H_ */