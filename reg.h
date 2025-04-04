#define mask2shift(X) __builtin_ctz(X)

#define bit_set(X, mask) (((X) << mask2shift(mask)) & (mask))
#define bit_get(X, mask) (((X) & (mask)) >> mask2shift(mask))

#define MPU_6050_GYRO_CONFIG 0x1B
#define MPU_6050_ACCEL_CONFIG 0x1C

#define MPU_6050_GYRO_CONFIG_XG_ST_MASK  (0x1 << 7)
#define MPU_6050_GYRO_CONFIG_YG_ST_MASK  (0x1 << 6)
#define MPU_6050_GYRO_CONFIG_ZG_ST_MASK  (0x1 << 5)
#define MPU_6050_GYRO_CONFIG_FS_SEL_MASK (0x3 << 3)

#define MPU_6050_ACCEL_CONFIG_XG_ST_MASK  (0x1 << 7)
#define MPU_6050_ACCEL_CONFIG_YG_ST_MASK  (0x1 << 6)
#define MPU_6050_ACCEL_CONFIG_ZG_ST_MASK  (0x1 << 5)
#define MPU_6050_ACCEL_CONFIG_FS_SEL_MASK (0x3 << 3)

#define MPU_6050_PM_CONFIG_SLEEP_MASK	(0x1 << 6)
#define MPU_6050_PM_CONFIG_CLKSEL_MASK	(0x3 << 3)

enum mpu_6050_gyro_config_fs_sel {
	MPU_6050_GYRO_CONFIG_FS_SEL_250  = 0,
	MPU_6050_GYRO_CONFIG_FS_SEL_500  = 1,
	MPU_6050_GYRO_CONFIG_FS_SEL_1000 = 2,
	MPU_6050_GYRO_CONFIG_FS_SEL_2000 = 3,
};

enum mpu_6050_accel_config_fs_sel {
	MPU_6050_ACCEL_CONFIG_FS_SEL_2	= 0,
	MPU_6050_ACCEL_CONFIG_FS_SEL_4	= 1,
	MPU_6050_ACCEL_CONFIG_FS_SEL_8	= 2,
	MPU_6050_ACCEL_CONFIG_FS_SEL_16	= 3,
};

