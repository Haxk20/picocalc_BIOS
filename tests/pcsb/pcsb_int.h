#include <pico/stdlib.h>
#include <hardware/i2c.h>
#include "pcsb.h"


#ifndef PCSB_INT_H
#define PCSB_INT_H

#define PCSB_I2C_MOD	i2c1
#define PCSB_I2C_ADDR	(0x1F)

#define PCSB_REG_TYP	(0x00)
#define PCSB_REG_VER	(0x01)

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitClear(value, bit) ((value) &= ~(1 << (bit)))
#define bitSet(value, bit) ((value) |= (1 << (bit)))


int _int_i2c_op(const uint8_t* in_buff, const size_t in_size, uint8_t* out_buff, const size_t out_size);

#endif	/* PCSB_INT_H */