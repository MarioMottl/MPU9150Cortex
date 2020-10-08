/*
Kommentar
*/
#ifndef MPU9150_H_INCLUDED
#define MPU9150_H_INCLUDED
//Includes
#include "i2c.h"

//defines
#define MPU9150_I2CSlave           0xD2
#define MPU9150_I2CWrite           0xD2
#define MPU9150_I2CRead            0xD3
#define MPU9150_CONFIG             0x1A
#define MPU9150_GYRO_CONFIG        0x1B
#define MPU9150_GYRO_XOUT_H        0x43
#define MPU9150_GYRO_XOUT_L        0x44
#define MPU9150_GYRO_YOUT_H        0x45
#define MPU9150_GYRO_YOUT_L        0x46
#define MPU9150_GYRO_ZOUT_H        0x47
#define MPU9150_GYRO_ZOUT_L        0x48

#define MPU9150_ACCEL_XOUT_H        0x3B
#define MPU9150_ACCEL_XOUT_L        0x3C
#define MPU9150_ACCEL_YOUT_H        0x3D
#define MPU9150_ACCEL_YOUT_L        0x3E
#define MPU9150_ACCEL_ZOUT_H        0x3F
#define MPU9150_ACCEL_ZOUT_L				0x40

#define MPU9150_POWER_MANAGEMENT	 0x6B
#define MPU9150_SAMPLE_DIVIDER		 0x19

#define MPU9150_ACCEL_CONFIG			 0x1C

#define GYRO_SENSITIVITY 					 131.0f
#define ACC_SENSITIVITY 					16384.0f

//Datastructs
typedef struct {
    float x,y,z;
}xyz;

typedef struct {
    xyz gyro;
    xyz accel;
}mpu_type;

typedef enum								 					    /***************************************/
{											 			 			        /*	   FS_SEL	  *	  Full Scale Range   */
  MR_250 = 0,								 					    /*			 0		  *	    +/- 250 �/s	   	*/
  MR_500 = 1, 												    /*			 1		  *	    +/- 500 �/s		  */
  MR_1000 = 2, 												    /*			 2		  *	    +/- 1000 �/s    */
  MR_2000 = 3												      /*			 3		  *	    +/- 2000 �/s	  */
} mpu_gyro_measurement_range;

typedef enum
{
  DLPF_260_Hz = 0,
  DLPF_184_Hz = 1,
  DLPF_94_Hz = 2,
  DLPF_44_Hz = 3,
  DLPF_21_Hz = 4,
  DLPF_10_Hz = 5,
  DLPF_5_Hz = 6
} mpu_bandwidth_dlpf;

typedef enum
{
	G2 = 0,
	G4 = 1,
	G8 = 2,
	G16 = 3
}AFS_SEL;

//Funktionen
                         
void _MPU9150_CONFIG(void);
void MPU9150_PWR_MGMT_1(void);
void MPU9150_SMPLRT_DIV(void);
void MPU9150_init(void);
void MPU9150_GYROCONFIG(mpu_gyro_measurement_range gmrange);
void MPU9150_ACCELCONFIG(AFS_SEL g);
void MPU_READ_GYRO(mpu_gyro_measurement_range range);
void MPU_READ_ACCEL(AFS_SEL g);
void uart_put_accel(AFS_SEL g);
void uart_put_gyro(mpu_gyro_measurement_range range);
#endif
