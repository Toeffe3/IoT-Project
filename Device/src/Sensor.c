/*
 * sensor.c
 *
 * Created: 12-04-2022 09:49:24
 *  Author: sylle
 */

#include "sensor.h"

void IRD_init (void) {
  // Configure IR movement detector as input
  DDR_IRD &= ~(1 << PIN_IRD);
}

bool IRD_read (void) { return (IRD & (1 << PIN_IRD)) != 0; }

void LDR_init (void) {
  // Configure LDR as input
  DDR_LDR &= ~(1 << PIN_LDR);
  ADMUX &= ~((1 << REFS1) & (1 << REFS0)); // Use 2.56V AREF
  ADMUX |= (0 << MUX3) | (1 << MUX2) | (1 << MUX1) | (0 << MUX0); // A6
  ADMUX |= (0 << ADLAR);								// Right adjust result
  ADCSRA |= (0 << ADPS2) | (0 << ADPS1) | (0 << ADPS0); // Prescale 2
  ADCSRA |= (1 << ADEN) | (1 << ADATE) | (1 << ADIE);   // Enable, auto trigger
														// and interrupt
  ADCSRA |= (1 << ADSC);								// Start ADC
}

uint16_t LDR_read (void) { return ADC; }

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
  DDR_HUM |= (1 << PIN_HUM);   // OUTPUT
  PORT_HUM &= ~(1 << PIN_HUM); // LOW
  
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
  // Configure microphone as input
  DDR_MIC &= ~(1 << PIN_MIC);
  //AC setup
  	ADCSRB |= (1 << ACME); //Positive input
  // ADC setup
  ADMUX |=  (1 << MUX4)| (1 << MUX3) | (0 << MUX2) | (1 << MUX1) | (1 << MUX0); // A6 gain x20

}

uint16_t MIC_read (void) { return ACO; }

void CNY_init (void) {
  // Configure optic sensor as input
  DDR_CNY &= ~(1 << PIN_CNY);
  ADMUX &= ~((1 << REFS1) & (1 << REFS0));				// Use 2.56V AREF
  ADMUX |= (0 << MUX2) | (1 << MUX1) | (1 << MUX0);		// A3
  ADMUX |= (0 << ADLAR);								// Right adjust result
  ADCSRA |= (0 << ADPS2) | (1 << ADPS1) | (0 << ADPS0); // Prescale 4
  ADCSRA |= (1 << ADEN) | (1 << ADATE) | (1 << ADIE);   // Enable, trigger and
														// interrupt
  ADCSRA |= (1 << ADSC);								// Start ADC
}

uint16_t CNY_read (void) { return ADC; }

void BUT_init ( ) {
  DDR_BUT &= ~(1 << PIN_BUT);
  PCICR |= (1 << PCIE1);
  PCMSK1 |= (1 << PCINT9);
}

bool tryk = 0;
ISR (PCINT1_vect) { tryk = (BUT & (1 << PIN_BUT)) != 0; }
void TEMP_init(void){
	  ADMUX &= ~((0 << REFS1) & (1 << REFS0));				// Use 1.1V AREF
	  ADMUX |= (1 << MUX3)| (0 << MUX2) | (1 << MUX1) | (1 << MUX0); // Temp sensor
	  ADMUX |= (0 << ADLAR);								// Right adjust result
	  ADCSRA |= (0 << ADPS2) | (0 << ADPS1) | (0 << ADPS0); // Prescale 2
	  ADCSRA |= (1 << ADEN) | (1 << ADATE) | (1 << ADIE);   // Enable, trigger and
	  // interrupt
	  ADCSRA |= (1 << ADSC);								// Start ADC
	  
}
 float TEMP_read(void) {
	 float k = 1.0, offset = -272.9,
	T = k * ((ADCH << 8) | ADCL) + offset;
	 return T;
 }
