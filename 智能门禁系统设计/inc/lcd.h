#ifndef LCD_H
#define LCD_H

#include<reg52.h> 

#define DATA P0	//LCD接口

sbit lcden = P2^0;	//LCD使能
sbit lcdrs = P2^1;	//LCD数据命令选择
sbit lcdwr = P2^2;	//LCD读写控制

sbit dula = P2^6;	//U1锁存器锁存端
sbit wela = P2^7;	//U2锁存器锁存端

//向LCD写命令
void write_com(unsigned char com);

//向LCD写数据
void write_data(unsigned char date);

//确定数据在LCD上显示的起始位置(x,y)
void lcd_pos(unsigned char x,unsigned char y);

//向LCD写一个字符
void write_char(unsigned char zifu);

//向LCD写一串字符
void write_str(unsigned char *string);

//LCD初始化
void lcd_init();

#endif