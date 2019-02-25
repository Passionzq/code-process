#include <reg52.h>
#include <intrins.h> 
#include "../inc/lcd.h"
#include "../inc/delay_ms.h"

 
bit lcd_busy()
{                          
    bit result;
    lcdrs = 0;
    lcdwr = 1;
    lcden = 1;
    _nop_();
    _nop_();
     result = (bit)(DATA&0x80);
    lcden = 0;
    return result; 
}

void write_com(unsigned char com) 
{
	while(lcd_busy());
    lcdwr = 0;
	  lcdrs = 0;
    lcden = 0;
	  DATA = com;
	  delay_ms(5);
    lcden = 1;
	  delay_ms(5);
    lcden = 0;
}


void write_data(unsigned char date)
{
	while(lcd_busy());
    lcdwr = 0;
  	lcdrs = 1;
    lcden = 0;
  	DATA = date;
		delay_ms(5);
    lcden = 1;
		delay_ms(5);
    lcden = 0;          
}

void write_char(unsigned char zifu)
{
	write_data(zifu);	
}

void write_str(unsigned char zifu[])
{
	unsigned char count;
	for(count=0; ;count++)
	{
		write_char(zifu[count]);
		if(zifu[count+1]=='\0')
		break;
	}
}
void lcd_pos(unsigned char x,unsigned char y)
{
	unsigned char pos;
	if(x == 0)
		x = 0x80;
	else if(x == 1)
		x = 0x80 + 0x40;
	pos = x + y;
	write_com(pos);
}
void lcd_init()
{
    dula = 0;
    wela = 1;
    lcden = 0;
    write_com(0x38);
    write_com(0x0c);
    write_com(0x06);
    write_com(0x01);
         
}
