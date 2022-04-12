/*
 * Sensor.h
 *
 * Created: 12-04-2022 10:05:40
 *  Author: sylle
 */ 


#ifndef SENSOR_H_
#define SENSOR_H_
/* Optic */
#define PINCNY PINA5
void init_OPTIC();

/* LDR */
#define PINLDR PINA3
void init_LDR();

/* MIC */
#define PINMIC PINA2
void init_MIC();

/* Fugt */
#define  PINFUG PINA4
void init_FUG();

/* Temp */
void init_temp();
uint16_t temp_celcius();

#endif /* SENSOR_H_ */