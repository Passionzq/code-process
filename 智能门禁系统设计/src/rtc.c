#include "../inc/rtc.h"
#include "../inc/lcd.h"

void display(char* time, char* date){
	lcd_pos(0,2);
	write_str(date);
	lcd_pos(1,3);
	write_str(time);
}
