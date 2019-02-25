#ifndef	I2C_H
#define	I2C_H

sbit SDA = P3^1; 	//�����߽ӿ�
sbit SCL = P3^0;	//ʱ���߽ӿ�

//11.0592MHZ�µ���ʱ6us
void delay(); 	

//���߳�ʼ��
void i2c_init();

//�����ź�
void start();

//ֹͣ�ź�
void stop();

//Ӧ���ź�
void respons();

//дһ���ֽ�
void writebyte(unsigned char date);

//��һ���ֽ�
unsigned char readbyte();

//���ַдһ���ֽ�����
void write_add(unsigned char address,unsigned char date);

//���ַ��һ���ֽ�����
unsigned char read_add(unsigned char address);

//���ַдn���ֽ�����,���ݴ����ָ��Pָ��������
void write_n_add(unsigned char * p,unsigned char address,unsigned char n);

//���ַ��n���ֽ�����,���ݴ����ָ��Pָ��������
void read_n_add(unsigned char * p,unsigned char address,unsigned char n);

#endif
