#include <pico/stdlib.h>


#ifndef PCSB_RTC_H
#define PCSB_RTC_H

static const char dayOfWeekLUT[7][4] = {
	{"Mon\0"},
	{"Tue\0"},
	{"Wed\0"},
	{"Thu\0"},
	{"Fri\0"},
	{"Sat\0"},
	{"Sun\0"}
};

typedef union {
	uint32_t raw;
	struct {
		uint8_t dayOfWeek;
		uint8_t day;
		uint8_t month;
		uint8_t year;
	};
} PCSB_RTC_DATE_STRUCT;

typedef union {
	uint32_t raw;
	struct {
		uint8_t hours;
		uint8_t minutes;
		uint8_t secondes;
		//uint8_t;
	};
} PCSB_RTC_TIME_STRUCT;


int pcsb_rtc_read_date(PCSB_RTC_DATE_STRUCT* const out_rtc_s);
int pcsb_rtc_read_time(PCSB_RTC_TIME_STRUCT* const out_rtc_s);
int pcsb_rtc_set_date(const PCSB_RTC_DATE_STRUCT* const in_rtc_s);
int pcsb_rtc_set_time(const PCSB_RTC_TIME_STRUCT* const in_rtc_s);

#endif  /* PCSB_RTC_H */