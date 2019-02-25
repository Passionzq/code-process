#include <reg52.h>
#include "../inc/i2c.h"
#include "../inc/delay_ms.h"

void delay() 
{
	;;
}
void i2c_init()
{
	SDA = 1;
	delay();
	SCL = 1;
	delay();
}
void start()
{
	SDA = 1;
	SCL = 1;
	delay();
	SDA = 0;
	delay();
}
void stop()
{
	SDA = 0;
	delay();
	SCL = 1;
	delay();
	SDA = 1;
	delay();
}
void respons()
{
	unsigned char i = 0;
	SCL = 1;
	delay();
	while(SDA == 1 && i < 255)
		i++;
	SCL = 0;
	delay();
}
void writebyte(unsigned char date)
{
	unsigned char i,temp;
	temp = date;
	for(i = 0; i < 8; i++)
	{
		temp <<= 1;
		SCL = 0;
		delay();
		SDA = CY;
		delay();
		SCL = 1;
		delay();
	}	
	SCL = 0;
	SDA = 1;
	delay();
}
unsigned char readbyte()
{
	unsigned char i,k;
	SCL = 0;
	delay();
	SDA = 1;
	for(i = 0; i < 8; i++)
	{
		SCL = 1;	
		delay();
		k = (k << 1) | SDA; 
		SCL = 0;
		delay();
	}
	delay();
	return k;
}
void write_add(unsigned char address,unsigned char date)
{
	start();
	writebyte(0xa0);
	respons();
	writebyte(address);
	respons();
	writebyte(date);
	respons();
	stop();
}
unsigned char read_add(unsigned char address)
{
	unsigned char date;
	start();
	writebyte(0xa0);
	respons();
	writebyte(address);
	respons();
	start();
	writebyte(0xa1);
	respons();
	date = readbyte();
	stop();
	return date;
}



void write_n_add(unsigned char * p,unsigned char address,unsigned char n)
{
	unsigned char i;
	for(i = 0; i < n; i++)
	{
		write_add((address + i),*(p + i));
		delay_ms(20);
	}
}

void read_n_add(unsigned char * p,unsigned char address,unsigned char n)
{
	unsigned char i;
	for(i = 0; i < n; i++)
	{
		*(p + i) = read_add(address + i);
		
	}
}

