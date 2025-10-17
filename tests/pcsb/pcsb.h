#include <pico/stdlib.h>
#include "kbd.h"
#include "rtc.h"


#ifndef PCSB_H
#define PCSB_H

typedef enum {
	PCSB_BKL_KBD,
	PCSB_BKL_LCD
} PCSB_BKL;

typedef struct addr_table_s {
	uint8_t reg_cfg;
	uint8_t reg_int;
	uint8_t reg_int_cfg;
	uint8_t reg_bkl;
	uint8_t reg_bk2;
	uint8_t reg_deb;
	uint8_t reg_frq;
	uint8_t reg_rst_ctrl;
	uint8_t reg_off_ctrl;
	
	uint8_t reg_rtc_cfg;
	uint8_t reg_rtc_date;
	uint8_t reg_rtc_time;
	uint8_t reg_rtc_alarm_date;
	uint8_t reg_rtc_alarm_time;
	
	uint8_t reg_key;
	uint8_t reg_fif;
	uint8_t reg_c64_mtx;
	uint8_t reg_c64_js;
	
	uint8_t reg_bat;
} PCSB_REGS_ADDR_TABLE;

#define PROG_PCSB_RAT ((const PCSB_REGS_ADDR_TABLE) { \
	.reg_cfg = 0x02, \
	.reg_int = 0x03, \
	.reg_key = 0x04, \
	.reg_bkl = 0x05, \
	.reg_deb = 0x06, \
	.reg_frq = 0x07, \
	.reg_rst_ctrl = 0x08, \
	.reg_fif = 0x09, \
	.reg_bk2 = 0x0A, \
	.reg_bat = 0x0B, \
	.reg_c64_mtx = 0x0C, \
	.reg_c64_js = 0x0D, \
	.reg_off_ctrl = 0x0E, \
	.reg_int_cfg = 0x0F, \
	.reg_rtc_cfg = 0x10, \
	.reg_rtc_date = 0x11, \
	.reg_rtc_time = 0x12, \
	.reg_rtc_alarm_date = 0x13, \
	.reg_rtc_alarm_time = 0x14, \
})


uint32_t pcsb_init(const PCSB_REGS_ADDR_TABLE* const addr_table, const uint8_t req_typ_id);
uint8_t pcsb_is_init(void);
uint pcsb_get_i2c_speed(void);
uint8_t pcsb_read_version(void);

const PCSB_REGS_ADDR_TABLE* pcsb_get_addr_table(void);
uint32_t pcsb_read_reg8b(const uint8_t reg_addr, uint8_t* const out_buff);

int pcsb_read_battery(void);
int pcsb_set_backlight(PCSB_BKL target, uint8_t val);
int pcsb_pwr_off(uint8_t delay);
int pcsb_pwr_sleep(uint8_t delay);

#endif	/* PCSB_H */