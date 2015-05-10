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
uint8_t nextid=0;
task tasks[10]={0};
time curr_time={0};
int32_t power=0;
void time_init()
{
	//char s[20];

	//sendserial("get_time\n");


	     {    sendserial("get_time\n");
	    	 delay(1000);
			  sendserial("get_time\n");

	     }
	     while(completed==0);
		completed=0;
		sscanf(Buffer,"time %d:%d",&curr_time.h,&curr_time.m);
		sscanf(Buffer,"time %d",&curr_time.h);


}

volatile uint32_t msTicks; /* counts 1ms timeTicks */

void delay(uint32_t dlyTicks);

/**************************************************************************//**
 * @brief SysTick_Handler
 * Interrupt Service Routine for system tick counter
 *****************************************************************************/
uint8_t op0=1,op1=1;
uint8_t completed=0;
char rx_char,Buffer[256];
void USART1_RX_IRQHandler(void)
{
	static int i=0;

//	if (completed == 1)
//		return;
    while(USART1->STATUS & (1 << 7)) // while it has smth in buffer receiving
                    {   // if RX buffer contains valid data
                      Buffer[i] = USART1->RXDATA;
                      if (Buffer[i] == '\n')
                      {
                    	  completed = 1;
                    	  Buffer[i]='\0';
                    	  i = 0;
                    	  return;
                      }
                      i++;// store the data
                    }
    //if (Buffer[i-1]='\n')
    //{ completed=1; Buffer[i]='\0';}
//                    if(rx_char) {                     // if we have a valid character
//                      if(USART1->STATUS & (1 << 6)) { // check if TX buffer is empty
//                        USART1->TXDATA = rx_char;     // echo received char
//                        rx_char = 0;                  // reset temp variable
//                      }
//                    }


}
int32_t a, old_a;
void SysTick_Handler(void)
{

  msTicks++;       /* increment counter necessary in Delay()*/
  if(msTicks%60000==0 )
  {
	  ++curr_time.m;
	  if(curr_time.m==60)
	  {
		  ++curr_time.h;
		  curr_time.m=0;
	  }
  }
  if(curr_time.h==24)
  		  curr_time.h=0;


  if(msTicks%7 ==0)
  {

   	if( op1==1 & GPIO_PinInGet(BTN_PORT, PB1)==0 )
   	{
   		if((1<current && current<6) | current==7 )
   			current--;
   		if(current==1)
   		{
   			oc=choice;

   		  if(choice==1)
   			  choice=2;
   		  else
   			  choice=1;
   		}
   		if(current==6) current=1;
    }

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


char s[32],s2[16],s3[2]={0x10,'\0'};

uint8_t select=1;
void menuLCD(menu_t menu1, menu_t menu2, menu_t menu3, menu_t menu4, menu_t menu5){

	old_a=a;
	a= CAPLESENSE_getSliderPosition();

	if (current == 1){



		  lcd_str("Main Menu        ",0,1);
		  lcd_str("Start           ",1,4);
		  lcd_str("Tasks           ",2,4);
		  lcd_str("ok               ",3,0);
		  lcd_str("move",3,11);
		  //lcd_str(s2,3,3);



		  lcd_str(">",choice,3);
		  lcd_str(" ",oc,3);



		  	  if( Button0pressed )
		  	  {
				if(choice==1){
					current=2;
				}
				else if (choice == 2){
					current=6;
				}
				lcd_str("         ",0,1);
				lcd_str("         ",1,4);
				lcd_str("         ",2,4);
				lcd_str("         ",3,0);
				lcd_str("    ",3,11);
			  }op0= GPIO_PinInGet(BTN_PORT, PB0);

	}
	else if (current == 2)
	{ // start menu

		  if(a>-1 && old_a>-1)
		  if(abs(a-old_a)>2) power+=10*(a-old_a);
		  if(power<0) power=0;
		  if(power>2000) power=2000;
		  sprintf(s2,"%0004d Watts",power);
          sprintf(s,"Time: %02d:%02d",curr_time.h,curr_time.m);
		  lcd_str(s,0,1);
		  lcd_str("Power:         ",1,4);
		  lcd_str(s2,2,4);
		  lcd_str("ok               ",3,0);
		  lcd_str("back",3,11);
		  //lcd_str(">",choice,3);
		  //lcd_str(" ",oc,3);


				  	  if( Button0pressed )
				  	  {
						tasks[nextid].pow=power;
						current=3;
						   lcd_str("               ",0,1);
						  lcd_str("      ",1,0);
						  lcd_str("        ",2,4);
						  lcd_str("   ",3,0);
						  lcd_str("    ",3,11);
					  }op0= GPIO_PinInGet(BTN_PORT, PB0);
	}




	else if (current == 3)
	{

		  if(a>-1 && old_a>-1)
		  power+=(a-old_a);
		  if(power<0) power=0;
		  if(power>24) power=24;
		  sprintf(s2,"%02d hours",power);
		  sprintf(s,"Time: %02d:%02d   ",curr_time.h,curr_time.m);
		  lcd_str(s,0,1);
		  lcd_str("Duration:        ",1,4);
		  lcd_str(s2,2,4);
		  lcd_str("ok            ",3,0);
		  lcd_str("back          ",3,11);



		  if( Button0pressed )
		  {
			tasks[nextid].duration=power;
			current=4;
			select=1;
					  lcd_str(s,0,1);
					  lcd_str("        ",1,0);
					  lcd_str("          ",2,4);
					  lcd_str("   ",3,0);
					  lcd_str("   ",3,11);
		  }op0= GPIO_PinInGet(BTN_PORT, PB0);
	}



	else if (current == 4){
		if(a>-1 && old_a>-1)
				  power+=(a-old_a);
				  if(power<0) power=0;
				  if(power>24) power=24;

		  if(select==1){

		  sprintf(s2,"%02d:00 ",power);
		  sprintf(s,"Time: %02d:%02d   ",curr_time.h,curr_time.m);
		  lcd_str(s,0,1);
		  lcd_str("Deadline:        ",1,4);
		  lcd_str(s2,2,4);
		  lcd_str("ok            ",3,0);
		  lcd_str("back          ",3,11);
		  }else{
			  sprintf(s2,"%02d:%02d ",tasks[nextid].deadline.h,power);
			 		  sprintf(s,"Time: %02d:%02d   ",curr_time.h,curr_time.m);
			 		  lcd_str(s,0,1);
			 		  lcd_str("Deadline:        ",1,4);
			 		  lcd_str(s2,2,4);
			 		  lcd_str("ok            ",3,0);
			 		  lcd_str("back          ",3,11);
		  }



		  if( Button0pressed )
		  {
			if(select==1){
				select=2;
				tasks[nextid].deadline.h=power;

			}
			else{
			//tasks[nextid].duration=power;
			//tasks[nextid].id=nextid+1;
				tasks[nextid].deadline.m=power;
				tasks[nextid].id=nextid+1;
				sprintf(s,"new_task %d %d %d %d\n",tasks[nextid].id,tasks[nextid].pow,tasks[nextid].duration * 60,tasks[nextid].deadline.h);

			     sendserial(s);
			    	 delay(100);
				 sendserial(s);


			     while(completed==0);
				completed=0;
				sscanf(Buffer,"status %d %d:%d %s",&tasks[nextid].id,&tasks[nextid].deadline.h,&tasks[nextid].deadline.m,tasks[nextid].status);
				sscanf(Buffer,"status %d %d:%d",&tasks[nextid].id,&tasks[nextid].deadline.h,&tasks[nextid].deadline.m);
				sscanf(Buffer,"status %d %d",&tasks[nextid].id,&tasks[nextid].deadline.h);
				sscanf(Buffer,"status %d",&tasks[nextid].id);
				sprintf(s,"get_cost %d\n",tasks[nextid].id);
				sendserial(s);
				delay(100);
				sendserial(s);
						while(completed==0);
				completed=0;
				//sscanf(Buffer,"cost %d %d",&tasks[nextid].id,&tasks[nextid].cost);
                //(Buffer,"cost %d",&tasks[nextid].id);
                nextid++;





			current=5;
			lcd_str("                  ",0,1);
			lcd_str("          ",1,0);
			lcd_str("        ",2,4);
			lcd_str("        "  ,3,0);
			lcd_str("        ",3,11);
			}
		  }op0= GPIO_PinInGet(BTN_PORT, PB0);



		}


	else if (current == 5){
		      sprintf(s,"cost: %d cents",tasks[nextid-1].cost);
		      Buffer[5]=' ';
		      Buffer[4]=':';
			  lcd_str(Buffer,0,1);
			  //lcd_str("accept        ",1,4);
			  lcd_str("Run it now?",2,4);
			  lcd_str("yes",3,0);
			  lcd_str("later",3,11);

			  //lcd_str(">",choice,3);
			  //lcd_str(" ",oc,3);
				  if( op0=1 & GPIO_PinInGet(BTN_PORT, PB0)==0 )
				  {
					  strcpy(tasks[nextid-1].status,"running");
					  sprintf(s,"set_status %d %s\n",tasks[nextid-1].id,tasks[nextid-1].status);
					  				sendserial(s);
					  				delay(100);
					  				sendserial(s);
					  						while(completed==0);
					  				completed=0;
					current=1;
					              lcd_str("           ",0,1);
								  //lcd_str("accept        ",1,4);
								  lcd_str("                ",2,4);
								  lcd_str("        ",3,0);
								  lcd_str("      ",3,11);
					}op0= GPIO_PinInGet(BTN_PORT, PB0);

			}
	         else if (current == 6){
			      //sprintf(s,"%s",tasks[nextid-1].status);
				  lcd_str("Tasks:",0,1);
				  //lcd_str("accept        ",1,4);
				  lcd_str(tasks[nextid-1].status,2,4);
				  lcd_str("back",3,0);
				  lcd_str("home",3,11);

				  //lcd_str(">",choice,3);
				  //lcd_str(" ",oc,3);
					  if( op0=1 & GPIO_PinInGet(BTN_PORT, PB0)==0 )
					  {
						   current=1;
						}op0= GPIO_PinInGet(BTN_PORT, PB0);

				}
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
//char c[]="*camilosssssssssss";



int main(void)
{
  chip_configs();
  CAPLESENSE_Init(0);
  GPIO_configs();
  UART_init();

  LCD_Init1();
  lcd_str("connecting",1,3);
  //TIMER_config();
  while(GPIO_PinInGet(COM_PORT, Status)==0);
  lcd_str("getting time",1,2);
  time_init();

  lcd_str("did it",1,6);
   choice=1;oc=2;
   LCD_PutCmd ( 0x01 ); /* clear display */
  /* Infinite loop */
  menu_t menu1={1,2};
  menu_t menu2={2,2};
  menu_t menu3={3,2};
  menu_t menu4={4,2};
  menu_t menu5={5,2};

  current=1; //start with menu1


  // flags mor manage the interface in their different menus:
//  unsigned char menu = 1; // 1-> menu1; 2->menu2
//
//  unsigned char menu1 = 0; //defines the main 2 things to do:  1-> start new task; 2-> show statues of current tasks
//  unsigned char menu2 = 0; // 1-> start new task: opens the meu in which it is show  the time the sch calculates and the options for the user
//  unsigned char menu3 = 0; // 2-> show status of current tasks: show the id of the task and the time in which it will be excecuted


char s1[8];

  while (1) {
	 delay(100);

	menuLCD(menu1, menu2,menu3 , menu4, menu5);





//	   if(completed==1)
//	   if(Recieved)
//
//	  				{
//	  					  //getserial(s1);
//	  					  if(strcmp(Buffer,"off")==0)
//	  						  GPIO->P[LED_PORT].DOUTCLR = 1 << LED1;
//
//	  					  else if(strcmp(Buffer,"on")==0)
//	  						  GPIO->P[LED_PORT].DOUTSET = 1 << LED1;
//	  					else if(strcmp(Buffer,"blink")==0)
//	  					{
//							GPIO->P[LED_PORT].DOUTCLR = 1 << LED1;
//							delay(1000);
//							GPIO->P[LED_PORT].DOUTSET = 1 << LED1;
//							delay(1000);
//							GPIO->P[LED_PORT].DOUTCLR = 1 << LED1;
//							delay(1000);
//	  					} else
//	  					sendserial("Solar Ranger says: command wasn't recognized  :( !!! \n");
//	  					sendserial(Buffer);
//	  					completed=0;
//	  				}




  }
}

