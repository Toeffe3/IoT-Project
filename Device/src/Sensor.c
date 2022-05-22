/*
 * sensor.c
 *
 * Created: 12-04-2022 09:49:24
 *  Author: sylle
 */

#include "sensor.h"

bool btn;

void IRD_init (void) {
  // Configure IR movement detector as input
  DDR_IRD = (0 << PIN_IRD);
}

bool IRD_read (void) { return (IRD & (1 << PIN_IRD)) != 0; }

void LDR_init (void) {
  // Configure LDR as input
  DDR_LDR = (0 << PIN_LDR);
  ADMUX   = (1 << REFS1) | (1 << REFS0) // Use 2.56V AREF
		  | (0 << ADLAR) | 0b00110;		// Right adjust, PA6
  ADCSRA = (1 << ADEN) | (0 << ADSC) |  // Enable, Pause
		   (0 << ADATE) | (0 << ADIF) | // No auto
		   (0 << ADIE) | (0 << ADPS2) | // No interupt
		   (0 << ADPS1) | (1 << ADPS0); // Prescale 2
}

uint16_t LDR_read (void) {
  ADCSRA |= (1 << ADSC); // Start ADC
  while (ADCSRA & (1 << ADSC))
	; // Wait for conversion
  return ADC;
}

uint16_t HUM_wait_for_high (void) {
  uint16_t timeout = DHT_TIMEOUT;
  while (PORT_HUM & (1 << PIN_HUM) != 0)
	if (!timeout--)
	  break;
  return timeout;
}

uint16_t HUM_wait_for_low (void) {
  uint16_t timeout = DHT_TIMEOUT;
  while (PORT_HUM & (1 << PIN_HUM) == 0)
	if (!timeout--)
	  break;
  return timeout;
}

bool DHT_get_one_bit (void) {
  if (!HUM_wait_for_low ( ))
	return false;
  uint8_t timediff = HUM_wait_for_high ( );
  if (timediff == 0)
	return 0;
  return (timediff >= 40 * F_CPU / 1000000); // ~40us
}

void HUM_init (void) {
  DDR_HUM  = (1 << PIN_HUM);  // OUTPUT
  PORT_HUM = ~(1 << PIN_HUM); // LOW
}

uint8_t HUM_get (uint16_t *temperature, uint16_t *humidity) {
  uint16_t timeout  = 0;
  uint8_t  checksum = 0;
  uint8_t  res;

  uint8_t buffer[5]; // 8*5 = 40

  // Start transaction
  DDR_HUM |= (1 << PIN_HUM);   // OUTPUT
  PORT_HUM &= ~(1 << PIN_HUM); // LOW
  _delay_ms (18);			   // 18ms
  DDR_HUM &= ~(1 << PIN_HUM);  // INPUT

  HUM_wait_for_low ( );
  HUM_wait_for_high ( );

  // Get bits
  for (uint8_t i = 0; i < 5; i++) {
	uint8_t temp = 0;

	for (uint8_t j = 8; j > 0; j--)
	  temp = DHT_get_one_bit ( ) << j;

	buffer[i] = temp;
  }

  *humidity	= (buffer[0] << 8) + buffer[1];
  *temperature = (buffer[2] << 8) + buffer[3];

  if ((uint8_t)*humidity + (uint8_t)*temperature == buffer[4])
	return 0;
  else
	return 3;
}

void MIC_init (void) {
  // Configure MIC as input
  DDR_LDR = (0 << PIN_MIC);
  ADMUX   = (1 << REFS1) | (1 << REFS0) // Use 2.56V AREF
		  | (0 << ADLAR) | 0b00110;		// Right adjust, PA6
  ADCSRA = (1 << ADEN) | (0 << ADSC) |  // Enable, Pause
		   (0 << ADATE) | (0 << ADIF) | // No auto
		   (0 << ADIE) | (0 << ADPS2) | // No interupt
		   (1 << ADPS1) | (0 << ADPS0); // Prescale 4
}

uint16_t MIC_read (void) {
  ADCSRA |= (1 << ADSC); // Start ADC
  while (ADCSRA & (1 << ADSC))
	; // Wait for conversion
  return ADC;
}

void CNY_init (void) {
  // Configure optic sensor as input
  DDR_CNY = ~(1 << PIN_CNY);
  ADMUX   = (1 << REFS1) | (1 << REFS0) // Use 2.56V AREF
		  | (0 << ADLAR) | 0b00011;		// Right adjust, PA3
  ADCSRA = (1 << ADEN) | (0 << ADSC) |  // Enable, Pause
		   (0 << ADATE) | (0 << ADIF) | // No auto
		   (0 << ADIE) | (0 << ADPS2) | // No interupt
		   (1 << ADPS1) | (0 << ADPS0); // Prescale 4
}

uint16_t CNY_read (void) {
  ADCSRA |= (1 << ADSC); // Start ADC
  while (ADCSRA & (1 << ADSC))
	; // Wait for conversion
  return ADC;
}

void BUT_init ( ) {
  DDR_BUT = (0 << PIN_BUT);
  PCICR   = (1 << PCIE1);
  PCMSK1  = (1 << PCINT9);
}

void TEMP_init (void) {
  ADMUX = (0 << REFS1) | (1 << REFS0)   // Use 1.1V AREF
		  | (0 << ADLAR) | 0b01011;		// Right adjust, Temperature sensor
  ADCSRA = (1 << ADEN) | (0 << ADSC) |  // Enable, Pause
		   (0 << ADATE) | (0 << ADIF) | // No auto
		   (0 << ADIE) | (0 << ADPS2) | // No interupt
		   (1 << ADPS1) | (0 << ADPS0); // Prescale 4
}

float TEMP_read (void) {
  ADCSRA |= (1 << ADSC);		   // Start ADC
  float k = 1.05, offset = -272.9; // Constants
  while (ADCSRA & (1 << ADSC))
	;						 // Wait for conversion
  return (k * ADC) + offset; // calculate
}

// ISR (PCINT1_vect) { btn = (BUT & (1 << PIN_BUT)) != 0; }
