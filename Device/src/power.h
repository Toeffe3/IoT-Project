/*
 * power.h
 *
 * Created: 14-05-2022 15:31:36
 *  Author: dense
 */

#ifndef POWER_H_
#define POWER_H_

#include "header.h"

// Modules that can be powered reduced
#define PWR_ADC 0b00000001
#define PWR_USI 0b00000010
#define PWR_TI0 0b00000100
#define PWR_TI1 0b00001000
// This will prevent programming the chip, leaved out for safty
//#define PWR_SPI 0b00010000
#define PWR_LIN 0b00100000

// Sleep modes
#define POWER_HIGH 4
#define POWER_REDUCED SLEEP_MODE_IDLE
#define POWER_MEDIUM SLEEP_MODE_ADC
#define POWER_LOW SLEEP_MODE_PWR_DOWN
#define POWER_MINIMAL SLEEP_MODE_PWR_SAVE

#define sleep( )                                                               \
  do {                                                                         \
	__asm__ __volatile__("sleep"                                               \
						 "\n\t" ::);                                           \
  } while (0)

#define reset( )                                                               \
  do {                                                                         \
	__asm__ __volatile__("jmp 0x0000"                                          \
						 "\n\t" ::);                                           \
  } while (0)

ISR (TIMER0_COMPA_vect)

void power_init (uint8_t mode, bool bod_detection, uint8_t reduce_module);
void power_down (void);

#endif /* POWER_H_ */
