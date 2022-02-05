#include<reg52.h>

void delay(unsigned int k);
sbit LED = P0^0; //LED
sbit led_en = P1^2; //LED使能端 高导通
sbit wei = P1^1; //数码管位控制
sbit Line = P1^3; //点阵行控制
sbit lcd_en = P1^7; //1602液晶使能端
sbit duan = P1^0;  //数码管段码控制

sbit Key = P2^4; //s6按键

unsigned int i,j;

unsigned int table[] = {
	0x76,0x79,0x38,0x38,0x3f
};  //duan

unsigned int table2[] = {
	0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f
};   //wei

void main()
{
	lcd_en = 0;
	P0 = 0x00;
	Line = 0;
	P0 = 0xff;
	led_en = 0;
	
	i = 0;
	
	duan = 1;
	P0 = table[0];
	duan = 0;  //初始化段码，之后一直不变
	
	while(1)
	{
		wei = 1;
		P0 = table2[i];
		wei = 0;
		if(Key == 0) {
			delay(2);  //软件防误触
			if(Key == 0) {
				i=++i%8;
			}
			delay(40); //延迟判定下一次按钮，防止出现重影
		}
	}
}

void delay(unsigned int k)
{
	unsigned int z,x;
	for(z = 0;z < k;z++) {
		for(x = 0;x < 1827;x++);
	}
}
