#include <reg52.h>
#include "../inc/delay_ms.h"
#include "../inc/keyboard.h" 
void baoj1();
unsigned char keyscan()
{
	unsigned char temp,key;
	key = 0xff;
	JPJK = 0xfe; 
	temp = JPJK;
	temp &= 0xf0; 
	if(temp != 0xf0)
	{
		delay_ms(10);
		temp = JPJK;
		temp &= 0xf0;
	   if(temp != 0xf0)
		{
			temp = JPJK;
			baoj1();
			switch(temp)
			{
				case 0xee: key = 1;break;
				case 0xde: key = 2;break;
				case 0xbe: key = 3;break;
				case 0x7e: key = 0x0a;break;
			}
			while(temp != 0xf0)
			{
				temp = JPJK;
				temp &= 0xf0;
			}
		}
	}
	JPJK = 0xfd; 
	temp = JPJK;
	temp &= 0xf0;
	if(temp != 0xf0)
	{
		delay_ms(10);
		temp = JPJK;
		temp &= 0xf0;
	   if(temp != 0xf0)
		{
			temp = JPJK;
			baoj1();
			switch(temp)
			{
				case 0xed: key = 4;break;
				case 0xdd: key = 5;break;
				case 0xbd: key = 6;break;
				case 0x7d: key = 0x0b;break;
			}
			while(temp != 0xf0)
			{
				temp = JPJK;
				temp &= 0xf0;
			}
		}
	}
	JPJK = 0xfb; 
	temp = JPJK;
	temp &= 0xf0;
	if(temp != 0xf0)
	{
		delay_ms(10);
		temp = JPJK;
		temp &= 0xf0;
	   if(temp != 0xf0)
		{
			temp = JPJK;
			baoj1();
			switch(temp)
			{
				case 0xeb: key = 7;break;
				case 0xdb: key = 8;break;
				case 0xbb: key = 9;break;
				case 0x7b: key = 0x0c;break;
			}
			while(temp != 0xf0)
			{
				temp = JPJK;
				temp &= 0xf0;
			}
		}
	}
	JPJK = 0xf7; 
	temp = JPJK;
	temp &= 0xf0;
	if(temp != 0xf0)
	{
		delay_ms(10);
		temp = JPJK;
		temp &= 0xf0;
	   if(temp != 0xf0)
		{
			temp = JPJK;
			baoj1();
			switch(temp)
			{
				case 0xe7: key = 0;break;
				case 0xd7: key = 0;break;
				case 0xb7: key = 0x0f;break;
				case 0x77: key = 0x0d;break;
			}
			while(temp != 0xf0)
			{
				temp = JPJK;
				temp &= 0xf0;
			}
		}
	}
   return key; 
}
