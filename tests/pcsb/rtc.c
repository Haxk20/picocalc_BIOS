#include "rtc.h"
#include <hardware/i2c.h>
#include "pcsb_int.h"


static uint8_t byte2bcd(uint8_t val) {
    uint32_t bcdhigh = 0U;

    while (val >= 10U) {
        bcdhigh++;
        val -= 10U;
    }

    return ((uint8_t)(bcdhigh << 4U) | val);
}

static uint8_t bcd2byte(uint8_t val) {
    uint32_t tmp = 0U;
    tmp = ((uint8_t)(val & 0xF0) >> 4U) * 10U;
    return (tmp + (val & 0x0F));
}

int pcsb_rtc_read_date(PCSB_RTC_DATE_STRUCT* const out_rtc_s) {
    uint8_t buff[5] = {0};
    unsigned char msg[3];

    if (pcsb_is_init() == 0 || out_rtc_s == NULL) return -1;
    msg[0] = pcsb_get_addr_table()->reg_rtc_date;

    if (_int_i2c_op(msg, 1, buff, 5) != 0)
        return -1;

    /*out_rtc_s->year = bcd2byte(buff[1]);
    out_rtc_s->month = bcd2byte(buff[2]);
    out_rtc_s->day = bcd2byte(buff[3]);*/
    out_rtc_s->year = buff[1];
    out_rtc_s->month = buff[2];
    out_rtc_s->day = buff[3];
    out_rtc_s->dayOfWeek = buff[4];
   
    return 0;
}

int pcsb_rtc_read_time(PCSB_RTC_TIME_STRUCT* const out_rtc_s) {
    uint8_t buff[4] = {0};
    unsigned char msg[3];

    if (pcsb_is_init() == 0 || out_rtc_s == NULL) return -1;
    msg[0] = pcsb_get_addr_table()->reg_rtc_time;

    if (_int_i2c_op(msg, 1, buff, 4) != 0)
        return -1;

    /*out_rtc_s->hours = bcd2byte(buff[1]);
    out_rtc_s->minutes = bcd2byte(buff[2]);
    out_rtc_s->secondes = bcd2byte(buff[3]);*/
    out_rtc_s->hours = buff[1];
    out_rtc_s->minutes = buff[2];
    out_rtc_s->secondes = buff[3];
   
    return 0;
}

int pcsb_rtc_set_date(const PCSB_RTC_DATE_STRUCT* const in_rtc_s) {
    uint8_t buff[5] = {0};
    unsigned char msg[4] = {0};

    if (pcsb_is_init() == 0 || in_rtc_s == NULL) return -1;
	msg[0] = pcsb_get_addr_table()->reg_rtc_date;
    bitSet(msg[0],7);
	/*msg[1] = byte2bcd(in_rtc_s->year);
    msg[2] = byte2bcd(in_rtc_s->month);
    msg[3] = byte2bcd(in_rtc_s->day);*/
    msg[1] = in_rtc_s->year;
    msg[2] = in_rtc_s->month;
    msg[3] = in_rtc_s->day;

    if (_int_i2c_op(msg, 4, buff, 5) != 0)
        return -1;

    /*if (bcd2byte(buff[1]) == in_rtc_s->year &&
        bcd2byte(buff[2]) == in_rtc_s->month &&
        bcd2byte(buff[3]) == in_rtc_s->day*/
    if (buff[1] == in_rtc_s->year &&
        buff[2] == in_rtc_s->month &&
        buff[3] == in_rtc_s->day
        ) {
            return 0;
    }
    return -2;
}

int pcsb_rtc_set_time(const PCSB_RTC_TIME_STRUCT* const in_rtc_s) {
    uint8_t buff[4] = {0};
    unsigned char msg[4] = {0};

    if (pcsb_is_init() == 0 || in_rtc_s == NULL) return -1;
	msg[0] = pcsb_get_addr_table()->reg_rtc_time;
    bitSet(msg[0],7);
	/*msg[1] = byte2bcd(in_rtc_s->hours);
    msg[2] = byte2bcd(in_rtc_s->minutes);*/
    msg[1] = in_rtc_s->hours;
    msg[2] = in_rtc_s->minutes;
    msg[3] = 0;   // Force 0 to make test logic easier

    if (_int_i2c_op(msg, 4, buff, 4) != 0)
        return -1;

    /*if (bcd2byte(buff[1]) == in_rtc_s->hours &&
        bcd2byte(buff[2]) == in_rtc_s->minutes*/
    if (buff[1] == in_rtc_s->hours &&
        buff[2] == in_rtc_s->minutes
        ) {
            return 0;
    }

    return -2;
}