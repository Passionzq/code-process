#ifndef	I2C_H
#define	I2C_H

sbit SDA = P3^1; 	//数据线接口
sbit SCL = P3^0;	//时钟线接口

//11.0592MHZ下的延时6us
void delay(); 	

//总线初始化
void i2c_init();

//启动信号
void start();

//停止信号
void stop();

//应答信号
void respons();

//写一个字节
void writebyte(unsigned char date);

//读一个字节
unsigned char readbyte();

//向地址写一个字节数据
void write_add(unsigned char address,unsigned char date);

//向地址读一个字节数据
unsigned char read_add(unsigned char address);

//向地址写n个字节数据,数据存放在指针P指的数组中
void write_n_add(unsigned char * p,unsigned char address,unsigned char n);

//向地址读n个字节数据,数据存放在指针P指的数组中
void read_n_add(unsigned char * p,unsigned char address,unsigned char n);

#endif
