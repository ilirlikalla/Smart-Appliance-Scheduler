#include "Load_shifter.h"

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
	 GPIO_PinModeSet(BTN_PORT, PB0, gpioModeInput, 9);
	 GPIO_PinModeSet(BTN_PORT, PB1, gpioModeInput, 10);
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
