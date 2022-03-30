/*
 * rtc.h
 *
 * Created: 30-03-2022 13:14:49
 *  Author: Tobia
 */ 


#ifndef RTC_H_
#define RTC_H_


#define OSC_32KHZ = 1;
#define OSC_RC = 0;
#define PRESCALER = 0b0001;
#define TOP_VAL = 6 000 000;
#define ENDABLE_RTC_INTERRUPT = 1;
#define DISABLE_RTC_INTERRUPT = 1;


#endif /* RTC_H_ */


void rtc_init(bool, uint8_t, uint32_t);

void rtc_endable_interrupt(void);

void rtc_disable_interrupt(void);