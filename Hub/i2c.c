/*
 * i2c.c
 *
 *  Created on: 16. maj 2022
 *      Author: Rainbow Dash
 */

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "i2c.h"

void i2c_init(void)
{
#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
    uint32_t ui32SysClock;
#endif

    //
    // Set the clocking to run directly from the external crystal/oscillator.
    // TODO: The SYSCTL_XTAL_ value must be changed to match the value of the
    // crystal on your board.
    //
#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
    ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_16MHZ |
                                       SYSCTL_OSC_MAIN |
                                       SYSCTL_USE_OSC), 25000000);
#else
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
    SYSCTL_XTAL_16MHZ);
#endif

    //
    // The I2C0 peripheral must be enabled before use.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C3);

    //
    // For this example I2C0 is used with PortB[3:2].  The actual port and
    // pins used may be different on your part, consult the data sheet for
    // more information.  GPIO port B needs to be enabled so these pins can
    // be used.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    //
    // Configure the pin muxing for I2C0 functions on port B2 and B3.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PD0_I2C3SCL);
    GPIOPinConfigure(GPIO_PD1_I2C3SDA);

    //
    // Select the I2C function for these pins.  This function will also
    // configure the GPIO pins pins for I2C operation, setting them to
    // open-drain operation with weak pull-ups.  Consult the data sheet
    // to see which functions are allocated per pin.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeI2CSCL(GPIO_PORTD_BASE, GPIO_PIN_6);
    GPIOPinTypeI2C(GPIO_PORTD_BASE, GPIO_PIN_7);

    //
    // Enable loopback mode.  Loopback mode is a built in feature that is
    // useful for debugging I2C operations.  It internally connects the I2C
    // master and slave terminals, which effectively let's you send data as
    // a master and receive data as a slave.
    // NOTE: For external I2C operation you will need to use external pullups
    // that are stronger than the internal pullups.  Refer to the datasheet for
    // more information.
    //
    I2CLoopbackEnable(I2C3_BASE);

    //
    // Enable and initialize the I2C0 master module.  Use the system clock for
    // the I2C0 module.  The last parameter sets the I2C data transfer rate.
    // If false the data rate is set to 100kbps and if true the data rate will
    // be set to 400kbps.  For this example we will use a data rate of 100kbps.
    //
#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
    I2CMasterInitExpClk(I2C3_BASE, ui32SysClock, false);
#else
    I2CMasterInitExpClk(I2C3_BASE, SysCtlClockGet(), false);
#endif

    //
    // Enable the I2C0 slave module. This module is enabled only for testing
    // purposes.  It does not need to be enabled for proper operation of the
    // I2Cx master module.
    //
    I2CSlaveEnable(I2C3_BASE);

    //
    // Set the slave address to SLAVE_ADDRESS.  In loopback mode, it's an
    // arbitrary 7-bit number (set in a macro above) that is sent to the
    // I2CMasterSlaveAddrSet function.
    //
    I2CSlaveInit(I2C3_BASE, SLAVE_ADDRESS);

    //
    // Tell the master module what address it will place on the bus when
    // communicating with the slave.  Set the address to SLAVE_ADDRESS
    // (as set in the slave module).  The receive parameter is set to false
    // which indicates the I2C Master is initiating a writes to the slave.  If
    // true, that would indicate that the I2C Master is initiating reads from
    // the slave.
    //
    I2CMasterSlaveAddrSet(I2C3_BASE, SLAVE_ADDRESS, false);

}

void i2c_send_char(const char chr)
{
    I2CMasterDataPut(I2C3_BASE, chr);
    while (I2CMasterBusy(I2C3_BASE))
        ;
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_SINGLE_SEND);
}

void i2c_send_string(const char str[], uint16_t size)
{
    uint16_t i;
    for(i = 0; i <= size; i++){
        I2CMasterDataPut(I2C3_BASE, str[i]);
        while (I2CMasterBusy(I2C3_BASE)){};
        //uart0_println("data ");
        uart0_print(str[i]);
    }
    uart0_println("123 ");


//    while (*str != '\0')
//    {
//        I2CMasterDataPut(I2C3_BASE, *str);
//        uart0_print(*str);
//        while (I2CMasterBusy(I2C3_BASE))
//            ;
//        str++;
//        uart0_println(" ");
//    }
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_SINGLE_SEND);
}

void i2c_read()
{
    char* str;
    while (*str != '\0')
    {
        *str = I2CSlaveDataGet(I2C3_BASE);
        uart0_print(*str);
        while (I2CMasterBusy(I2C3_BASE));
        str++;
        uart0_println(" ");
    }
}

void i2c_task(void)
{
    i2c_init();
    while (1)
    {
        // Main code
        const char besked[4] = "Test";
        i2c_send_string(besked, 4);
        //while (!(I2CSlaveStatus(I2C3_BASE) & I2C_SLAVE_ACT_RREQ)){};
        //i2c_read();



        // Delay between exe
        vTaskDelay(500 / portTICK_RATE_MS);

    }
}

