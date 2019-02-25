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
#define A 0x0a //密码模式
#define B 0x0b  //修改密码
#define D 0x0d //关锁
#define enter 0x0c //确认密码
#define backspace 0x0f //退格

sbit baojing = P3^7; //蜂鸣器接口
sbit lock = P3^3;	//锁信号(使用灯代替)
sbit set = P3^2;
uchar idata mima_5[6] = {1,2,3,4,5,6}; //初始密码为：123456


uchar time[] = "12:00:00";	//初始时间字符串
uchar date[] = "2019-02-05";	//初始日期字符串

/*若需要修改初始日期/时间，请同时修改 上述字符串 以及 下述相应变量 */

int year = 2019, hold;
uchar month = 2, day = 5, hour = 12, minute = 0, second = 0, x = 0;
uchar judge[13] = {0,31,0,31,30,31,30,31,31,30,31,30,31};	//月份判断(主要针对闰平年二月的天数)

uchar flag_change; 
uchar aa;//存放密码错误的次数，够三次报警
uchar bb;
uchar flag_t0;

//报警函数
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

//使用计数器1进行时钟更新
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

//密码处理
void mimachuli() 
{
	uchar key,i;
	uchar idata mima_1[6]={' ',' ',' ',' ',' ',' '};//存放密码缓冲区
	uchar idata mima_2[6]={' ',' ',' ',' ',' ',' '};
	uchar idata mima_3[6]={' ',' ',' ',' ',' ',' '};

	key = step_choose();
	if(key == A)//A被按下,接收输入密码，处理
	{
		read_n_add(mima_1,0x00,6);
		write_com(0x06);//写一个字符后地址指针加 1 
		write_com(0x01);//显示清零，数据指针清零
		write_com(0x0f);//显示光标
		lcd_pos(0,0);
		write_str(" press password ");		
	
		if(input(mima_2)) //处理输入密码
		{
			if(check(mima_2,mima_1)) //密码正确
			{
				lcd_pos(0,0);
				write_com(0x0c);
	        	write_com(0x06);//写一个字符后地址指针加 1 
	         	write_com(0x01);//显示清零，数据指针清零
				write_str(" password right ");
				aa = 0; //清除密码错误次数
				lock = 0; //开锁
				baojing = 1; //响一下
				delay_ms(1000);
				baojing = 0;
				TR0 = 1;
				flag_t0 = 1;
				while(key != D && flag_t0) //D没按下一直开
				{			
					key = keyscan();
				}
				TR0 = 0;
				lock = 1;//D按下了关锁
			}
			else //密码 不正确
			{
				lcd_pos(0,0);
				write_com(0x0c); //关光标
				write_com(0x06);//写一个字符后地址指针加 1 
				write_com(0x01);//显示清零，数据指针清零
				write_str(" password wrong");
				delay_ms(1000);
				aa++;
				if(aa == 4)
				{
					aa = 0;
			    	i = 20; //密码不正确报警
					while(i--)
					 baoj();
				}

			}
		}
		else //密码没有输入正确或完成
		{
			lcd_pos(0,0);
			write_com(0x0c); //关光标
	   	write_com(0x06);//写一个字符后地址指针加 1 
		   write_com(0x01);//显示清零，数据指针清零
			write_str(" password wrong");
			delay_ms(1000);
			aa++;
			if(aa == 4)
			{
				aa = 0;
		    	i = 20; //密码不正确报警
				while(i--)
				 baoj();
			}

		}
	}

	if(key == B)//B被按下,修改密码
	{
		read_n_add(mima_1,0x00,6);
		write_com(0x06);//写一个字符后地址指针加 1 
		write_com(0x01);//显示清零，数据指针清零
		write_com(0x0f);//显示光标
		lcd_pos(0,0);
		write_str(" input password");		
		write_com(0x0f);//显示光标	
		if(input(mima_2)) //处理输入密码
		{
			if(check(mima_2,mima_1)) //密码正确
			{
				lcd_pos(0,0);
				write_com(0x0c);
	      write_com(0x06);//写一个字符后地址指针加 1 
	      write_com(0x01);//显示清零，数据指针清零
				write_str("password right ");
				aa = 0; //清除密码错误次数
				delay_ms(1500);
				flag_change = 1;
				while(flag_change) //下面开始修改密码
				{
					write_com(0x06);//写一个字符后地址指针加 1 
					write_com(0x01);//显示清零，数据指针清零
					write_com(0x0f);//显示光标
					lcd_pos(0,0);
					write_str("In new password");
					delay_ms(1500);
					if(input(mima_2)) //处理输入密码
					{

						lcd_pos(0,0);
						write_com(0x0c);
			      write_com(0x06);//写一个字符后地址指针加 1 
			      write_com(0x01);//显示清零，数据指针清零
						write_str("Input new pass"); //确定新密码
						lcd_pos(1,0);
						write_str("word again");
						delay_ms(2000);
						lcd_pos(0,0);
						write_com(0x0f);//显示光标
			      write_com(0x06);//写一个字符后地址指针加 1 
			      write_com(0x01);//显示清零，数据指针清零
						write_str("In new password");						
							if(input(mima_3)) //处理输入密码
							{
								if(check(mima_2,mima_3)) //密码正确
								{
									lcd_pos(0,0);
									write_com(0x0c);
						      write_com(0x06);//写一个字符后地址指针加 1 
						      write_com(0x01);//显示清零，数据指针清零
									write_str("password has");
									lcd_pos(1,0);
									write_str("change already");
									write_n_add(mima_3,0x00,6); //把修改的密码存进24C02
									delay_ms(2000);
									flag_change = 0;
								}
								else //密码 不正确
								{
									lcd_pos(0,0);
									write_com(0x0c); //关光标
									write_com(0x06);//写一个字符后地址指针加 1 
									write_com(0x01);//显示清零，数据指针清零
									write_str("password wrong");
									delay_ms(1000);
									aa++;
									if(aa == 4)
									{
										aa = 0;
								    	i = 20; //3次输入密码不正确报警
										while(i--)
										 baoj();
									}
									flag_change = 0;
								}
							}
							else //密码没有输入正确或完成
							{
								lcd_pos(0,0);
								write_com(0x0c); //关光标
						   	write_com(0x06);//写一个字符后地址指针加 1 
							  write_com(0x01);//显示清零，数据指针清零
								write_str(" password wrong");
								delay_ms(1000);
								aa++;
								if(aa == 4)
								{
									aa = 0;
							    i = 20; //3次输入密码不正确报警
									while(i--)
									 baoj();
								}
							}
						
					}
					else //密码没有输入正确或完成
					{
						lcd_pos(0,0);
						write_com(0x0c); //关光标
				   	write_com(0x06);//写一个字符后地址指针加 1 
					  write_com(0x01);//显示清零，数据指针清零
						write_str("password wrong");
						delay_ms(1000);
						flag_change = 0;
						aa++;
						if(aa == 4)
						{
							aa = 0;
					    i = 20; //3次输入密码不正确报警
							while(i--)
							 baoj();
						}
					}
									
				}
			}
			else //密码 不正确
			{
				lcd_pos(0,0);
				write_com(0x0c); //关光标
				write_com(0x06);//写一个字符后地址指针加 1 
				write_com(0x01);//显示清零，数据指针清零
				write_str("password wrong");
				delay_ms(1000);
				aa++;
				if(aa == 4)
				{
					aa = 0;
			    i = 20; //3次输入密码不正确报警
					while(i--)
					 baoj();
				}
			}
		}
		else //密码没有输入正确或完成
		{
			lcd_pos(0,0);
			write_com(0x0c); //关光标
	   	write_com(0x06);//写一个字符后地址指针加 1 
		   write_com(0x01);//显示清零，数据指针清零
			write_str("password wrong");
			delay_ms(1000);
			aa++;
			if(aa == 4)
			{
				aa = 0;
		    i = 20; //3次输入密码不正确报警
				while(i--)
				 baoj();
			}
		}		
	}

}

//使用中断进行密码重置(reset)操作
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
	//初始化相关部件/变量
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



