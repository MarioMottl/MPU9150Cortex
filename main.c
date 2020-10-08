#include "MPU9150.h"

int main(void){
	uart_init(9600);
	MPU9150_init();
	MPU9150_GYROCONFIG(MR_2000);
	MPU9150_ACCELCONFIG(G16);
	while(1){
	uart_put_accel(G16);
	//uart_put_gyro(MR_2000);
	}
}
