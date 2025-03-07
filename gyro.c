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

	int init = mpu6050_init(i2c0,
			SDA_PIN,
			SCL_PIN,
			GYRO_FS,
			ACCEL_FS,
			BAUDRATE);
	
	if(init != 0){
		printf("Error: MPU6050 initialization failed\n");
		while(true){
			tight_loop_contents();
		}
	}

	printf("MPU6050 initialized\n");

	int16_t gx, gy, gz;
	float x, y, z;

	while(true){
		int read = mpu6050_read_gyro(&gx, &gy, &gz);
		if(read != 0){
			printf("Error: Failed to read gyro\n");
		}
		else{
			x = gx / GYRO_FULL_SCALE_500;
			y = gy / GYRO_FULL_SCALE_500;
			z = gz / GYRO_FULL_SCALE_500;

			printf("Gyro (deg/s): X = %.2f, Y = %.2f, Z = %.2f\n", x, y, z);
		}

		sleep_ms(100);
	}


	return 0;
}
