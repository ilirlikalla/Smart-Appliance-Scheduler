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
 ***************************************************************************
 ***************************************************************************/
#include "Load_shifter.h"


volatile uint32_t msTicks; /* counts 1ms timeTicks */

void delay(uint32_t dlyTicks);

/**************************************************************************//**
 * @brief SysTick_Handler
 * Interrupt Service Routine for system tick counter
 *****************************************************************************/
uint8_t op0=1,op1=1;
void SysTick_Handler(void)
{
  op0= GPIO_PinInGet(BTN_PORT, PB0);
  op1= GPIO_PinInGet(BTN_PORT, PB1);
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


char s[16],s2[16],s3[16];


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
char c[]="*camilos";

int main(void)
{
  chip_configs();
  GPIO_configs();
  UART_init();




  LCD_Init1();
  TIMER_config();
  uint8_t choice=1,oc=1;
  /* Infinite loop */
  while (1) {
	  //LCD_PutCmd ( 0x01 );
	  lcd_str("Main menu:",0,0);
	  lcd_str("start",1,7);
	  lcd_str("scan",2,7);
	  //lcd_str("ok",3,0);
	 // lcd_str("move",3,11);
	  lcd_str(">",choice,6);
	  lcd_str(" ",oc,6);
	  sprintf(s,"oc= %d ch= %d",oc, choice);
	  lcd_str(s,3,0);
	  if( op0=1 & GPIO_PinInGet(BTN_PORT, PB0)==0 )
	  {
		  GPIO->P[LED_PORT].DOUTCLR = 1 << LED1;
		  oc=choice;
		  if(choice==1)
			  choice=2;
		  else
			  choice=1;
	  }
	 // lcd_str(">",1,6);
	  //c[0]++;
	  GPIO->P[LED_PORT].DOUTCLR = 1 << LED0;
	  delay(100);
	  GPIO->P[LED_PORT].DOUTSET = 1 << LED0;
	  delay(100);
	  GPIO->P[LED_PORT].DOUTCLR = 1 << LED0;


	                   // if we have a valid character
		 // if(USART1->STATUS & (1 << 6)) { // check if TX buffer is empty
			  USART1->TXDATA = 'k';     // echo received char
			  GPIO->P[LED_PORT].DOUTSET = 1 << LED0;
//
	  //}
  }
}
