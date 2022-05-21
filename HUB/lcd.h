/*****************************************************************************
 * University of Southern Denmark
 * Embedded Programming (EMP)
 *
 * MODULENAME.: lcd.h
 *
 * PROJECT....: Assignment 7
 *
 *****************************************************************************/

#ifndef LCD_H_
#define LCD_H_

/***************************** Include files *******************************/
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "FreeRTOS.h"
#include "tm4c123gh6pm.h"
#include "task.h"

#include "systick_frt.h"
#include "stream_buffer.h"

/*****************************    Defines    *******************************/
#define LF              0x0A
#define FF              0x0C
#define CR              0x0D
#define ESC             0x1B
#define LCD_CTRL        GPIO_PORTD_DATA_R
#define LCD_RW          0b00000010
#define LCD_RS          0b00000100
#define LCD_EN          0b00001000
#define LCD_DATA        GPIO_PORTC_DATA_R
#define LCD_D4          0b00010000
#define LCD_D5          0b00100000
#define LCD_D6          0b01000000
#define LCD_D7          0b10000000
#define LCD_CLEAR       0b00000001// Clear the display
#define LCD_HOME        0b00000010 // Set cursor position to 0.0
#define LCD_BUFFER_SIZE 16*2
#define SCREEN_CLEAR    "§"
#define SCREEN_POS      "¤"
#define SCREEN_CLEAR_CHAR '§'
#define SCREEN_POS_CHAR '¤'
// Macro to convert line (y) and column (x) to lcd encoding
#define LCD_POS(x,y)    0x80 + (x) + (64*(y))
// Macro to convert lcd encoded pos to an column (x value)
#define POS_X(pos) ((pos) - 0x80) - (64*POS_Y((pos)))

/*****************************   Variables   *******************************/
StreamBufferHandle_t imagbuff;

/*****************************   Functions   *******************************/
// Types required for proper conversion MACRO is not good enough:
uint8_t POS_Y(uint8_t pos);

// Send a number to display by first converting it
void lcd_utoa(const uint16_t num);

// Write a string to the display buffer max
size_t lcd_write_buffer(const char* data);
size_t lcd_write_buffer_size(const char* data, size_t l);
void lcd_task(void* pvParameters);

#endif /* LCD_H_ */
