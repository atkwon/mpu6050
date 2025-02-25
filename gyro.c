#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "mpu6050.h"

/*
 * Gyro Full Scale	/ Sensitivity
 * 0 => 250			131
 * 1 => 500			65.5
 * 2 => 1000			32.8
 * 3 => 2000 deg/s		16.4 LSB/(deg/s)
 *
 * Accel Full Scale	/ Sensitivity
 * 0 => 2			16384
 * 1 => 4			8192
 * 2 => 8			4096
 * 3 => 16g			2048 LSB/g
 */


int main(){


	stdio_init_all();

	int init = mpu6050_init(i2c0,
			4,	/* SDA pin # */
			5,	/* SCL pin # */
			1,	/* gyro_fs */
			1,	/* accel_fs */
			100000)	/* baudrate */
	
	if(init != 0){
		printf("Error: MPU6050 initialization failed\n");
		while(;;);
	}

	printf("MPU6050 initialized\n");

	int16_t gx, gy, gz;
	float x, y, z;

	while(;;){
		int read = mpu6050_read_gyro(&gx, &gy, &gz);
		if(read != 0){
			printf("Error: Failed to read gyro\n");
		}
		else{
			x = gx / 65.5f;
			y = gy / 65.5f;
			z = gz / 65.5f;

			printf("Gyro (deg/s): X = %.2f, Y = %.2f, Z = %.2f\n", x, y, z);
		}

		sleep_ms(100);
	}


	return 0;
}
