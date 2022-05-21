/*
 * com.c
 *
 * Created: 18-05-2022 09:52:47
 *  Author: dense
 */

#include "com.h"

bool signal_flag = false;

void com_init ( ) {
  PORT_COM &= ~(1 << PIN_COM_0);
  PORT_COM &= ~(1 << PIN_COM_1);

  // Enable interupts on COM protocol to allow for sleep inbetween requests
  /* CANNOT GET IT WAKE UP PROPERLY (MAYBE TO SLOW?) */
  // PCICR |= (1 << PCIE1);
  // PCMSK1 |= (1 << PIN_COM_1) | (1 << PIN_COM_0);
}

void com_send_signal (void) {
  signal_flag = !signal_flag;
  if (signal_flag) {
	DDR_COM |= (1 << PIN_COM_0);
	DDR_COM |= (1 << PIN_COM_1);
  }

  PORT_COM |= (1 << PIN_COM_0);
  PORT_COM |= (1 << PIN_COM_1);
  _delay_ms (COM_SPEED);
  PORT_COM &= ~(1 << PIN_COM_0);
  PORT_COM &= ~(1 << PIN_COM_1);
  _delay_ms (COM_SPEED);

  if (!signal_flag) {
	DDR_COM &= ~(1 << PIN_COM_0);
	DDR_COM &= ~(1 << PIN_COM_1);
  }
}

uint8_t com_get_data (void) {
  switch (COM & ((1 << PIN_COM_1) | (1 << PIN_COM_0))) {
	case ((1 << PIN_COM_0) | (1 << PIN_COM_1)):
	  return COM_SIGNAL;
	case (1 << PIN_COM_0):
	  return COM_ZERO;
	case (1 << PIN_COM_1):
	  return COM_ONE;
	default:
	  return COM_FLAT;
  }
}

uint8_t com_wait_for_next (void) {
  while (com_get_data ( ) != COM_FLAT)
	;
  while (com_get_data ( ) == COM_FLAT)
	;
  return com_get_data ( );
}

void com_wait_for_signal (void) {
  while (com_get_data ( ) == COM_SIGNAL)
	;
  while (com_get_data ( ) == COM_FLAT)
	;
}

void com_get_string (char* str) {
  uint8_t i = 8;

  while (true) {
	uint8_t next = com_wait_for_next ( );

	if (i == 0) {
	  i = 8;
	  str++;
	}

	switch (next) {
	  case COM_ZERO:
		_delay_ms (COM_SPEED / 4);
		i--;
		*str &= ~(1 << i);
		break;
	  case COM_ONE:
		_delay_ms (COM_SPEED / 4);
		i--;
		*str |= (1 << i);
		break;
	  case COM_SIGNAL:
		_delay_ms (COM_SPEED * 2);
		return;
	}
  }
}

void private_com_send_bit (bool b, bool passthrough) {
  if (!passthrough)
	com_send_signal ( );

  if (b)
	PORT_COM |= (1 << PIN_COM_1);
  else
	PORT_COM |= (1 << PIN_COM_0);
  _delay_ms (COM_SPEED);
  PORT_COM &= ~((1 << PIN_COM_0) | (1 << PIN_COM_1));
  _delay_ms (COM_SPEED);

  if (!passthrough)
	com_send_signal ( );
}

void private_com_send_char (char c, bool passthrough) {
  if (!passthrough)
	com_send_signal ( );
  for (uint8_t i = 8; i > 0; i--)
	private_com_send_bit (c & (1 << (i - 1)), true);
  if (!passthrough)
	com_send_signal ( );
}

void private_com_send_string (const char* str, bool passthrough) {
  if (!passthrough)
	com_send_signal ( );
  do
	private_com_send_char (*str, true);
  while (str++ && *str != '\0');
  if (!passthrough)
	com_send_signal ( );
}

char buff[10];
// Shorthands
void com_send_bit (bool b) { private_com_send_bit (b, false); }
void com_send_char (char c) { private_com_send_char (c, false); }
void com_send_string (const char* str) { private_com_send_string (str, false); }
void com_send_num (uint16_t num) { com_send_string (utoa (num, buff, 10)); }
