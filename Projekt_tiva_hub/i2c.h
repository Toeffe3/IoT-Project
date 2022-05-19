/*
 * i2c.h
 *
 *  Created on: 16. maj 2022
 *      Author: Rainbow Dash
 */

#ifndef I2C_H_
#define I2C_H_

#define NUM_I2C_DATA 20 			// Number of I2C data packets to send.
// Set the address for slave module. This is a 7-bit address sent in the
// following format:
//                      [A6:A5:A4:A3:A2:A1:A0:RS]
//
// A zero in the "RS" position of the first byte means that the master
// transmits (sends) data to the selected slave, and a one in this position
// means that the master receives data from the slave.
#define SLAVE_ADDRESS 0x3C 		// Set the address for slave module
uint32_t pui32DataTx[NUM_I2C_DATA];
uint32_t pui32DataRx[NUM_I2C_DATA];

void i2c_task(void);

#endif /* I2C_H_ */
