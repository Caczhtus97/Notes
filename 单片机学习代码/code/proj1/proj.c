#include<reg52.h>

void delay(unsigned int k);
sbit LED = P0^0; //LED
sbit Leden = P1^2; //LED使能端 高导通
sbit wei = P1^1; //数码管位控制
sbit Line = P1^3; //点阵行控制
sbit lcd_en = P1^7; //1602液晶使能端

unsigned int i,j;

unsigned int table[] = {
	0xfd,0xf5,0xd5,0x55,
	0xff,
	0x7f,0x5f,0x57,0x55,
	0xff,
	0x00,0xff,0x00,0xff
};

void main()
{
	lcd_en = 0;
	P0 = 0x00;
	Line = 0;
	P0 = 0xff;
	wei = 0;
	Leden = 1;
	while(1)
	{
		for(i = 0;i < 14;i++) {
			P0 = table[i];
			delay(50);
		}
	}
}

void delay(unsigned int k)
{
	unsigned int z,x;
	for(z = 0;z < k;z++) {
		for(x = 0;x < 1800;x++);
	}
}
