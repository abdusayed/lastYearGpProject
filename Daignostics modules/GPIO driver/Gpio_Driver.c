
#include "Gpio_Driver.h"
#ifndef uart_h
#define uart_h
#include "UART.h"
#endif
#include"hw_types.h"
#include"Bit Manpulation.h"

const uint32 _uint32_BaseAddress[]=
 {
    0x40004000,
    0x40005000,
    0x40006000,
    0x40007000,
    0x40024000,
    0x40025000,
 };

#define GPIOAMSEL 0x528
#define GPIO_CLK  0x608
#define DIGITAL_OFFSET 0x51c
/****************************************************************************************/
/*    Function Description    : This function Enables a specific pin to the UART using  */
/*                              GPIOAFSEL register and selects uart peripheral function */
/*                              using GPIOPCTL register                                 */
/*    Parameter in            : uint8 index (index of the uart module 0 to 7)           */
/*    Parameter inout         : None                                                    */
/*    Parameter out           : None                                                    */
/*    Return value            : None                                                    */
/****************************************************************************************/
void GPIO_vidEnableAfselAndControl(uint8 channelNum){

    uint32 _ui32PortBaseAddress;
    Enum_Port_Type _Port          = portObj.Port;


    switch(channelNum){
        case(UART0):
            _ui32PortBaseAddress   = _uint32_BaseAddress[0] ;
            /*SET THE ASFEL REG for the appropriate pins to work as alternative function*/
            HWREG(_ui32PortBaseAddress+AFSEL_OFFSET)    |= AFSEL_UART0_PORTA;
            /*Select the UART function from CONTROL REG  */
            HWREG(_ui32PortBaseAddress+GPIOPCTL_OFFSET) &= ZERO_MASK_PIN0_PIN1;
            HWREG(_ui32PortBaseAddress+GPIOPCTL_OFFSET) |= GPIOPCTL_ENABLE_UART;
            HWREG(_ui32PortBaseAddress+GPIODEN)          = DEN_PIN0_PIN1;
             //Digital ENABLE GPIO PINS //
        break;

        case(UART1):
            //CHECK WHICH PORT FOR UART1//
            if(_Port == PORTB){
             _ui32PortBaseAddress   = _uint32_BaseAddress[1] ;
            /*SET THE ASFEL REG for the appropriate pins to work as alternative function*/
            HWREG(_ui32PortBaseAddress+AFSEL_OFFSET)    |= AFSEL_UART1_PORTB;
            /*Select the UART function from CONTROL REG  */
            HWREG(_ui32PortBaseAddress+GPIOPCTL_OFFSET) &= ZERO_MASK_PIN0_PIN1;
            HWREG(_ui32PortBaseAddress+GPIOPCTL_OFFSET) |= GPIOPCTL_ENABLE_UART;
            //ENABLE THE GPIO PINS //
            HWREG(_ui32PortBaseAddress+GPIODEN)          = DEN_PIN0_PIN1;
            }
            /*PORTC*/
            else if(_Port == PORTC){
             _ui32PortBaseAddress   = _uint32_BaseAddress[2] ;
            /*SET THE ASFEL REG for the appropriate pins to work as alternative function*/
            HWREG(_ui32PortBaseAddress+AFSEL_OFFSET)    |= AFSEL_UART1_PORTC;
            /*Select the UART function from CONTROL REG  */
            HWREG(_ui32PortBaseAddress+GPIOPCTL_OFFSET) &= ZERO_MASK_PIN0_PIN1;
            HWREG(_ui32PortBaseAddress+GPIOPCTL_OFFSET) |= GPIOPCTL_ENABLE_UART1;
            //ENABLE THE GPIO PINS //
            HWREG(_ui32PortBaseAddress+GPIODEN)          = DEN_PIN0_PIN1;
            }else{
                /*return error*/
            }
        ;

        case(UART2):
            /*SET THE ASFEL REG for the appropriate pins to work as alternative function*/
            HWREG(_ui32PortBaseAddress+AFSEL_OFFSET)    |= AFSEL_UART2_PORTD;
            /*Select the UART function from CONTROL REG  */
            HWREG(_ui32PortBaseAddress+GPIOPCTL_OFFSET) &= ZERO_MASK_PIN6_PIN7;
            HWREG(_ui32PortBaseAddress+GPIOPCTL_OFFSET) |= GPIOPCTL_ENABLE_UART;            
            //ENABLE THE GPIO PINS //
            HWREG(_ui32PortBaseAddress+GPIODEN)         = DEN_PIN6_PIN7;            
         break;

        case(UART3):
            /*SET THE ASFEL REG for the appropriate pins to work as alternative function*/
            HWREG(_ui32PortBaseAddress+AFSEL_OFFSET)    |= AFSEL_UART3_PORTC;
            /*Select the UART function from CONTROL REG  */
            HWREG(_ui32PortBaseAddress+GPIOPCTL_OFFSET) &= ZERO_MASK_PIN6_PIN7;
            HWREG(_ui32PortBaseAddress+GPIOPCTL_OFFSET) |= GPIOPCTL_ENABLE_UART;
            //ENABLE THE GPIO PINS //
            HWREG(_ui32PortBaseAddress+GPIODEN)         = DEN_PIN6_PIN7;
         break;
            
        case(UART4):
            /*SET THE ASFEL REG for the appropriate pins to work as alternative function*/
            HWREG(_ui32PortBaseAddress+AFSEL_OFFSET)    |= AFSEL_UART3_PORTC;
            /*Select the UART function from CONTROL REG  */
            HWREG(_ui32PortBaseAddress+GPIOPCTL_OFFSET) &= ZERO_MASK_PIN4_PIN5;
            HWREG(_ui32PortBaseAddress+GPIOPCTL_OFFSET) |= GPIOPCTL_ENABLE_UART;
            //ENABLE THE GPIO PINS //
            HWREG(_ui32PortBaseAddress+GPIODEN)          = DEN_PIN4_PIN5;
         break;
            
        case(UART5):
            /*SET THE ASFEL REG for the appropriate pins to work as alternative function*/
            HWREG(_ui32PortBaseAddress+AFSEL_OFFSET)    |= AFSEL_UART5_PORTE;
            /*Select the UART function from CONTROL REG  */
            HWREG(_ui32PortBaseAddress+GPIOPCTL_OFFSET) &= ZERO_MASK_PIN4_PIN5;
            HWREG(_ui32PortBaseAddress+GPIOPCTL_OFFSET) |= GPIOPCTL_ENABLE_UART;
            //ENABLE THE GPIO PINS //
            HWREG(_ui32PortBaseAddress+GPIODEN)          = DEN_PIN4_PIN5;
         break;
            
        case(UART6):
            /*SET THE ASFEL REG for the appropriate pins to work as alternative function*/
            HWREG(_ui32PortBaseAddress+AFSEL_OFFSET)  |= AFSEL_UART6_PORTD ;
            /*Select the UART function from CONTROL REG  */
            HWREG(_ui32PortBaseAddress+GPIOPCTL_OFFSET) &= ZERO_MASK_PIN4_PIN5;
            HWREG(_ui32PortBaseAddress+GPIOPCTL_OFFSET) |= GPIOPCTL_ENABLE_UART;
            //ENABLE THE GPIO PINS //
            HWREG(_ui32PortBaseAddress+GPIODEN)          = DEN_PIN4_PIN5;
         break;
            
        case(UART7):
            /*SET THE ASFEL REG for the appropriate pins to work as alternative function*/
            HWREG(_ui32PortBaseAddress+AFSEL_OFFSET)    |= AFSEL_UART7_PORTE;
            /*Select the UART function from CONTROL REG  */
            HWREG(_ui32PortBaseAddress+GPIOPCTL_OFFSET) &= ZERO_MASK_PIN0_PIN1;
            HWREG(_ui32PortBaseAddress+GPIOPCTL_OFFSET) |= GPIOPCTL_ENABLE_UART;
            //ENABLE THE GPIO PINS //
            HWREG(_ui32PortBaseAddress+GPIODEN)          = DEN_PIN0_PIN1;
         break;
            
    };
}
/****************************************************************************************/
/*    Function Description    : Enable the GPIO clock for Requested port                */
/*    Parameter in            : uint8 index (index of the uart module 0 to 7)           */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : None                                                    */
/*    Return value            : None                                                    */
/****************************************************************************************/
 void UART_vidGpioClockEnable(){
    Enum_Port_Type _Port  = portObj.Port;
    HWREG(RCGC_Base+RCGC2) |= (1<<_Port);
    HWREG(RCGC_Base+GPIO_CLK) |=  (1<<_Port);
}

/****************************************************************************************/
/*    Function Description    : Diable the GPIO clock                                   */
/*    Parameter in            : uint8 index (index of the uart module 0 to 7)           */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : None                                                    */
/*    Return value            : None                                                    */
/****************************************************************************************/
void UART_vidGpioClockDisable(){
    Enum_Port_Type _Port  = portObj.Port;
    HWREG(RCGC_Base+RCGC2)    &= ~(1<<_Port);
    HWREG(RCGC_Base+GPIO_CLK) &= ~(1<<_Port);
}

