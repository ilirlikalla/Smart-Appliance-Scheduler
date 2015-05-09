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

  msTicks++;       /* increment counter necessary in Delay()*/
  if(msTicks%3 ==0)
  {
	op0= GPIO_PinInGet(BTN_PORT, PB0);
	op1= GPIO_PinInGet(BTN_PORT, PB1);
  }
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
//char c[]="*camilosssssssssss";

int main(void)
{
  chip_configs();
  GPIO_configs();
  UART_init();




  LCD_Init1();
  TIMER_config();
  uint8_t choice=1,oc=2;
  /* Infinite loop */

  // flags mor manage the interface in their different menus:
  unsigned char menu = 1; // 1-> menu1; 2->menu2

  unsigned char menu1 = 0; //defines the main 2 things to do:  1-> start new task; 2-> show statues of current tasks
  unsigned char menu2 = 0; // 1-> start new task: opens the meu in which it is show  the time the sch calculates and the options for the user
  unsigned char menu3 = 0; // 2-> show status of current tasks: show the id of the task and the time in which it will be excecuted

  void menuLCD1(){

  }

  while (1) {
//<<<<<<< Updated upstream
	  //LCD_PutCmd ( 0x01 );
	  //lcd_str("Main menu:",0,0);
	//  lcd_str("start",1,7);
	 // lcd_str("scan",2,7);
	  //lcd_str("ok",3,0);
	 // lcd_str("move",3,11);

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
//=======

	  if (menu == 1){
		  lcd_str("Main Menu",0,1);
		  lcd_str("Start",1,4);
		  lcd_str("Tasks",2,4);
		  lcd_str("ok",3,0);
		  lcd_str("move",3,11);
		  //c[0]++;
		  GPIO->P[LED_PORT].DOUTCLR = 1 << LED0;
		  delay(100);
		  GPIO->P[LED_PORT].DOUTSET = 1 << LED0;
		  delay(100);
		  GPIO->P[LED_PORT].DOUTCLR = 1 << LED0;
						   // if we have a valid character
		  //if(USART1->STATUS & (1 << 6)) { // check if TX buffer is empty
		  USART1->TXDATA = 'k';     // echo received char
		  GPIO->P[LED_PORT].DOUTSET = 1 << LED0;

		  lcd_str(">",choice,3);
		  	  lcd_str(" ",oc,3);
//		  	  sprintf(s,"oc= %d ch= %d",oc, choice);
//		  	  lcd_str(s,3,0);
		  	  if( op1=1 & GPIO_PinInGet(BTN_PORT, PB1)==0 )
		  	  {
		  		 // GPIO->P[LED_PORT].DOUTCLR = 1 << LED1;
		  		  oc=choice;
		  		  if(choice==1)
		  			  choice=2;
		  		  else
		  			  choice=1;
		  	  }
		  	if( op0=1 & GPIO_PinInGet(BTN_PORT, PB0)==0 )
		  	{
		  		if(choice==1)
			      GPIO->P[LED_PORT].DOUTSET = 1 << LED1;
				else
				  GPIO->P[LED_PORT].DOUTCLR = 1 << LED1;
		  	}

	  }else if (menu == 2){

	  }else if (menu ==3){

	  }



//>>>>>>> Stashed changes
//
	  //}
  }
}
