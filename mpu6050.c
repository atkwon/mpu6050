#include "mpu6050.h"
#include "reg.h"
#include <stdio.h>

#include "hardware/i2c.h"
#include "pico/stdlib.h"

#define TIMEOUT_MS TIMER_MS(10) 

static int mpu6050_wakeup(mpu6050_handle_t *handle);
static int mpu6050_config_gyro(mpu6050_handle_t *handle, uint8_t gyro_fs);
static int mpu6050_config_accel(mpu6050_handle_t *handle, uint8_t accel_fs);


int mpu6050_init(mpu6050_handle_t *handle, const mpu6050_config_t *config)
{
	if (handle->address == 0){
		handle->address = MPU6050_I2C_DEFAULT_ADDR;
	}


	int ret = mpu6050_wakeup(handle, config->clk_sel);
	if (ret != 2) {
		printf("Error: Failed to wake up. Expected 2 bytes, got %d.\n", ret);
		return -1;
	}

	ret = mpu6050_config_gyro(handle, config->gyro_fs);
	if (ret != 2) {
		printf("Error: Failed to configure gyro. Expected 2 bytes, got %d.\n", ret);
		return -1;
	}


	ret = mpu6050_config_accel(handle, config->accel_fs);
	if (ret != 2) {
		printf("Error: Failed to configure accel. Expected 2 bytes, got %d.\n", ret);
		return -1;
	}

	return 0;
}

int mpu6050_read_gyro(mpu6050_handle_t *handle, mpu6050_axis_t *gyro)
{
	const uint8_t gyro_reg = MPU6050_GYRO_XOUT;
	uint8_t data[6];

	int ret = i2c_write_blocking_until(handle->i2c, handle->address, &gyro_reg, 1, true, TIMEOUT_MS);
	if (ret != 1) {
		printf("Error: Failed to write gyro address. Expected 1 bytes, got %d.\n", ret);
		return -1;
	}

	ret = i2c_read_blocking_until(handle->i2c, handle->address, data, 6, false, TIMEOUT_MS);
	if (ret != 6) {
		printf("Error: Failed to read gyro data. Expected 6 bytes, got %d.\n", ret);
		return -1;
	}

	gyro->x = (int16_t) ((data[0] << 8) | data[1]);
	gyro->y = (int16_t) ((data[2] << 8) | data[3]);
	gyro->z = (int16_t) ((data[4] << 8) | data[5]);

	return 0;
}

int mpu6050_read_accel(mpu6050_handle_t *handle, mpu6050_axis_t *accel)
{
	const uint8_t accel_reg = MPU6050_ACCEL_XOUT;
	uint8_t data[6];

	int ret = i2c_write_blocking_until(handle->i2c, handle->address, &accel_reg, 1, true, TIMEOUT_MS);
	if (ret != 1) {
		printf("Error: Failed to write accel address. Expected 1 bytes, got %d.\n", ret);
		return -1;
	}

	ret = i2c_read_blocking_until(handle->i2c, handle->address, data, 6, false, TIMEOUT_MS);
	if (ret != 6) {
		printf("Error: Failed to read accel data. Expected 6 bytes, got %d.\n", ret);
		return -1;
	}

	accel->x = (int16_t) ((data[0] << 8) | data[1]);
	accel->y = (int16_t) ((data[2] << 8) | data[3]);
	accel->z = (int16_t) ((data[4] << 8) | data[5]);

	return 0;
}


static int mpu6050_wakeup(mpu6050_handle_t *handle, uint8_t clk_sel){
	uint8_t buffer[2];
	buffer[0] = MPU6050_PWR_MGMT_1;
	buffer[1] = bit_set(0, MPU_6050_PM_CONFIG_SLEEP_MASK)
		|   bit_set(clk_sel, MPU_6050_PM_CONFIG_CLKSEL_MASK)
	int ret	  = i2c_write_blocking_until(handle->i2c, handle->address, buffer, 2, false, TIMEOUT_MS);

	return ret;
}

 static int mpu6050_config_gyro(
      mpu6050_handle_t *handle,
      enum mpu_6050_gyro_config_fs_sel fs_sel)
 {
      uint8_t buf[2];

      buf[0] = MPU6050_GYRO_CONFIG;
      buf[1]
              = bit_set(0,      MPU_6050_GYRO_CONFIG_XG_ST_MASK)
              | bit_set(0,      MPU_6050_GYRO_CONFIG_YG_ST_MASK)
              | bit_set(0,      MPU_6050_GYRO_CONFIG_ZG_ST_MASK)
              | bit_set(fs_sel, MPU_6050_GYRO_CONFIG_FS_SEL_MASK);

      int ret = i2c_write_blocking_until(
              handle->i2c,
              handle->address,
              buf,
              sizeof(buf),
              false,
	      TIMEOUT_MS);

      return ret;
 }

 static int mpu6050_config_accel(
      mpu6050_handle_t *handle,
      enum mpu_6050_accel_config_fs_sel fs_sel)
 {
      uint8_t buf[2];

      buf[0] = MPU6050_ACCEL_CONFIG;
      buf[1]
              = bit_set(0,      MPU_6050_ACCEL_CONFIG_XG_ST_MASK)
              | bit_set(0,      MPU_6050_ACCEL_CONFIG_YG_ST_MASK)
              | bit_set(0,      MPU_6050_ACCEL_CONFIG_ZG_ST_MASK)
              | bit_set(fs_sel, MPU_6050_ACCEL_CONFIG_FS_SEL_MASK);

      int ret = i2c_write_blocking_until(
              handle->i2c,
              handle->address,
              buf,
              sizeof(buf),
              false,
	      TIMEOUT_MS);

      return ret;
 }
