/*
 * usb.cpp
 *
 * Created: 06-04-2022 11:44:32
 *  Author: Tobia
 */ 

#include "usb.h"


// Note:
// The USB_VBOF and USB_ID pins are multiplexed with I/O Controller lines and may also be
// multiplexed with lines of other peripherals. In order to use them with the USB, the user must first
// configure the I/O Controller to assign them to their USB peripheral functions.
// If USB_ID is used, the I/O Controller must be configured to enable the internal pull-up resistor of its pin.
// If USB_VBOF or USB_ID is not used by the application, the corresponding pin can be used for other purposes by the I/O Controller or by other peripherals.

// The 48MHz USB clock is generated by a dedicated generic clock from the Power Manager.
// Before using the USB, the user must ensure that the USB generic clock (GCLK_USBB) is enabled at 48MHz in the Power Manager.

// If the USB_ID pin is not connected to ground, the USB_ID Pin State bit in the General Status
// register (USBSTA.ID) is set (the internal pull-up resistor of the USB_ID pin must be enabled by
// the I/O Controller) and device mode is engaged.


usb_init(){
	
	
	
	
}