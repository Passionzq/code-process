#ifndef	PASSWORD_H
#define	PASSWORD_H

#define uchar unsigned char
#define uint unsigned int
#define A 0x0a	//进入密码模式
#define B 0x0b 	//修改密码
#define enter 0x0c //确认密码
#define backspace 0x0f	//退格

//密码比对
bit check(uchar *string1,uchar *string2);

//输入密码
bit input(uchar * mima);

#endif

