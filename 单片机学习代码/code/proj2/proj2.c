#include<reg52.h>

void delay(unsigned int k);
sbit LED = P0^0; //LED
sbit led_en = P1^2; //LED使能端 高导通
sbit wei = P1^1; //数码管位控制
sbit Line = P1^3; //点阵行控制
sbit lcd_en = P1^7; //1602液晶使能端
sbit duan = P1^0;

unsigned int i,j;

unsigned int table[] = {
	0x76,0x79,0x38,0x38,0x3f
};  //duan

unsigned int table2[] = {
	0xfe,0xfd,0xfb,0xf7,0xef
};   //wei

void main()
{
	lcd_en = 0;
	P0 = 0x00;
	Line = 0;
	P0 = 0xff;
	led_en = 0;
	while(1)
	{
		for(i = 0;i < 5;i++) {
			duan = 1;
			P0 = table[i];
			duan = 0;
			wei = 1;
			P0 = table2[i];
			wei = 0;
			delay(1);
		}
	}
}

void delay(unsigned int k)
{
	unsigned int z,x;
	for(z = 0;z < k;z++) {
		for(x = 0;x < 500;x++);
	}
}
