/**************************************************************************//**
 * @file
 * @brief Empty Project
 * @author Energy Micro AS
 * @version 3.20.2
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs Software License Agreement. See 
 * "http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt"  
 * for details. Before using this software for any purpose, you must agree to the 
 * terms of that agreement.
 *
 ******************************************************************************/
#include <stdint.h>

#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "em_system.h"

#include <string.h>     // required for strlen() function
//#iclude "LCD.c" //lcd functions
// port definitions:
#define COM_PORT gpioPortD // USART location #1: PD0 and PD1
#define UART_TX_pin 7      // PD0
#define UART_RX_pin 6      // PD1
#define LED_PORT gpioPortE


volatile uint32_t msTicks; /* counts 1ms timeTicks */

void delay(uint32_t dlyTicks);

/**************************************************************************//**
 * @brief SysTick_Handler
 * Interrupt Service Routine for system tick counter
 *****************************************************************************/
void SysTick_Handler(void)
{
  msTicks++;       /* increment counter necessary in Delay()*/
}

/**************************************************************************//**
 * @brief Delays number of msTick Systicks (typically 1 ms)
 * @param dlyTicks Number of ticks to delay
 *****************************************************************************/
void delay(uint32_t dlyTicks)
{
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks) ;
}




//lcd functions:

#define LCD_D4 0
#define LCD_D5 1
#define LCD_D6 2
#define LCD_D7 3
#define LCD_EN 4
#define LCD_RS 5
#define LED0 2
#define LED1 3
// Functions
void LCD_Init1 ( void );
void LCD_SetPosition ( unsigned int c );
void LCD_PutCmd ( unsigned int c );
void LCD_PulseEnable ( void );

void upper (unsigned int c);
void lower(unsigned int c);
void LCD_PutChar ( unsigned int c );
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
#define LCD_SetPosition(a) LCD_PutCmd( (a) | 0x80)

