#include <stdint.h>

#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "em_system.h"
#include "em_timer.h"

#include <string.h>     // required for strlen() function
//#iclude "LCD.c" //lcd functions
// port definitions:
#define COM_PORT gpioPortD // USART location #1: PD0 and PD1
#define UART_TX_pin 7      // PD0
#define UART_RX_pin 6      // PD1
#define LED_PORT gpioPortE
#define BTN_PORT gpioPortB

#define LCD_D4 0
#define LCD_D5 1
#define LCD_D6 2
#define LCD_D7 3
#define LCD_EN 4
#define LCD_RS 5
#define LED0 2
#define LED1 3
#define PB0 9
#define PB1 10


void LCD_Init1 ( void );
#define LCD_SetPosition(a) LCD_PutCmd( (a) | 0x80)
//void LCD_SetPosition ( unsigned int c );
void LCD_PutCmd ( unsigned int c );
void LCD_PulseEnable ( void );

void upper (unsigned int c);
void lower(unsigned int c);
void LCD_PutChar ( unsigned int c );