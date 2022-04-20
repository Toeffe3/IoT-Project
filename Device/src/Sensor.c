/*
 * Sensor.c
 *
 * Created: 12-04-2022 09:49:24
 *  Author: sylle
 */
#include "Sensor.h"
#include "header.h"

void init_OPTIC ( ) {

  DDRA &= ~(1 << PINCNY); // Set optic sensor as input

  ADMUX &= ~((1 << REFS1) & (1 << REFS0));				// Use 2.56V AREF
  ADMUX |= (0 << MUX2) | (1 << MUX1) | (1 << MUX0);		// A3
  ADMUX |= (1 << ADLAR);								// Left adjust result
  ADCSRA |= (0 << ADPS2) | (1 << ADPS1) | (0 << ADPS0); // Prescale 4
  ADCSRA |= (1 << ADEN) | (1 << ADATE) | (1 << ADIE);   // Enable ADC, ADC auto
														// trigger and ADC
														// interrupt

  ADCSRA |= (1 << ADSC); // Start ADC
}

void init_LDR ( ) {

  DDRA &= ~(1 << PINLDR); // Set LDR as input

  ADMUX &= ~((1 << REFS1) & (1 << REFS0)); // Use 2.56V AREF
  ADMUX |= (1 << MUX3) | (0 << MUX2) | (0 << MUX1) | (1 << MUX0); // A6
  ADMUX |= (1 << ADLAR);								// left adjust result
  ADCSRA |= (0 << ADPS2) | (0 << ADPS1) | (0 << ADPS0); // Prescale 2
  ADCSRA |= (1 << ADEN) | (1 << ADATE) | (1 << ADIE);   // Enable ADC, ADC auto
														// trigger and ADC
														// interrupt

  ADCSRA |= (1 << ADSC); // Start ADC
}

void init_MIC ( ) {

  DDRA &= ~(1 << PINMIC); // Set microphone as input

  ADMUX &= ~((1 << REFS1) & (1 << REFS0)); // Use 2.56V AREF
  ADMUX |= (1 << MUX3) | (0 << MUX2) | (1 << MUX1) | (0 << MUX0); // A7
  ADMUX |= (1 << ADLAR);								// left adjust result
  ADCSRA |= (0 << ADPS2) | (0 << ADPS1) | (0 << ADPS0); // Prescale 2
  ADCSRA |= (1 << ADEN) | (1 << ADATE) | (1 << ADIE);   // Enable ADC, ADC auto
														// trigger and ADC
														// interrupt

  ADCSRA |= (1 << ADSC); // Start ADC
}

void init_FUG ( ) {
  DDRA &= ~(1 << PINFUG); // Set moisture sennsor as input
}

void init_temp ( ) {

  ADMUX &= ~((01 << REFS1) & (1 << REFS0)); // Use 1.1V AREF
  ADMUX |= (1 << MUX3) | (0 << MUX2) | (1 << MUX1) | (1 << MUX0); // Temp
  ADMUX |= (1 << ADLAR);								// left adjust result
  ADCSRA |= (0 << ADPS2) | (0 << ADPS1) | (0 << ADPS0); // Prescale 2
  ADCSRA |= (1 << ADEN) | (1 << ADATE) | (1 << ADIE);   // Enable ADC, ADC auto
														// trigger and ADC
														// interrupt

  ADCSRA |= (1 << ADSC); // Start ADC
}

void init_IR ( ) { DDRA &= ~(1 << PINIR); }

uint8_t read_ir ( ) { return (PINA & (1 << PINIR)) != 0; }

uint16_t temp_celcius ( ) {
  uint16_t data = ADC;
  return data - 273;
}
