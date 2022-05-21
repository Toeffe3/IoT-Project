#include "lcd.h"

void delay_ms(uint32_t t) {
	vTaskDelay(t / portTICK_RATE_MS);
}

// Tell the LCD that the datalines is populated
void lcd_signal() {
	LCD_CTRL |= LCD_EN;
	delay_ms(1);
	LCD_CTRL &= ~(LCD_EN);  // Toggle ready signal
}

// Tell the LCD that the next 8 bytes is an instruction
void lcd_instruct(void) {
	LCD_CTRL &= ~(LCD_EN | LCD_RS);
	delay_ms(10);
}

// Tell the LCD that the next 8 bytes is an charecter
void lcd_write(void) {
	LCD_CTRL &= ~(LCD_EN);
	LCD_CTRL |= LCD_RS;
	delay_ms(10);
}

// Send 8 bytes to the display
void lcd_send(const uint8_t data) {
	LCD_DATA = data;
	lcd_signal();
	LCD_DATA = data << 4;
	lcd_signal();
}

void swap(char* x, char* y) {
	char t = *x;
	*x = *y;
	*y = t;
}

char* reverse(char* buffer, int i, int j) {
	while ( i < j )
		swap(&buffer [i++], &buffer [j--]);
	return buffer;
}

void lcd_utoa(uint16_t n) {
	char buffer [6];
	uint8_t i = 0;
	while ( n ) {
		buffer [i++] = (n % 10) + '0';
		n /= 10;
	}
	if ( i == 0 ) buffer [i++] = '0';
	buffer [i] = '\0';
	xStreamBufferSend(imagbuff, reverse(buffer, 0, i - 1), i, 0);
}

size_t lcd_write_buffer(const char* data) {
	return xStreamBufferSend(imagbuff, data, strlen(data), 0);
}

size_t lcd_write_buffer_size(const char* data, size_t l) {
	return xStreamBufferSend(imagbuff, data, l, 0);
}

uint8_t POS_Y(uint8_t pos) {
	return (pos - 0x80) / 64;
}

void lcd_init(void) {
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC | SYSCTL_RCGC2_GPIOD;
	delay_ms(10);
	// Set control pins as output
	GPIO_PORTC_DIR_R |= LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7;
	GPIO_PORTC_DEN_R |= LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7;
	GPIO_PORTC_PUR_R |= LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7;
	GPIO_PORTD_DIR_R |= LCD_RS | LCD_EN | LCD_RW;
	GPIO_PORTD_DEN_R |= LCD_RS | LCD_EN | LCD_RW;
	GPIO_PORTD_PUR_R |= LCD_RS | LCD_EN | LCD_RW;
	delay_ms(1000);  // Let display caps charge up
	lcd_instruct();
	lcd_send(0b00101000);  //4-bit mode, 2 lines, 5x8 font
	lcd_instruct();
	lcd_send(0b00001101);  //Display on, cursor off, blinking on
	lcd_instruct();
	lcd_send(0b00000110);  //Increment, don't scroll scroll
	lcd_instruct();
	lcd_send(LCD_CLEAR);  //Increment, don't scroll scroll
}

void lcd_task(void* pvParameters) {

	imagbuff = xStreamBufferGenericCreate(LCD_BUFFER_SIZE, LCD_BUFFER_SIZE, pdFALSE);
	lcd_init();

	uint8_t data [LCD_BUFFER_SIZE], lcdpos = LCD_POS(0, 0), mode = 0;

	while ( 1 ) {
		if ( xStreamBufferReceive(imagbuff, &data, 1, 100) == pdPASS ) {
			delay_ms(10);
			switch ( *data ) {
				case SCREEN_CLEAR_CHAR:
					lcd_instruct();
					lcd_send(LCD_CLEAR);
					lcdpos = LCD_POS(0, 0);
					lcd_write();
					mode = 0;
					break;
				case SCREEN_POS_CHAR:
					mode = 1;
					break;
				default: {
					switch ( mode ) {
						case 1:
							if ( *data == LCD_POS(16, 0) || *data == LCD_POS(16, 1) ) break;
							lcdpos = *data;
							lcd_instruct();
							lcd_send(lcdpos);
							delay_ms(10);
							mode = 0;
							break;
						default: {
							if ( POS_X(lcdpos) >= 16 ) {
								lcdpos = LCD_POS(0, (POS_Y(lcdpos) + 1) % 2);
								lcd_instruct();
								lcd_send(lcdpos);
								delay_ms(10);
							}
							lcd_write();
							lcd_send(*data);
							lcdpos++;
						}
					}
				}
			}
		}
	}
}
