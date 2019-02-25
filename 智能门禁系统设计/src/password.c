#include <reg52.h>
#include "../inc/password.h"
#include "../inc/lcd.h"
#include "../inc/keyboard.h"
#include "../inc/delay_ms.h"
#include "../inc/rtc.h"



bit check(unsigned char *string1,unsigned char *string2)
{
	unsigned char count;
	for(count = 0; count < 6; count++)
	{
		if(string1[count] != string2[count])
		return 0;
	}
	return 1;
}


bit input(uchar * mima)//ÊäÈëÃÜÂëº¯Êý
{
	unsigned char count,key;
	lcd_pos(1,0);
	for(count = 0; count < 7; count++)
	{
		delay_ms(100);
		if(count < 6)
		{
			do{key = keyscan();}
			while(key == 0xff);
			if((key != backspace) && (key != A) && (key != enter))
			{
				write_data('*');	//ÃÜÂëÒþË½±£»¤
				mima[count] = key;
			//	continue;
			}
			if(key == backspace)
			{
				if(count > 0)
				{
				    lcd_pos(1,--count);
					write_data(' ');
					mima[count] = ' ';
					lcd_pos(1,count);
					count--;
				}
			}
			if(key == enter)
			{
				lcd_pos(0,0);
				return(0);
			}
		}
		if(count==6)
		{
			do{key = keyscan();}
			while((key != backspace)&&(key != enter));
			if(key == backspace)
			{
				lcd_pos(1,--count);
				write_data(' ');
				mima[count]=' ';
				lcd_pos(1,count);
				count--;
			}
			if(key == enter)
			{
				return(1);
			}
		}
	}
	
}


