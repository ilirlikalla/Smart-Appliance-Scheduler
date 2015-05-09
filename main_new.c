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
#include "LCD_40.h"


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

// configurations:
void chip_configs()
{
	/* Chip errata */
	  CHIP_Init();
	  if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000)) while (1) ;
	    //if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 24000)) while (1) ;

	  //CMU_HFRCOBandSet(cmuHFRCOBand_1MHz);
	  CMU_ClockDivSet(cmuClock_HF, cmuClkDiv_2);       // Set HF clock divider to /2 to keep core frequency < 32MHz  core_freq= 24 MHz
	  CMU_OscillatorEnable(cmuOsc_HFXO, true, true);   // Enable XTAL Osc and wait to stabilize
	  CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO); // Select HF XTAL osc as system clock source. 48MHz XTAL,


	  CMU_ClockDivSet(cmuClock_HFPER, cmuClkDiv_1);
	  //CMU_ClockEnable(cmuClock_HFPER, true);

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
void TIMER_config()
{
	TIMER0->TOP= 0xFFFF;               // Set timer TOP value
	TIMER0->CTRL =(5<<24)|(0<<16) |(0<<0); //prescale 32
	TIMER0->CMD = 0x1;
//	TIMER_Init_TypeDef timerInit =            // Setup Timer initialization
//	{
//			.enable     = true,                     // Start timer upon configuration
//			.debugRun   = true,                     // Keep timer running even on debug halt
//			.prescale   = timerPrescale1,           // Use /1 prescaler...timer clock = HF clock = 1 MHz
//			.clkSel     = timerClkSelHFPerClk,      // Set HF peripheral clock as clock source
//			.fallAction = timerInputActionNone,     // No action on falling edge
//			.riseAction = timerInputActionNone,     // No action on rising edge
//			.mode       = timerModeUp,              // Use up-count mode
//			.dmaClrAct  = false,                    // Not using DMA
//			.quadModeX4 = false,                    // Not using quad decoder
//			.oneShot    = false,                    // Using continuous, not one-shot
//			.sync       = false,                    // Not synchronizing timer operation off of other timers
//	};
//	TIMER_Init(TIMER0, &timerInit);		// Configure and start Timer0
}
char s[16],s2[16],s3[16];
void UART_configs()
{
//	USART_InitAsync_TypeDef uartInit =  {    .enable       = usartDisable,   // Wait to enable the transmitter and receiver
//    .refFreq      = 0,              // Setting refFreq to 0 will invoke the CMU_ClockFreqGet() function and measure the HFPER clock
//    .baudrate     = 9600,          // Desired baud rate    .oversampling = usartOVS16,     // Set oversampling value to x16
//    .databits     = usartDatabits8, // 8 data bits
//    .parity       = usartNoParity,  // No parity bits
//    .stopbits     = usartStopbits1, // 1 stop bit
//    .mvdis        = false,          // Use majority voting
//    .prsRxEnable  = false,          // Not using PRS input
//    .prsRxCh      = usartPrsRxCh0,  // Doesn't matter which channel we select
//    };
//    USART_InitAsync(USART1, &uartInit);   // Apply configuration struct to USART1
	USART1->CTRL= USART1->CTRL |(0<<5);
	uint32_t fr=CMU_ClockFreqGet (cmuClock_HFPER);
	uint32_t fh=CMU_ClockFreqGet (cmuClock_HF);
	uint32_t fc=CMU_ClockFreqGet (cmuClock_CORE);
	uint8_t baud= 9600;
	sprintf(s,"f= %d",fr);
	sprintf(s2,"fc= %d",fc);
	sprintf(s3,"fh= %d %d",fh);
	uint16_t div= 4*((double)((double)fr/(16*(long)baud))-1);
	sprintf(s3,"fh= %d %d",fh,div);
	// Use default value for USART1->CTRL: asynch mode, x16 OVS, lsb first, CLK idle low
    USART1->CLKDIV = (621 << 6);                               // 152 will give 38400 baud rate (using 16-bit oversampling with 24MHz peripheral clock)
    USART1->CMD = (1 << 11) | (1 << 10) | (1 << 2) | (1 << 0); // Clear RX/TX buffers and shif regs, Enable Transmitter and Receiver
    USART1->IFC = 0x1FF9;                                      // clear all USART interrupt flags
    //USART1->CLKDIV = (621 << 6);
    USART1->ROUTE = 0x203; // Clear RX/TX buffers and shift regs, enable transmitter and receiver pins
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
char c[]="*camilos";

int main(void)
{
  chip_configs();
  GPIO_configs();
  UART_configs();
  LCD_Init1();
  TIMER_config();

  /* Infinite loop */
  while (1) {
	  lcd_str(s,0x00);
	  lcd_str(s2,0x40);
	  lcd_str(s3,0x10);
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