void LCD_PutCmd ( unsigned int c )
{
	GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_RS;
/* this subroutine works specifically for 4-bit Port A */
	upper ( c ); /* send high nibble */
	delay(2);
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
	delay(10); // was 10
	GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_EN ;//LCD_EN =0;
	delay(10);

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
	if(c & 0x80) GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D7; else GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D7;
	if(c & 0x40) GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D6; else GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D6;
	if(c & 0x20) GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D5; else GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D5;
	if(c & 0x10) GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D4; else GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D4;
}
void lower(unsigned int c)
{
	if(c & 0x08) GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D7; else GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D7;
	if(c & 0x04) GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D6; else GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D6;
	if(c & 0x02) GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D5; else GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D5;
	if(c & 0x01) GPIO->P[COM_PORT].DOUTSET = 1 << LCD_D4; else GPIO->P[COM_PORT].DOUTCLR = 1 << LCD_D4;
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
void lcd_str( char *c )
{LCD_SetPosition(0x00);
    int i=0,n=40;
    for(i=0;i<strlen(c);i++)
    {
        LCD_PutChar(c[i]);


    }

}

// configurations:
void chip_configs()
{
	/* Chip errata */
	  CHIP_Init();
	  if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000)) while (1) ;
	    //if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 24000)) while (1) ;


	  CMU_ClockDivSet(cmuClock_HF, cmuClkDiv_2);       // Set HF clock divider to /2 to keep core frequency < 32MHz  core_freq= 24 MHz
	  CMU_OscillatorEnable(cmuOsc_HFXO, true, true);   // Enable XTAL Osc and wait to stabilize  	  CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO); // Select HF XTAL osc as system clock source. 48MHz XTAL,
	  CMU_OscillatorEnable(cmuOsc_HFXO, true, true);   // Enable XTAL Osc and wait to stabilize
	  CMU_ClockEnable(cmuClock_GPIO, true);            // Enable GPIO peripheral clock
	  CMU_ClockEnable(cmuClock_USART1, true);          // Enable USART1 peripheral clock

}
void GPIO_configs()
{
	 GPIO_PinModeSet(COM_PORT, UART_TX_pin, gpioModePushPull, 7); // Configure UART TX pin as digital output, initialize high since UART TX idles high (otherwise glitches can occur)
	 GPIO_PinModeSet(COM_PORT, UART_RX_pin, gpioModeInput, 6);    // Configure UART RX pin as input (no filter)
	 GPIO_PinModeSet(COM_PORT, LCD_EN, gpioModePushPull, 4);
	 GPIO_PinModeSet(COM_PORT, LCD_RS, gpioModePushPull, 5);
	 GPIO_PinModeSet(COM_PORT, LCD_D4, gpioModePushPull, 0);
	 GPIO_PinModeSet(COM_PORT, LCD_D5, gpioModePushPull, 1);
	 GPIO_PinModeSet(COM_PORT, LCD_D7, gpioModePushPull, 3);
	 GPIO_PinModeSet(COM_PORT, LCD_D6, gpioModePushPull, 2);
	 GPIO_PinModeSet(LED_PORT, LED0, gpioModePushPull, 2);
	 GPIO_PinModeSet(LED_PORT, LED1, gpioModePushPull, 3);
}
void UART_configs()
{
	USART_InitAsync_TypeDef uartInit =  {    .enable       = usartDisable,   // Wait to enable the transmitter and receiver
    .refFreq      = 0,              // Setting refFreq to 0 will invoke the CMU_ClockFreqGet() function and measure the HFPER clock
    .baudrate     = 38400,          // Desired baud rate    .oversampling = usartOVS16,     // Set oversampling value to x16
    .databits     = usartDatabits8, // 8 data bits
    .parity       = usartNoParity,  // No parity bits
    .stopbits     = usartStopbits1, // 1 stop bit
    .mvdis        = false,          // Use majority voting
    .prsRxEnable  = false,          // Not using PRS input
    .prsRxCh      = usartPrsRxCh0,  // Doesn't matter which channel we select
    };
    USART_InitAsync(USART1, &uartInit);   // Apply configuration struct to USART1
    USART1->ROUTE = UART_ROUTE_RXPEN | UART_ROUTE_TXPEN | _UART_ROUTE_LOCATION_LOC1; // Clear RX/TX buffers and shift regs, enable transmitter and receiver pins
    USART_IntClear(USART1, _UART_IF_MASK); // Clear any USART interrupt flags
    NVIC_ClearPendingIRQ(UART1_RX_IRQn);   // Clear pending RX interrupt flag in    NVIC
    NVIC_ClearPendingIRQ(UART1_TX_IRQn);   // Clear pending TX interrupt flag in NVIC
    USART_Enable(USART1, usartEnable);     // Enable transmitter and receiver

}

// volatile uint32_t msTicks;
// interrupt:
// void SysTick_Handler(void)
// {
  // msTicks++;       /* increment counter necessary in Delay()*/
// }

// void Delay(uint32_t dlyTicks)
// {
  // uint32_t curTicks;

  // curTicks = msTicks;
  // while ((msTicks - curTicks) < dlyTicks) ;
// }
/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
char c[]="******";
int main(void)
{
  chip_configs();
  GPIO_configs();
  UART_configs();
  LCD_Init1();

  /* Infinite loop */
  while (1) {
	  lcd_str(c);
	  c[0]++;
	  GPIO->P[LED_PORT].DOUTCLR = 1 << LED0;
	  delay(100);
	  GPIO->P[LED_PORT].DOUTSET = 1 << LED0;
	  delay(100);
	  GPIO->P[LED_PORT].DOUTCLR = 1 << LED0;
	                   // if we have a valid character
		  if(USART1->STATUS & (1 << 6)) { // check if TX buffer is empty
			  USART1->TXDATA = 'k';     // echo received char
			  GPIO->P[LED_PORT].DOUTSET = 1 << LED0;

	  }
  }
}
