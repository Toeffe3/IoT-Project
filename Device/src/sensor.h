/******************************************************************************/
/* Project:    Device                                                         */
/* File:       src/sensor.h                                                   */
/* Decription: Device sensor control header                                   */
/******************************************************************************/

#ifndef SENSOR_H_
#define SENSOR_H_

/***************************** Include files *******************************/
#include "header.h"

/*****************************    Defines    *******************************/
#define DHT_TIMEOUT 1000

// Infrared movement detector
#define PORT_IRD PORTA
#define DDR_IRD DDRA
#define PIN_IRD PINA2
#define IRD PINA

// Light dependent resistor
#define PORT_LDR PORTA
#define DDR_LDR DDRA
#define PIN_LDR PINA6
#define LDR PINA

// Humidity sensor
#define PORT_HUM PORTA
#define DDR_HUM DDRA
#define PIN_HUM PINA0
#define HUM PINA

// Microphone
#define PORT_MIC PORTA
#define DDR_MIC DDRA
#define PIN_MIC PINA6
#define MIC PINA

// CNY70 Optical sensor
#define PORT_CNY PORTA
#define DDR_CNY DDRA
#define PIN_CNY PINA3
#define CNY PINA

// Button D1
#define PORT_BUT PORTB
#define DDR_BUT DDRB
#define PIN_BUT PINB1
#define BUT PINB

/*****************************   Variables   *******************************/
extern bool btn;

/*****************************   Functions   *******************************/
void	 IRD_init (void);
bool	 IRD_read (void);
void	 LDR_init (void);
uint16_t LDR_read (void);
uint16_t HUM_wait_for_high (void);
uint16_t HUM_wait_for_low (void);
bool	 DHT_get_one_bit (void);
void	 HUM_init (void);
uint8_t  HUM_get (uint16_t *temperature, uint16_t *humidity);
void	 MIC_init (void);
uint16_t MIC_read (void);
void	 CNY_init (void);
uint16_t CNY_read (void);
void	 BUT_init ( );
void	 TEMP_init (void);
float	TEMP_read (void);
#endif /* SENSOR_H_ */
