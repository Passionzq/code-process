#ifndef	PASSWORD_H
#define	PASSWORD_H

#define uchar unsigned char
#define uint unsigned int
#define A 0x0a	//��������ģʽ
#define B 0x0b 	//�޸�����
#define enter 0x0c //ȷ������
#define backspace 0x0f	//�˸�

//����ȶ�
bit check(uchar *string1,uchar *string2);

//��������
bit input(uchar * mima);

#endif

