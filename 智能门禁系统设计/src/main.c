#include <reg52.h>
#include "../inc/delay_ms.h"
#include  "../inc/keyboard.h"
#include "../inc/i2c.h"
#include "../inc/lcd.h"
#include "../inc/delay_ms.h"
#include "../inc/password.h"
#include "../inc/rtc.h"

#define uchar unsigned char
#define uint unsigned int
#define A 0x0a //����ģʽ
#define B 0x0b  //�޸�����
#define D 0x0d //����
#define enter 0x0c //ȷ������
#define backspace 0x0f //�˸�

sbit baojing = P3^7; //�������ӿ�
sbit lock = P3^3;	//���ź�(ʹ�õƴ���)
sbit set = P3^2;
uchar idata mima_5[6] = {1,2,3,4,5,6}; //��ʼ����Ϊ��123456


uchar time[] = "12:00:00";	//��ʼʱ���ַ���
uchar date[] = "2019-02-05";	//��ʼ�����ַ���

/*����Ҫ�޸ĳ�ʼ����/ʱ�䣬��ͬʱ�޸� �����ַ��� �Լ� ������Ӧ���� */

int year = 2019, hold;
uchar month = 2, day = 5, hour = 12, minute = 0, second = 0, x = 0;
uchar judge[13] = {0,31,0,31,30,31,30,31,31,30,31,30,31};	//�·��ж�(��Ҫ�����ƽ����µ�����)

uchar flag_change; 
uchar aa;//����������Ĵ����������α���
uchar bb;
uchar flag_t0;

//��������
void baoj1()
{
	int i;
	for(i = 0;i < 5; i++)
	{
		baojing = 1;
		delay_ms(5);
		baojing = 0;
		delay_ms(5);	
	}

}

void baoj()
{
	uchar i;
	for(i = 0; i < 10; i++)
		baoj1();
}

//ʹ�ü�����1����ʱ�Ӹ���
void update(void) interrupt 3
{
	TH1 = (65535 - 50000) / 256;
	TL1 = (65535 - 50000) % 256;
	x++;
	
	if(year%400==0||(year%4==0&&year%100!=0))
		judge[2] = 29;
	else
		judge[2] = 28;
   	
	if(x == 120){
		x = 0;
		if(++second >= 60){
			second = 0;	
			if(++minute >= 60){
				minute = 0;				
				if(++hour >= 24){
					hour = 0;				
					if(++day >= judge[month]){
						day = 1;
						if(++month >= 12){
							month = 1;
							++year;
						}
					}
				}
			}
		}
	}
    
  hold = second;
	time[7] = hold%10 + '0';
	hold /= 10;
	time[6] = hold + '0';   

  hold = minute;
	time[4] = minute%10 + '0';
	hold /= 10;
	time[3] = hold + '0'; 

    hold = hour;
	time[1] = hour%10 + '0';
	hold /= 10;
	time[0] = hold + '0';
					
	hold = day;
	date[9] = day%10 + '0';
	hold /= 10;
	date[8] = hold + '0';

  hold = month;
	date[6] = month%10 + '0';
	hold /= 10;
	date[5] = hold + '0';
							
	hold = year/10;
	date[3] = year%10 + '0';
	date[2] = hold%10 + '0';
	hold /= 10;
	date[1] = hold%10 + '0';
	hold /= 10;
	date[0] = hold + '0';
}

uchar step_choose(void)
{
	uchar key;
	key = 0xff;
	write_com(0x06);
  write_com(0x01);
	while((key != A) && (key != B)){
		display(time,date);
		key = keyscan();	
	}
	return key;
}

