#include "i2c.h"

void i2c_init(void){
    //Enable CLK for PB7 and PB6
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	GPIOB->CRL &= 0x00FFFFFF;
	GPIOB->CRL |= 0x55000000;
}

void i2c_delay(void){
    wait_ms(1);
}

void i2c_start(void){
    //Start sequence
	SDA = 1;
	i2c_delay();
	SCL = 1;
	i2c_delay();
	SDA = 0;
	i2c_delay();
	SCL = 0;
	i2c_delay();
}

void i2c_stop(void){
    //Stop sequence
	SDA = 0;
	i2c_delay();
	SCL = 1;
	i2c_delay();
	SDA = 1;
	i2c_delay();
}

unsigned char i2c_write(unsigned char data){
	int i;
	static unsigned char ack;
    for(i = 8; i > 0; i--)
	{
		i2c_delay();
    	if(data&0x80) SDA = 1;	//Maskierung mit 80 -> MSB (High / Low)
    	else SDA = 0;
    	SCL = 1;
    	data <<= 1;
    	i2c_delay();
   		SCL = 0;
    }
    SDA = 1;
    SCL = 1;
    ack = SDA_IN;          // possible ACK bit
    SCL = 0;
    return ack;
}

unsigned char i2c_read(char ack){
	int i;
	unsigned char	data = 0;
    SDA = 1;
    for(i = 0; i <= 7; i++)
	{
        i2c_delay();
        data <<= 1;
        SCL = 1;

        i2c_delay();
        if(SDA_IN)
		{
			data |= 1;
		}
        SCL = 0;
    }

	i2c_delay();
    if(ack)
	{
		SDA = 0;
	}
    else
	{
		SDA = 1;
	}
    SCL = 1;

    i2c_delay();             // send (N)ACK bit
    SCL = 0;
    SDA = 1;
  	return data;
}
