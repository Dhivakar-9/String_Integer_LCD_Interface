/* write an ECP to display string on 16x2 alphanumeric LCD using LPC2129 */

#include<LPC21XX.H>
#include "delay.c"

#define LCD_D 0xff
#define RS 1<<8
#define E 1<<9

void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_STR(unsigned char*);
void LCD_INT(int);

int main(){
	LCD_INIT();
	while(1)
	{
		LCD_CMD(0x80);
		LCD_STR("Hello World");
		LCD_CMD(0xc0);
		LCD_INT(1);
		LCD_INT(-12);
		LCD_INT(-2025);
	}
}

void LCD_INIT(void){
	
	IODIR0=LCD_D|RS|E;
	LCD_CMD(0x01);
	LCD_CMD(0x02);
	LCD_CMD(0x0C);
	LCD_CMD(0x38);
}

void LCD_CMD(unsigned char cmd){
	
	IOCLR0=LCD_D;
	IOSET0=cmd;
	IOCLR0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
}

void LCD_DATA(unsigned char d){
	
	IOCLR0=LCD_D;
	IOSET0=d;
	IOSET0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
}

void LCD_STR(unsigned char *s)
{
	while(*s)
		LCD_DATA(*s++);
	
}

void LCD_INT(int n)
{
	unsigned char arr[5];
	int i=0;
	if(n==0)
		LCD_DATA('0');
	else
	{
		if(n<0)
		{
			LCD_DATA('-');
			n=-n;
		}
		while(n>0)
		{
			arr[i++]=n%10;
			n=n/10;
		}
		for(i=i-1;i>=0;i--)
			LCD_DATA(arr[i]+48);
	}
}
