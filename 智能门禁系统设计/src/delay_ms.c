//����Ϊ11.0592HZ����ʱ1ms
void delay_ms(unsigned int x)
{
   unsigned int i,j;
		for(i = 0;i < x; i++)
			for(j = 0; j < 110; j++);
}
