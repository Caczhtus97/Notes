#include<reg52.h>

void delay(unsigned int k);
void change(unsigned int *table,unsigned int num,unsigned int Size);  //取数
sbit LED = P0^0; //LED
sbit led_en = P1^2; //LED使能端 高导通
sbit wei = P1^1; //数码管位控制
sbit Line = P1^3; //点阵行控制
sbit lcd_en = P1^7; //1602液晶使能端
sbit duan = P1^0;  //数码管段码控制

sbit Key = P2^4;

unsigned int i,j;

unsigned int table[] = {
	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f
};  //duan  0~9

/*
0: 0011 1111
1: 0000 0110
2: 0101 1011
3: 0100 1111
4: 0110 0110
5: 0110 1101
6: 0111 1101
7: 0000 0111
8: 0111 1111
9: 0110 1111
*/

unsigned int table2[] = {
	0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f
};   //wei

unsigned int table3[4] = {1,0,0,0},num = 1000; //计数

void main()
{
	lcd_en = 0;
	P0 = 0x00;
	Line = 0;
	P0 = 0xff;
	led_en = 0;
	j = 0;
	while(1)
	{
		for(i = 0;i < 4; i++) {
			duan = 1;
			P0 = table[table3[i]];
			duan = 0;
			wei = 1;
			P0 = table2[i];
			wei = 0;
			delay(1);
		}
		j++;
		if(j == 40) {
			num= ++num % 10000;
			change(table3,num,4);
			j = 0;
		}
		if(Key == 0) {
			delay(7);
			if(Key == 0) {
				change(table3,0,4);
				num = 0;
			}
			delay(200);
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

void change(unsigned int *table,unsigned int num,unsigned int Size)
{
	int i = Size -1;
	while(i >= 0) {
		table[i] = num%10;
		num /= 10;
		i--;
	}
}
