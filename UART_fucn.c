#include "Load_shifter.h"

void UART_init()
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