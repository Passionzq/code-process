#ifndef LCD_H
#define LCD_H

#include<reg52.h> 

#define DATA P0	//LCD�ӿ�

sbit lcden = P2^0;	//LCDʹ��
sbit lcdrs = P2^1;	//LCD��������ѡ��
sbit lcdwr = P2^2;	//LCD��д����

sbit dula = P2^6;	//U1�����������
sbit wela = P2^7;	//U2�����������

//��LCDд����
void write_com(unsigned char com);

//��LCDд����
void write_data(unsigned char date);

//ȷ��������LCD����ʾ����ʼλ��(x,y)
void lcd_pos(unsigned char x,unsigned char y);

//��LCDдһ���ַ�
void write_char(unsigned char zifu);

//��LCDдһ���ַ�
void write_str(unsigned char *string);

//LCD��ʼ��
void lcd_init();

#endif