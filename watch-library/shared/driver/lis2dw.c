/*
 * MIT License
 *
 * Copyright (c) 2021 Joey Castillo
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "lis2dw.h"
#include "watch.h"

bool lis2dw_begin(void) {
    if (lis2dw_get_device_id() != LIS2DW_WHO_AM_I_VAL) {
        return false;
    }
    watch_i2c_write8(LIS2DW_ADDRESS, LIS2DW_REG_CTRL2, LIS2DW_CTRL2_VAL_BOOT);
    watch_i2c_write8(LIS2DW_ADDRESS, LIS2DW_REG_CTRL2, LIS2DW_CTRL2_VAL_SOFT_RESET);
    // Start at lowest possible data rate and lowest possible power mode
    watch_i2c_write8(LIS2DW_ADDRESS, LIS2DW_REG_CTRL1, LIS2DW_CTRL1_VAL_ODR_LOWEST | LIS2DW_CTRL1_VAL_MODE_LOW_POWER | LIS2DW_CTRL1_VAL_LPMODE_1);
    // Enable block data update (output registers not updated until MSB and LSB have been read) and address autoincrement
    watch_i2c_write8(LIS2DW_ADDRESS, LIS2DW_REG_CTRL2, LIS2DW_CTRL2_VAL_BDU | LIS2DW_CTRL2_VAL_IF_ADD_INC);
    // Set range to ±2G
    watch_i2c_write8(LIS2DW_ADDRESS, LIS2DW_REG_CTRL6, LIS2DW_CTRL6_VAL_RANGE_2G);

    return true;
}

uint8_t lis2dw_get_device_id(void) {
    return watch_i2c_read8(LIS2DW_ADDRESS, LIS2DW_REG_WHO_AM_I);
}

bool lis2dw_have_new_data(void) {
    uint8_t retval = watch_i2c_read8(LIS2DW_ADDRESS, LIS2DW_REG_STATUS);
    return retval & LIS2DW_STATUS_VAL_DRDY;
}

lis2dw_reading_t lis2dw_get_raw_reading(void) {
    uint8_t buffer[6];
    uint8_t reg = LIS2DW_REG_OUT_X_L | 0x80; // set high bit for consecutive reads
    lis2dw_reading_t retval;

    watch_i2c_send(LIS2DW_ADDRESS, &reg, 1);
    watch_i2c_receive(LIS2DW_ADDRESS, (uint8_t *)&buffer, 6);

    retval.x = buffer[0];
    retval.x |= ((uint16_t)buffer[1]) << 8;
    retval.y = buffer[2];
    retval.y |= ((uint16_t)buffer[3]) << 8;
    retval.z = buffer[4];
    retval.z |= ((uint16_t)buffer[5]) << 8;

    return retval;
}

 lis2dw_acceleration_measurement_t lis2dw_get_acceleration_measurement(lis2dw_reading_t *out_reading) {
    lis2dw_reading_t reading = lis2dw_get_raw_reading();
    uint8_t range = lis2dw_get_range();
    if (out_reading != NULL) *out_reading = reading;

    // this bit is cribbed from Adafruit's LIS3DH driver; from their notes, the magic number below
    // converts from 16-bit lsb to 10-bit and divides by 1k to convert from milli-gs.
    // final value is raw_lsb => 10-bit lsb -> milli-gs -> gs
    uint8_t lsb_value = 1;
    if (range == LIS2DW_RANGE_2_G) lsb_value = 4;
    if (range == LIS2DW_RANGE_4_G) lsb_value = 8;
    if (range == LIS2DW_RANGE_8_G) lsb_value = 16;
    if (range == LIS2DW_RANGE_16_G) lsb_value = 48;

    lis2dw_acceleration_measurement_t retval;

    retval.x = lsb_value * ((float)reading.x / 64000.0);
    retval.y = lsb_value * ((float)reading.y / 64000.0);
    retval.z = lsb_value * ((float)reading.z / 64000.0);

    return retval;
}

void lis2dw_set_range(lis2dw_range_t range) {
    uint8_t val = watch_i2c_read8(LIS2DW_ADDRESS, LIS2DW_REG_CTRL6) & ~(LIS2DW_RANGE_16_G << 4);
    uint8_t bits = range << 4;

    watch_i2c_write8(LIS2DW_ADDRESS, LIS2DW_REG_CTRL6, val | bits);
}

lis2dw_range_t lis2dw_get_range(void) {
    uint8_t retval = watch_i2c_read8(LIS2DW_ADDRESS, LIS2DW_REG_CTRL6) & (LIS2DW_RANGE_16_G << 4);
    retval >>= 4;
    return (lis2dw_range_t)retval;
}

void lis2dw_set_data_rate(lis2dw_data_rate_t dataRate) {
    uint8_t val = watch_i2c_read8(LIS2DW_ADDRESS, LIS2DW_REG_CTRL1) & ~(0b1111 << 4);
    uint8_t bits = dataRate << 4;

    watch_i2c_write8(LIS2DW_ADDRESS, LIS2DW_REG_CTRL1, val | bits);
}

lis2dw_data_rate_t lis2dw_get_data_rate(void) {
    return watch_i2c_read8(LIS2DW_ADDRESS, LIS2DW_REG_CTRL1) >> 4;
}

void lis2dw_set_low_power_mode(lis2dw_low_power_mode_t mode) {
    uint8_t val = watch_i2c_read8(LIS2DW_ADDRESS, LIS2DW_REG_CTRL1) & ~(0b11);
    uint8_t bits = mode & 0b11;

    watch_i2c_write8(LIS2DW_ADDRESS, LIS2DW_REG_CTRL1, val | bits);
}

lis2dw_low_power_mode_t lis2dw_get_low_power_mode(void) {
    return watch_i2c_read8(LIS2DW_ADDRESS, LIS2DW_REG_CTRL1) & 0b11;
}

void lis2dw_set_low_noise_mode(bool on) {
    uint8_t val = watch_i2c_read8(LIS2DW_ADDRESS, LIS2DW_REG_CTRL1) & ~(LIS2DW_CTRL6_VAL_LOW_NOISE);
    uint8_t bits = on ? LIS2DW_CTRL6_VAL_LOW_NOISE : 0;

    watch_i2c_write8(LIS2DW_ADDRESS, LIS2DW_REG_CTRL1, val | bits);
}

bool lis2dw_get_low_noise_mode(void) {
    return (watch_i2c_read8(LIS2DW_ADDRESS, LIS2DW_REG_CTRL1) & LIS2DW_CTRL6_VAL_LOW_NOISE) != 0;
}

inline void lis2dw_disable_fifo(void) {
    watch_i2c_write8(LIS2DW_ADDRESS, LIS2DW_REG_FIFO_CTRL, LIS2DW_FIFO_CTRL_MODE_OFF);
}

inline void lis2dw_enable_fifo(void) {
    watch_i2c_write8(LIS2DW_ADDRESS, LIS2DW_REG_FIFO_CTRL, LIS2DW_FIFO_CTRL_MODE_COLLECT_AND_STOP | LIS2DW_FIFO_CTRL_FTH);
}

bool lis2dw_read_fifo(lis2dw_fifo_t *fifo_data) {
    uint8_t temp = watch_i2c_read8(LIS2DW_ADDRESS, LIS2DW_REG_FIFO_SAMPLE);
    bool overrun = !!(temp & LIS2DW_FIFO_SAMPLE_OVERRUN);
    uint8_t buffer[6];

    fifo_data->count = temp & LIS2DW_FIFO_SAMPLE_COUNT;

    for(int i = 0; i < fifo_data->count; i++) {
        watch_i2c_receive(LIS2DW_ADDRESS, (uint8_t *)&buffer, 6);
        fifo_data->readings[i] = lis2dw_get_raw_reading();
    }

    return overrun;
}

void lis2dw_clear_fifo(void) {
    watch_i2c_write8(LIS2DW_ADDRESS, LIS2DW_REG_FIFO_CTRL, LIS2DW_FIFO_CTRL_MODE_OFF);
    watch_i2c_write8(LIS2DW_ADDRESS, LIS2DW_REG_FIFO_CTRL, LIS2DW_FIFO_CTRL_MODE_COLLECT_AND_STOP | LIS2DW_FIFO_CTRL_FTH);
}
