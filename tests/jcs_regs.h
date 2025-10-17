#include "pcsb.h"


#define JCS_PCSB_RAT ((const PCSB_REGS_ADDR_TABLE) { \
	.reg_cfg = 0x02, \
	.reg_int = 0x03, \
	.reg_key = 0x04, \
	.reg_bkl = 0x05, \
	.reg_bk2 = 0x0A, \
	.reg_deb = 0x06, \
	.reg_frq = 0x07, \
	\
	.reg_rst_ctrl = 0x08, \
	.reg_off_ctrl = 0x0E, \
	\
	.reg_int_cfg = 0x12, \
	.reg_rtc_cfg = 0x13, \
	.reg_rtc_date = 0x14, \
	.reg_rtc_time = 0x15, \
	.reg_rtc_alarm_date = 0x16, \
	.reg_rtc_alarm_time = 0x17, \
	\
	.reg_fif = 0x09, \
	.reg_c64_mtx = 0x0C, \
	.reg_c64_js = 0x0D, \
	.reg_bat = 0x0B, \
})
#define JCS_PCSB_ID     (0xCA)
