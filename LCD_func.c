#include "Load_shifter.h"


void usdelay(uint16_t n)
{
	int i=0, j=0;
	for(i;i<n;i++)
	{   j=0;
		while(j++<24);
	}
}


//lcd functions:


// Functions

//void Delay(uint32_t dlyTicks);
void LCD_Init1 ( void ) //Initialize display
{

	delay (20); /* wait enough time after Vdd rise */

	GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_RS ; 	//LCD_RS=0;
	GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D4 ;	//LCD_D4=1;
	GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D5 ;	//LCD_D5=1;
	GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D6 ;	//LCD_D6=0;
	GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D7 ;	// LCD_D7=0;
	GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_EN ;	// LCD_EN=0;

		//PORTD = 0x03;
	LCD_PulseEnable();
	delay (6);
	LCD_PulseEnable();
	delay (1);
	LCD_PulseEnable();
	GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_RS ;	//LCD_RS=1;

	GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D4 ;	//LCD_D4=0;
	GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D5 ;	//LCD_D5=1;
	GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D6 ; 	//LCD_D6=0;
	GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D7 ;	//LCD_D7=0;
	GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_EN ;	// LCD_EN=0; //PORTD = 0x02 ; /* set 4-bit interface */
	LCD_PulseEnable();
	LCD_PutCmd ( 0x2C ); /* function set (all lines, 5x7 characters) */
	LCD_PutCmd ( 0x0C ); /* display ON, cursor off, no blink */
	LCD_PutCmd ( 0x01 ); /* clear display */
	LCD_PutCmd ( 0x06 ); /* entry mode set, increment & scroll left */
}


void LCD_PutCmd ( unsigned int c )
{
	GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_RS;
/* this subroutine works specifically for 4-bit Port A */
	upper ( c ); /* send high nibble */
	delay(1);
	LCD_PulseEnable();

	//delay(2);
	lower ( c ); /* send low nibble */
	LCD_PulseEnable();
	//delay(2);

//		if(c & 0x80) GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D7; else GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D7;
//		if(c & 0x40) GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D6; else GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D6;
//		if(c & 0x20) GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D5; else GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D5;
//		if(c & 0x10) GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D4; else GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D4;
//
//		if(c & 0x08) GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D3; else GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D3;
//		if(c & 0x04) GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D2; else GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D2;
//		if(c & 0x02) GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D1; else GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D1;
//		if(c & 0x01) GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D0; else GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D0;

}
void LCD_PulseEnable ( void )
{

	GPIO->P[COM_PORT].DOUTSET = 1 << LCD_EN ;//LCD_EN = 1;
	usdelay(220); // was 10
	GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_EN ;//LCD_EN =0;
	usdelay(220);

}
/*
void delay(void)
{
	int count;
	for(count = 1; count <100000; count++);
	Delay(2);
} */
void upper (unsigned int c)
{

	GPIO_PortOutSetVal (COM_PORT, (c>>4), 0x0F);
//	if(c & 0x80) GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D7; else GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D7;
//	if(c & 0x40) GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D6; else GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D6;
//	if(c & 0x20) GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D5; else GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D5;
//	if(c & 0x10) GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D4; else GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D4;
}
void lower(unsigned int c)
{
	GPIO_PortOutSetVal (COM_PORT, c, 0x0F);
//	if(c & 0x08) GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D7; else GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D7;
//	if(c & 0x04) GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D6; else GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D6;
//	if(c & 0x02) GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D5; else GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D5;
//	if(c & 0x01) GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D4; else GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D4;
}
void LCD_PutChar ( unsigned int c )
{
/* this subroutine works specifically for 4-bit Port A */
	GPIO->P[COM_PORT].DOUTSET = 1 << LCD_RS;
	upper ( c ); /* send high nibble */
    delay(1);
	LCD_PulseEnable();
	//delay(2);
	lower ( c ); /* send low nibble */
	LCD_PulseEnable();
	//delay(4);
	//GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_RS;
}
uint8_t pos;
void lcd_str( char *c ,uint8_t row, uint8_t col)//  indexes start at 0
{
	uint8_t line;

	if (row == 1) line= 4;
	else if (row == 2) line= 1;
	else if (row == 3) line= 5;
	else line=row;
	uint8_t p=col+ (line<<4);
	LCD_SetPosition(p);
    int i=0,n=40;
    for(i=0;i<strlen(c);i++)
    {
        LCD_PutChar(c[i]);
    }

}
