#ifndef MPU6050_H
#define MPU6050_H

#include "hardware/i2c.h"

#include <stdint.h>

#define MPU6050_I2C_DEFAULT_ADDR 0x68
#define MPU6050_PWR_MGMT_1 0x6B

#define MPU6050_GYRO_CONFIG  0x1B
#define MPU6050_ACCEL_CONFIG 0x1C

#define MPU6050_GYRO_XOUT  0x43
#define MPU6050_ACCEL_XOUT 0x3B

#define GYRO_FULL_SCALE_250	131.0f
#define GYRO_FULL_SCALE_500	65.5f
#define GYRO_FULL_SCALE_1000	32.8f
#define GYRO_FULL_SCALE_2000	16.4f

#define ACCEL_FULL_SCALE_2	16384
#define ACCEL_FULL_SCALE_4	8192
#define ACCEL_FULL_SCALE_8	4096
#define ACCEL_FULL_SCALE_16	2048

#define DEFAULT_HANDLER(X) mpu6050_handle_t X = {.i2c = i2c0, .address = MPU6050_I2C_DEFAULT_ADDR}

typedef struct{
	i2c_inst_t *	i2c;
	uint8_t 	address;
} mpu6050_handle_t;

typedef struct{
	uint		sda;
	uint		scl;
	uint8_t		gyro_fs;
	uint8_t		accel_fs;
	uint		baudrate;
} mpu6050_config_t;

typedef struct{
	int16_t 	x;
	int16_t 	y;
	int16_t 	z;
} mpu6050_axis_t;


int mpu6050_init(mpu6050_handle_t *handle, const mpu6050_config_t *config);

int mpu6050_read_gyro(mpu6050_handle_t *handle, mpu6050_axis_t *gyro);

int mpu6050_read_accel(mpu6050_handle_t *handle, mpu6050_axis_t *accel);


#endif /* MPU6050_H */