//���봦��
void mimachuli() 
{
	uchar key,i;
	uchar idata mima_1[6]={' ',' ',' ',' ',' ',' '};//������뻺����
	uchar idata mima_2[6]={' ',' ',' ',' ',' ',' '};
	uchar idata mima_3[6]={' ',' ',' ',' ',' ',' '};

	key = step_choose();
	if(key == A)//A������,�����������룬����
	{
		read_n_add(mima_1,0x00,6);
		write_com(0x06);//дһ���ַ����ַָ��� 1 
		write_com(0x01);//��ʾ���㣬����ָ������
		write_com(0x0f);//��ʾ���
		lcd_pos(0,0);
		write_str(" press password ");		
	
		if(input(mima_2)) //������������
		{
			if(check(mima_2,mima_1)) //������ȷ
			{
				lcd_pos(0,0);
				write_com(0x0c);
	        	write_com(0x06);//дһ���ַ����ַָ��� 1 
	         	write_com(0x01);//��ʾ���㣬����ָ������
				write_str(" password right ");
				aa = 0; //�������������
				lock = 0; //����
				baojing = 1; //��һ��
				delay_ms(1000);
				baojing = 0;
				TR0 = 1;
				flag_t0 = 1;
				while(key != D && flag_t0) //Dû����һֱ��
				{			
					key = keyscan();
				}
				TR0 = 0;
				lock = 1;//D�����˹���
			}
			else //���� ����ȷ
			{
				lcd_pos(0,0);
				write_com(0x0c); //�ع��
				write_com(0x06);//дһ���ַ����ַָ��� 1 
				write_com(0x01);//��ʾ���㣬����ָ������
				write_str(" password wrong");
				delay_ms(1000);
				aa++;
				if(aa == 4)
				{
					aa = 0;
			    	i = 20; //���벻��ȷ����
					while(i--)
					 baoj();
				}

			}
		}
		else //����û��������ȷ�����
		{
			lcd_pos(0,0);
			write_com(0x0c); //�ع��
	   	write_com(0x06);//дһ���ַ����ַָ��� 1 
		   write_com(0x01);//��ʾ���㣬����ָ������
			write_str(" password wrong");
			delay_ms(1000);
			aa++;
			if(aa == 4)
			{
				aa = 0;
		    	i = 20; //���벻��ȷ����
				while(i--)
				 baoj();
			}

		}
	}

	if(key == B)//B������,�޸�����
	{
		read_n_add(mima_1,0x00,6);
		write_com(0x06);//дһ���ַ����ַָ��� 1 
		write_com(0x01);//��ʾ���㣬����ָ������
		write_com(0x0f);//��ʾ���
		lcd_pos(0,0);
		write_str(" input password");		
		write_com(0x0f);//��ʾ���	
		if(input(mima_2)) //������������
		{
			if(check(mima_2,mima_1)) //������ȷ
			{
				lcd_pos(0,0);
				write_com(0x0c);
	      write_com(0x06);//дһ���ַ����ַָ��� 1 
	      write_com(0x01);//��ʾ���㣬����ָ������
				write_str("password right ");
				aa = 0; //�������������
				delay_ms(1500);
				flag_change = 1;
				while(flag_change) //���濪ʼ�޸�����
				{
					write_com(0x06);//дһ���ַ����ַָ��� 1 
					write_com(0x01);//��ʾ���㣬����ָ������
					write_com(0x0f);//��ʾ���
					lcd_pos(0,0);
					write_str("In new password");
					delay_ms(1500);
					if(input(mima_2)) //������������
					{

						lcd_pos(0,0);
						write_com(0x0c);
			      write_com(0x06);//дһ���ַ����ַָ��� 1 
			      write_com(0x01);//��ʾ���㣬����ָ������
						write_str("Input new pass"); //ȷ��������
						lcd_pos(1,0);
						write_str("word again");
						delay_ms(2000);
						lcd_pos(0,0);
						write_com(0x0f);//��ʾ���
			      write_com(0x06);//дһ���ַ����ַָ��� 1 
			      write_com(0x01);//��ʾ���㣬����ָ������
						write_str("In new password");						
							if(input(mima_3)) //������������
							{
								if(check(mima_2,mima_3)) //������ȷ
								{
									lcd_pos(0,0);
									write_com(0x0c);
						      write_com(0x06);//дһ���ַ����ַָ��� 1 
						      write_com(0x01);//��ʾ���㣬����ָ������
									write_str("password has");
									lcd_pos(1,0);
									write_str("change already");
									write_n_add(mima_3,0x00,6); //���޸ĵ�������24C02
									delay_ms(2000);
									flag_change = 0;
								}
								else //���� ����ȷ
								{
									lcd_pos(0,0);
									write_com(0x0c); //�ع��
									write_com(0x06);//дһ���ַ����ַָ��� 1 
									write_com(0x01);//��ʾ���㣬����ָ������
									write_str("password wrong");
									delay_ms(1000);
									aa++;
									if(aa == 4)
									{
										aa = 0;
								    	i = 20; //3���������벻��ȷ����
										while(i--)
										 baoj();
									}
									flag_change = 0;
								}
							}
							else //����û��������ȷ�����
							{
								lcd_pos(0,0);
								write_com(0x0c); //�ع��
						   	write_com(0x06);//дһ���ַ����ַָ��� 1 
							  write_com(0x01);//��ʾ���㣬����ָ������
								write_str(" password wrong");
								delay_ms(1000);
								aa++;
								if(aa == 4)
								{
									aa = 0;
							    i = 20; //3���������벻��ȷ����
									while(i--)
									 baoj();
								}
							}
						
					}
					else //����û��������ȷ�����
					{
						lcd_pos(0,0);
						write_com(0x0c); //�ع��
				   	write_com(0x06);//дһ���ַ����ַָ��� 1 
					  write_com(0x01);//��ʾ���㣬����ָ������
						write_str("password wrong");
						delay_ms(1000);
						flag_change = 0;
						aa++;
						if(aa == 4)
						{
							aa = 0;
					    i = 20; //3���������벻��ȷ����
							while(i--)
							 baoj();
						}
					}
									
				}
			}
			else //���� ����ȷ
			{
				lcd_pos(0,0);
				write_com(0x0c); //�ع��
				write_com(0x06);//дһ���ַ����ַָ��� 1 
				write_com(0x01);//��ʾ���㣬����ָ������
				write_str("password wrong");
				delay_ms(1000);
				aa++;
				if(aa == 4)
				{
					aa = 0;
			    i = 20; //3���������벻��ȷ����
					while(i--)
					 baoj();
				}
			}
		}
		else //����û��������ȷ�����
		{
			lcd_pos(0,0);
			write_com(0x0c); //�ع��
	   	write_com(0x06);//дһ���ַ����ַָ��� 1 
		   write_com(0x01);//��ʾ���㣬����ָ������
			write_str("password wrong");
			delay_ms(1000);
			aa++;
			if(aa == 4)
			{
				aa = 0;
		    i = 20; //3���������벻��ȷ����
				while(i--)
				 baoj();
			}
		}		
	}

}

//ʹ���жϽ�����������(reset)����
void int0() interrupt 0
{
	delay_ms(2000);
	if(!set)
	{
		lcd_pos(0,0);
		write_com(0x0c); 
	  write_com(0x06);
		write_com(0x01);
		i2c_init();
		write_n_add(mima_5,0x00,6);
		write_str("password renew");
		lcd_pos(1,0);
		write_str("already");
		delay_ms(1000);
		lcd_pos(0,0);
		write_com(0x0c); 
	  write_com(0x06); 
		write_com(0x01);
	}
}

void timer0() interrupt 1 
{
	TH0 = 0x4c;
	TL0 = 0x00;
	bb++;
	if(bb == 200)
	{
		bb = 0;
		flag_t0 = 0;
	}

}
void main()
{
	//��ʼ����ز���/����
	lcd_init();	
	i2c_init();
	baojing = 0;
	lock = 1; 
	TMOD = 0x01;
	EA = 1;
	ET0 = 1;
	EX0 = 1; 
	IT0 = 1;
	TR0 = 1;
	TH0 = 0x4c;
	TL0 = 0x00;
  ET1 = 1;
	TR1 = 1;
	while(1)
	{
	  mimachuli(); 
	}
}



