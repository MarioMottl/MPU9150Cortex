#include "MPU9150.h" 

mpu_type mpu;

void _MPU9150_CONFIG(){
    i2c_start();
    i2c_write(MPU9150_I2CWrite); 
    i2c_write(MPU9150_CONFIG);  
    i2c_write(0x06);  
    i2c_stop();
}

void MPU9150_PWR_MGMT_1()
{
    i2c_start();   
    i2c_write(MPU9150_I2CWrite);  
    i2c_write(MPU9150_POWER_MANAGEMENT);   
    i2c_write(0x01);  
    i2c_stop();
}

void MPU9150_SMPLRT_DIV()
{
    i2c_start(); 
    i2c_write(MPU9150_I2CWrite); 
    i2c_write(MPU9150_SAMPLE_DIVIDER); 
    i2c_write(0x00); 
    i2c_stop();
}
/*
Register (Hex) BIT7 BIT6 BIT5   BIT4 BIT3 BIT2 BIT1 BIT0
	   1B    XG_ST YG_ST ZG_ST   FS_SEL    -    -    -
*/
void MPU9150_GYROCONFIG(mpu_gyro_measurement_range gmrange){
    uint8_t data = gmrange<<3u;
    i2c_start();  
    i2c_write(MPU9150_I2CWrite);
    i2c_write(MPU9150_GYRO_CONFIG);  
    i2c_write(data);   
    i2c_stop();
}

void MPU9150_ACCELCONFIG(AFS_SEL g){
    uint8_t data = g<<3u;
    i2c_start();  
    i2c_write(MPU9150_I2CWrite);
    i2c_write(MPU9150_ACCEL_CONFIG);  
    i2c_write(data);   
    i2c_stop();
}

int8_t MPU9150_read(int8_t addr){
    int8_t data;
    i2c_start();
    i2c_write(MPU9150_I2CWrite); 
    i2c_write(addr);
    i2c_start();
    i2c_write(MPU9150_I2CRead);
    data = i2c_read(0);
    i2c_stop();
    return data;
}


void MPU9150_init(){
    i2c_init();
    MPU9150_PWR_MGMT_1();
    _MPU9150_CONFIG();
	MPU9150_SMPLRT_DIV();
}

void MPU_READ_GYRO(mpu_gyro_measurement_range range){
    float gyrosensitivity = GYRO_SENSITIVITY / (float)(0x1u << range);
	uint16_t help;
	uint8_t buffer[10];
	//x
	buffer[0] = MPU9150_read(MPU9150_GYRO_XOUT_H); // Lese werte von X in buffer ein
	buffer[1] = MPU9150_read(MPU9150_GYRO_XOUT_L);
	help = ((uint16_t)buffer[0] << 8) | buffer[1]; // Baue wert zusammen
	mpu.gyro.x = ((float)help)/gyrosensitivity;	// schreibe wert in zwischenspeicher
	//y
	buffer[2] = MPU9150_read(MPU9150_GYRO_YOUT_H); // Lese werte von Y in buffer ein
	buffer[3] = MPU9150_read(MPU9150_GYRO_YOUT_L);
	help = ((uint16_t)buffer[2] << 8) | buffer[3]; // Baue wert zusammen
	mpu.gyro.y = ((float)help)/gyrosensitivity; // schreibe wert in zwischenspeicher
	//z
	buffer[4] = MPU9150_read(MPU9150_GYRO_ZOUT_H); // lese werte von Z in buffer ein 
	buffer[5] = MPU9150_read(MPU9150_GYRO_ZOUT_L);
	help = ((uint16_t)buffer[4] << 8) | buffer[5]; // Baue wert zusammen
	mpu.gyro.z = ((float)help)/gyrosensitivity; // schreieb wert in zwischenspeicher
}
void MPU_READ_ACCEL(AFS_SEL g){
	uint16_t help;
	uint8_t buffer[10];
	float accelsensitivity = ACC_SENSITIVITY/(float)(0x1u << g);
	//x
	buffer[0] = MPU9150_read(MPU9150_ACCEL_XOUT_H); // Lese werte von X in buffer ein
	buffer[1] = MPU9150_read(MPU9150_ACCEL_XOUT_L);
	help = ((uint16_t)buffer[0] << 8) | buffer[1]; // Baue wert zusammen
	mpu.accel.x = (((float)help)/accelsensitivity)/3.5;	// schreibe wert in zwischenspeicher
	//y
	buffer[2] = MPU9150_read(MPU9150_ACCEL_YOUT_H); // Lese werte von Y in buffer ein
	buffer[3] = MPU9150_read(MPU9150_ACCEL_YOUT_L);
	help = ((uint16_t)buffer[2] << 8) | buffer[3]; // Baue wert zusammen
	mpu.accel.y = (((float)help)/accelsensitivity)/3.5; // schreibe wert in zwischenspeicher
	//z
	buffer[4] = MPU9150_read(MPU9150_ACCEL_ZOUT_H); // lese werte von Z in buffer ein 
	buffer[5] = MPU9150_read(MPU9150_ACCEL_ZOUT_L);
	help = ((uint16_t)buffer[4] << 8) | buffer[5]; // Baue wert zusammen
	mpu.accel.z = (((float)help)/accelsensitivity)/3.5; // schreieb wert in zwischenspeicher
}

void uart_put_accel(AFS_SEL g){
    uart_put_string("\033[93m\r\n\r ------------------------------------Accel--------------------------------\033[0m\n\r");
	char buf[256];
    MPU_READ_ACCEL(g);
	sprintf(buf, "|X : %6.1f|\r\n|Y : %6.1f|\r\n|Z : %6.1f|\r\n", mpu.accel.x, mpu.accel.y, mpu.accel.z);
	uart_put_string(buf);
}

void uart_put_gyro(mpu_gyro_measurement_range range){
    uart_put_string("\033[93m\r\n\r ----------------------------------Gyro----------------------------------\033[0m\n\r");
	char buf[256];
    MPU_READ_GYRO(range);
	sprintf(buf, "|X : %6.1f|\r\n|Y : %6.1f|\r\n|Z : %6.1f|\r\n", mpu.gyro.x, mpu.gyro.y, mpu.gyro.z);
	uart_put_string(buf);
}
