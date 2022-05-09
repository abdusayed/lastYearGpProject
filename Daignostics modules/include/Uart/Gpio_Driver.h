
#include"GPIO_Pbcfg.h"
/*****************************************************/
/*                                                   */
/* Ports number in RCGCGPIO REG                      */
/*                                                   */
/*****************************************************/



/*Afsel Offset */
#define AFSEL_OFFSET 0x420

/*                  Masks used select specific pins in AFSEL register        */
#define AFSEL_UART0_PORTA 0x03
#define AFSEL_UART1_PORTB 0x03
#define AFSEL_UART1_PORTC 0x30
#define AFSEL_UART2_PORTD 0xc0
#define AFSEL_UART3_PORTC 0xc0
#define AFSEL_UART4_PORTC 0x30
#define AFSEL_UART5_PORTE 0x30
#define AFSEL_UART6_PORTD 0x30
#define AFSEL_UART7_PORTE 0x03

#define DEN_PIN0_PIN1 0x03
#define DEN_PIN4_PIN5 0x30
#define DEN_PIN6_PIN7 0xc0
#define GPIODEN 0x51C

#define RCGC_Base   0x400FE000
#define RCGC2   0x108

void GPIO_vidEnableAfselAndControl(uint8 channelNum);
void UART_vidGpioClockEnable() ;
void UART_vidGpioClockDisable() ;
