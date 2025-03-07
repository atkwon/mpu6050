#ifndef MPU6050_H
#define MPU6050_H

#include "hardware/i2c.h"

#include <stdint.h>

#define MPU6050_PWR_MGMT_1 0x6B

#define MPU6050_GYRO_CONFIG  0x1B
#define MPU6050_ACCEL_CONFIG 0x1C

#define MPU6050_GYRO_XOUT  0x43
#define MPU6050_ACCEL_XOUT 0x3B

/*
 * Gyro Full Scale      / Sensitivity
 * 0 => 250                     131
 * 1 => 500                     65.5
 * 2 => 1000                    32.8
 * 3 => 2000 deg/s              16.4 LSB/(deg/s)
 *
 * Accel Full Scale     / Sensitivity
 * 0 => 2                       16384
 * 1 => 4                       8192
 * 2 => 8                       4096
 * 3 => 16g                     2048 LSB/g
 */

#define GYRO_FULL_SCALE_250	131f
#define GYRO_FULL_SCALE_500	65.5f
#define GYRO_FULL_SCALE_1000	32.8f
#define GYRO_FULL_SCALE_2000	16.4f

#define ACCEL_FULL_SCALE_2	16384
#define ACCEL_FULL_SCALE_4	8192
#define ACCEL_FULL_SCALE_8	4096
#define ACCEL_FULL_SCALE_16	2048


int mpu6050_init(i2c_inst_t *i2c,
	uint		      sda,
	uint		      scl,
	uint8_t		      gyro_fs,
	uint8_t		      accel_fs,
	uint		      baudrate);

int mpu6050_read_gyro(int16_t *gx, int16_t *gy, int16_t *gz);

int mpu6050_read_accel(int16_t *ax, int16_t *ay, int16_t *az);

#endif /* MPU6050_H */
