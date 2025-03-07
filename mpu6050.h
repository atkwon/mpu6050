#ifndef MPU6050_H
#define MPU6050_H

#include "hardware/i2c.h"

#include <stdint.h>

#define MPU6050_PWR_MGMT_1 0x6B

#define MPU6050_GYRO_CONFIG  0x1B
#define MPU6050_ACCEL_CONFIG 0x1C

#define MPU6050_GYRO_XOUT  0x43
#define MPU6050_ACCEL_XOUT 0x3B


int mpu6050_init(i2c_inst_t *i2c,
	uint		      sda,
	uint		      scl,
	uint8_t		      gyro_fs,
	uint8_t		      accel_fs,
	uint		      baudrate);

int mpu6050_read_gyro(int16_t *gx, int16_t *gy, int16_t *gz);

int mpu6050_read_accel(int16_t *ax, int16_t *ay, int16_t *az);

#endif /* MPU6050_H */
