/*
 * Sensor.h
 *
 * Created: 12-04-2022 10:05:40
 *  Author: sylle
 */

#ifndef SENSOR_H_
#define SENSOR_H_
#include "header.h"
/* Optic */
#define PINCNY PINA3
void init_OPTIC ( );

/* LDR */
#define PINLDR PINA6
void init_LDR ( );
uint8_t read_LDR();

/* MIC */
#define PINMIC PINA7
void init_MIC ( );

/* Fugt */
#define PINFUG PINA0
void init_FUG ( );

/* Temp */
void	 init_temp ( );
uint16_t temp_celcius ( );

/*IR sensor*/
#define PINIR PINA2
void	init_IR ( );
uint8_t read_ir ( );

#endif /* SENSOR_H_ */
