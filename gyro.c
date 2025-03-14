#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "mpu6050.h"

#define SDA_PIN		4
#define SCL_PIN 	5
#define GYRO_FS 	1
#define ACCEL_FS	1
#define BAUDRATE	100000

int main(void)
{

	stdio_init_all();


	mpu6050_handle_t mpu = default_mpu;

	mpu6050_config_t config = {
		.sda = SDA_PIN,
		.scl = SCL_PIN,
		.gyro_fs = GYRO_FS,
		.accel_fs = ACCEL_FS,
		.baudrate = BAUDRATE
	};

	i2c_init(handle->i2c, config->baudrate);
	gpio_set_function(config->sda, GPIO_FUNC_I2C);
	gpio_set_function(config->scl, GPIO_FUNC_I2C);
	gpio_pull_up(config->sda);
	gpio_pull_up(config->scl);

	
	if(mpu6050_init(&mpu, &config) != 0){
		printf("Error: MPU6050 initialization failed\n");
		while(true){
			tight_loop_contents();
		}
	}

	printf("MPU6050 initialized\n");

	mpu6050_axis_t raw_gyro;
	float x, y, z;

	while(true){
		int read = mpu6050_read_gyro(&mpu, &raw_gyro);
		if(read != 0){
			printf("Error: Failed to read gyro\n");
		}
		else{
			x = raw_gyro.x / GYRO_FULL_SCALE_500;
			y = raw_gyro.y / GYRO_FULL_SCALE_500;
			z = raw_gyro.z / GYRO_FULL_SCALE_500;

			printf("Gyro (deg/s): X = %.2f, Y = %.2f, Z = %.2f\n", x, y, z);
		}

		sleep_ms(100);
	}


	return 0;
}
