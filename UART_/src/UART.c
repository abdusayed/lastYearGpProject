/*****************************************************************************/
/*                           Included files                                  */
/*****************************************************************************/

#include"hw_uart.h"
#include"platform_Types.h"
#include"Bit Manpulation.h"
#include"UART_cfg.h"
#include"hw_types.h"
#include"UART_PBCfg.h"
#include"Gpio_Driver.h"


#ifndef uart_h
#define uart_h
#include "UART.h"
#endif
/*****************************************************************************/
/*                          Internal define                                  */
/*****************************************************************************/
#define UART_INTIALIZED     1
#define UART_UNINTIALIZED   0
/*WLEN bits(bit5 , bit 6) in UARTLCRH register */
#define WLEN_BITS 0x60
#define INTREG 0xE000E000
#define EN0    0x100
#define EN1    0x104
#define UART0_INTERRUPT_ENABLE  5
#define UART1_INTERRUPT_ENABLE  6
#define UART2_INTERRUPT_ENABLE  1
#define UART3_INTERRUPT_ENABLE  27
#define UART4_INTERRUPT_ENABLE  28
#define UART5_INTERRUPT_ENABLE  29
#define UART6_INTERRUPT_ENABLE  30
#define UART7_INTERRUPT_ENABLE  31
#define RXFE 4
#define FIFO 1

/*****************************************************/
/*                                                   */
/* Table 14-3. UART Register Map (offset)            */
/*                                                   */
/*****************************************************/
#define UARTDR               0x000
#define UARTRSR              0x004
#define UARTECR              0x004
#define UARTFR               0x018
#define UARTILPR             0x020
#define UARTIBRD             0x024
#define UARTFBRD             0x028
#define UARTLCRH             0x02C
#define UARTCTL              0x030
#define UARTIFLS             0x034
#define UARTIM               0x038
#define UARTRIS              0x03C
#define UARTMIS              0x040
#define UARTICR              0x044
#define UARTDMACTL           0x048
#define UART9BITADDR         0x0A4
#define UART9BITAMASK        0x0A8
#define UARTPP               0xFC0
#define UARTCC               0xFC8
#define UARTPeriphID4        0xFD0
#define UARTPeriphID5        0xFD4
#define UARTPeriphID6        0xFD8
#define UARTPeriphID7        0xFDC
#define UARTPeriphID0        0xFE0
#define UARTPeriphID1        0xFE4
#define UARTPeriphID2        0xFE8
#define UARTPeriphID3        0xFEC
#define UARTPCellID0         0xFF0
#define UARTPCellID1         0xFF4
#define UARTPCellID2         0xFF8
#define UARTPCellID3         0xFFC

#define UART_TXINT_MODE_EOT   0x00000010
#define     UART_TXINT_MODE_FIFO   0x00000000

/*                                      Base address                         */
#define RCGC_Base   0x400FE000
      
/*                                         Offset                            */
#define RCGC1    0x104
#define RCGCUART 0x618
#define GPIO_Clock_Enable 0x3F
#define UART_FR_RXFF 0x00000040
#define UART_FR_TXFF 0x00000020


#define IDLE                                            0U
#define INTERRUPT_LEVEL_REACHED                         1U
#define NUM_OF_REMINDED_BYTES_LESS_THAN_INTERRUPT_LEVEL 2U
 uint8 ReceiveStateMachine =  IDLE;




/*****************************************************************************/
/*                          Internal Variables                               */
/*****************************************************************************/
pf_UartRx_Cbk TXCb_Fun ;
pf_UartRx_Cbk RXCb_Fun ;
str_UartConfig_t astr_UartConfig_t[UART_MAX_NUM];
/*counter to indicate number of bytes have been received*/
uint16 InterruptReceivedFlagCounter[UART_MAX_NUM];

static boolean UART_Initialized[UART_MAX_NUM];
static const str_UartConfig_t *gpas_UartConfig  ;
static uint32 CounterBytesReceived[UART_MAX_NUM] ;
const uint32 uint32_BaseAddress[]=
 {
    0x4000C000,
    0x4000D000,
    0x4000E000,
    0x4000F000,
    0x40010000,
    0x40011000,
    0x40012000,
    0x40013000
 };

typedef struct
{
    uint8 Tx_Level;
    uint8 Rx_Level;
}str_UartFIFOLevel;

str_UartFIFOLevel  Uart_Level[UART_MAX_NUM];
extern str_Receive_Data_Info  *gArrRxRequest;
/*****************************************************************************/
/*                          UART0 interrupt                                  */
/*****************************************************************************/
/*7- To do 11:30 >> 11:47*/
/*11- To do 12:04 >> 12:*/
void UART0_Handler (void)
 {
	 if (( (HWREG(uint32_BaseAddress[UART0]+UARTRIS)) & UART_RIS_RXRIS ) != 0)
	 {
	     uint8 i ;
         /*Received Interrupt Clear*/
          HWREG(uint32_BaseAddress[UART0] + UARTICR) |= (UART_ICR_RXIC) ;
          InterruptReceivedFlagCounter[UART0]++;
          /*save the Received byte to the buffer */
         for(i = 0 ; i < Uart_Level[UART0].Rx_Level ; i++)
         {
             gArrRxRequest->ptr_Buffer[CounterBytesReceived[UART0]] = HWREG(uint32_BaseAddress[UART0] + UARTDR) ;
            /*increment the Received counter bytes*/
            CounterBytesReceived[UART0]++ ;
         }
	 }
	 else if(( (HWREG(uint32_BaseAddress[UART0]+UARTRIS)) & UART_RIS_TXRIS ) != 0 )
	 {
         /*Transmit Interrupt Clear*/
         HWREG(uint32_BaseAddress[UART0] + UARTICR) |= (UART_ICR_TXIC) ;
         (*TXCb_Fun)();
	 }
}


/*****************************************************************************/
/*                          UART1 interrupt                                  */
/*****************************************************************************/
void UART1_Handler (void)
{
    if (( (HWREG(uint32_BaseAddress[UART1]+UARTRIS)) & UART_RIS_RXRIS ) != 0)
    {
        uint8 i ;
        /*Received Interrupt Clear*/
         HWREG(uint32_BaseAddress[UART1] + UARTICR) |= (UART_ICR_RXIC) ;
         InterruptReceivedFlagCounter[UART1]++;
         /*save the Received byte to the buffer */
        for(i = 0 ; i < Uart_Level[UART1].Rx_Level ; i++)
        {
            gArrRxRequest->ptr_Buffer[CounterBytesReceived[UART1]] = HWREG(uint32_BaseAddress[UART1] + UARTDR) ;
           /*increment the Received counter bytes*/
           CounterBytesReceived[UART1]++ ;
        }
    }
    else if(( (HWREG(uint32_BaseAddress[UART1]+UARTRIS)) & UART_RIS_TXRIS ) != 0 )
    {
        /*Transmit Interrupt Clear*/
        HWREG(uint32_BaseAddress[UART1] + UARTICR) |= (UART_ICR_TXIC) ;
        (*TXCb_Fun)();
    }
}

/*****************************************************************************/
/*                          UART2 interrupt                                  */
/*****************************************************************************/
void UART2_Handler (void)
{
    if (( (HWREG(uint32_BaseAddress[UART2]+UARTRIS)) & UART_RIS_RXRIS ) != 0)
    {
        uint8 i ;
        /*Received Interrupt Clear*/
         HWREG(uint32_BaseAddress[UART2] + UARTICR) |= (UART_ICR_RXIC) ;
         InterruptReceivedFlagCounter[UART2]++;
         /*save the Received byte to the buffer */
        for(i = 0 ; i < Uart_Level[UART2].Rx_Level ; i++)
        {
            gArrRxRequest->ptr_Buffer[CounterBytesReceived[UART2]] = HWREG(uint32_BaseAddress[UART2] + UARTDR) ;
           /*increment the Received counter bytes*/
           CounterBytesReceived[UART2]++ ;
        }
    }
    else if(( (HWREG(uint32_BaseAddress[UART2]+UARTRIS)) & UART_RIS_TXRIS ) != 0 )
    {
        /*Transmit Interrupt Clear*/
        HWREG(uint32_BaseAddress[UART2] + UARTICR) |= (UART_ICR_TXIC) ;
        (*TXCb_Fun)();
    }
}

/*****************************************************************************/
/*                          UART3 interrupt                                  */
/*****************************************************************************/
void UART3_Handler (void)
{
    if (( (HWREG(uint32_BaseAddress[UART3]+UARTRIS)) & UART_RIS_RXRIS ) != 0)
    {
        uint8 i ;
        /*Received Interrupt Clear*/
         HWREG(uint32_BaseAddress[UART3] + UARTICR) |= (UART_ICR_RXIC) ;
         InterruptReceivedFlagCounter[UART3]++;
         /*save the Received byte to the buffer */
        for(i = 0 ; i < Uart_Level[UART3].Rx_Level ; i++)
        {
            gArrRxRequest->ptr_Buffer[CounterBytesReceived[UART3]] = HWREG(uint32_BaseAddress[UART3] + UARTDR) ;
           /*increment the Received counter bytes*/
           CounterBytesReceived[UART3]++ ;
        }
    }
    else if(( (HWREG(uint32_BaseAddress[UART3]+UARTRIS)) & UART_RIS_TXRIS ) != 0 )
    {
        /*Transmit Interrupt Clear*/
        HWREG(uint32_BaseAddress[UART3] + UARTICR) |= (UART_ICR_TXIC) ;
        (*TXCb_Fun)();
    }
}

/*****************************************************************************/
/*                          UART4 interrupt                                  */
/*****************************************************************************/
void UART4_Handler(void)
{
    if (( (HWREG(uint32_BaseAddress[UART4]+UARTRIS)) & UART_RIS_RXRIS ) != 0)
    {
        uint8 i ;
        /*Received Interrupt Clear*/
         HWREG(uint32_BaseAddress[UART4] + UARTICR) |= (UART_ICR_RXIC) ;
         InterruptReceivedFlagCounter[UART0]++;
         /*save the Received byte to the buffer */
        for(i = 0 ; i < Uart_Level[UART4].Rx_Level ; i++)
        {
            gArrRxRequest->ptr_Buffer[CounterBytesReceived[UART4]] = HWREG(uint32_BaseAddress[UART4] + UARTDR) ;
           /*increment the Received counter bytes*/
           CounterBytesReceived[UART4]++ ;
        }
    }
    else if(( (HWREG(uint32_BaseAddress[UART4]+UARTRIS)) & UART_RIS_TXRIS ) != 0 )
    {
        /*Transmit Interrupt Clear*/
        HWREG(uint32_BaseAddress[UART4] + UARTICR) |= (UART_ICR_TXIC) ;
        (*TXCb_Fun)();
    }
}

/*****************************************************************************/
/*                          UART5 interrupt                                  */
/*****************************************************************************/
void UART5_Handler (void)
{
    if (( (HWREG(uint32_BaseAddress[UART5]+UARTRIS)) & UART_RIS_RXRIS ) != 0)
    {
        uint8 i ;
        /*Received Interrupt Clear*/
         HWREG(uint32_BaseAddress[UART5] + UARTICR) |= (UART_ICR_RXIC) ;
         InterruptReceivedFlagCounter[UART5]++;
         /*save the Received byte to the buffer */
        for(i = 0 ; i < Uart_Level[UART5].Rx_Level ; i++)
        {
            gArrRxRequest->ptr_Buffer[CounterBytesReceived[UART5]] = HWREG(uint32_BaseAddress[UART5] + UARTDR) ;
           /*increment the Received counter bytes*/
           CounterBytesReceived[UART5]++ ;
        }
    }
    else if(( (HWREG(uint32_BaseAddress[UART5]+UARTRIS)) & UART_RIS_TXRIS ) != 0 )
    {
        /*Transmit Interrupt Clear*/
        HWREG(uint32_BaseAddress[UART5] + UARTICR) |= (UART_ICR_TXIC) ;
        (*TXCb_Fun)();
    }
}

/*****************************************************************************/
/*                          UART6 interrupt                                  */
/*****************************************************************************/
void UART6_Handler (void)
{
    if (( (HWREG(uint32_BaseAddress[UART6]+UARTRIS)) & UART_RIS_RXRIS ) != 0)
    {
        uint8 i ;
        /*Received Interrupt Clear*/
         HWREG(uint32_BaseAddress[UART6] + UARTICR) |= (UART_ICR_RXIC) ;
         InterruptReceivedFlagCounter[UART6]++;
         /*save the Received byte to the buffer */
        for(i = 0 ; i < Uart_Level[UART6].Rx_Level ; i++)
        {
            gArrRxRequest->ptr_Buffer[CounterBytesReceived[UART6]] = HWREG(uint32_BaseAddress[UART6] + UARTDR) ;
           /*increment the Received counter bytes*/
           CounterBytesReceived[UART6]++ ;
        }
    }
    else if(( (HWREG(uint32_BaseAddress[UART6]+UARTRIS)) & UART_RIS_TXRIS ) != 0 )
    {
        /*Transmit Interrupt Clear*/
        HWREG(uint32_BaseAddress[UART6] + UARTICR) |= (UART_ICR_TXIC) ;
        (*TXCb_Fun)();
    }
}

/*****************************************************************************/
/*                          UART7 interrupt                                  */
/*****************************************************************************/
void UART7_Handler (void)
{
    if (( (HWREG(uint32_BaseAddress[UART7]+UARTRIS)) & UART_RIS_RXRIS ) != 0)
    {
        uint8 i ;
        /*Received Interrupt Clear*/
         HWREG(uint32_BaseAddress[UART7] + UARTICR) |= (UART_ICR_RXIC) ;
         InterruptReceivedFlagCounter[UART7]++;
         /*save the Received byte to the buffer */
        for(i = 0 ; i < Uart_Level[UART7].Rx_Level ; i++)
        {
            gArrRxRequest->ptr_Buffer[CounterBytesReceived[UART7]] = HWREG(uint32_BaseAddress[UART7] + UARTDR) ;
           /*increment the Received counter bytes*/
           CounterBytesReceived[UART7]++ ;
        }
    }
    else if(( (HWREG(uint32_BaseAddress[UART0]+UARTRIS)) & UART_RIS_TXRIS ) != 0 )
    {
        /*Transmit Interrupt Clear*/
        HWREG(uint32_BaseAddress[UART7] + UARTICR) |= (UART_ICR_TXIC) ;
        (*TXCb_Fun)();
    }
}

/****************************************************************************************/
/*    Function Description    : Initializes the global variables						*/
/*    Parameter in            : uint8 index (index of the uart module 0 to 7)           */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : None                        			                */
/*    Return value            : None                         						    */
/****************************************************************************************/
static void InitGlobal_Variable(void)
{ 	
	TXCb_Fun  		= NULL;
	RXCb_Fun  	    = NULL;
	gpas_UartConfig = NULL;
	uint8 i  ;
	for(i = 0 ; i<UART_MAX_NUM ; i++)
	{
		UART_Initialized[i] = UART_UNINTIALIZED ;
		InterruptReceivedFlagCounter[i] = UART_UNINTIALIZED ;
		CounterBytesReceived[i]         =  UART_UNINTIALIZED ;
	}
}



/****************************************************************************************/
/*    Function Description    : Set the BuaRate 	 									*/
/*    Parameter in            : uint8 index (index of the uart module 0 to 7)           */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : None                        			                */
/*    Return value            : None                         						    */
/****************************************************************************************/
static void UART_vidSetBuadRate(uint8 Index){
	

	uint8 _ClkDiv                     = gpas_UartConfig[Index].ClkDiv;
	uint32 _BaudRate                  = gpas_UartConfig[Index].BaudRate ;
	uint32 _UARTSysClk                = gpas_UartConfig[Index].UARTSysClk ;
    uint32  _ui32uartBaseAddress      = uint32_BaseAddress[gpas_UartConfig[Index].UartNum] ;

	/*BRD = intBRD + fracBRD = UARTSysClk / (ClkDiv * BaudRate)*/
	/*get the integer part*/
	uint16 intBRD = _UARTSysClk / (_ClkDiv * _BaudRate); 

	/*get the fractional part*/
	float fracBRD = (float)(((float)(_UARTSysClk) / (float)(_ClkDiv * _BaudRate)) - intBRD);
	
	/*BRDF * 64 + 0.5*/
	fracBRD = fracBRD*64 +0.5;
	//TODO GET THE ADD FROM THE CONFIG

	HWREG(_ui32uartBaseAddress+UARTIBRD)=intBRD;
	HWREG(_ui32uartBaseAddress+UARTFBRD)=(uint8)fracBRD;
	
}

void SetFifoRXInterrupt_TriggerLevel(uint8 channel , uint32 NUM_Ofbytes)
{
    if(NUM_Ofbytes >= 14)
    {
        Uart_Level[channel].Rx_Level = 14 ;
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) &= ~(1<<3);
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) &= ~(1<<4);
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) |=  (1<<5);
    }
    else if(NUM_Ofbytes >= 12)
    {
        Uart_Level[channel].Rx_Level = 12 ;
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) |=  (1<<3);
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) |=  (1<<4);
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) &= ~(1<<5);
    }
    else if(NUM_Ofbytes >= 8)
    {
        Uart_Level[channel].Rx_Level = 8 ;
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) &= ~(1<<3);
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) |=  (1<<4);
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) &= ~(1<<5);
    }
    else if(NUM_Ofbytes >= 4)
    {
        Uart_Level[channel].Rx_Level = 4 ;
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) |=  (1<<3);
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) &= ~(1<<4);
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) &= ~(1<<5);
    }
    else
    {
        Uart_Level[channel].Rx_Level = 2 ;
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) &= ~(1<<3);
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) &= ~(1<<4);
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) &= ~(1<<5);
    }

}

void SetFifoTXInterrupt_TriggerLevel(uint8 channel , uint32 NUM_Ofbytes)
{
    if(NUM_Ofbytes >= 14)
    {
        Uart_Level[channel].Tx_Level = 14 ;
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) &= ~(1<<0);
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) &= ~(1<<1);
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) |=  (1<<2);
    }
    else if(NUM_Ofbytes >= 12)
    {
        Uart_Level[channel].Tx_Level = 12 ;
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) |=  (1<<0);
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) |=  (1<<1);
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) &= ~(1<<2);
    }
    else if(NUM_Ofbytes >= 8)
    {
        Uart_Level[channel].Tx_Level = 8 ;
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) &= ~(1<<0);
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) |=  (1<<1);
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) &= ~(1<<2);
    }
    else if(NUM_Ofbytes >= 4)
    {
        Uart_Level[channel].Tx_Level = 4 ;
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) |=  (1<<0);
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) &= ~(1<<1);
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) &= ~(1<<2);
    }
    else
    {
        Uart_Level[channel].Tx_Level = 2 ;
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) &= ~(1<<0);
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) &= ~(1<<1);
        HWREG(uint32_BaseAddress[channel]+UARTIFLS) &= ~(1<<2);
    }
}

void INT_Enable(uint8 UARTNum)
{
    if(UARTNum == UART0)
    {
        HWREG(INTREG+EN0) |= (1<<UART0_INTERRUPT_ENABLE);
    }
    else if(UARTNum == UART1)
    {
        HWREG(INTREG+EN0) |= (1<<UART1_INTERRUPT_ENABLE);
    }
    else if(UARTNum == UART2)
    {
        HWREG(INTREG+EN1) |= (1<<UART2_INTERRUPT_ENABLE);
    }
    else if(UARTNum == UART3)
    {
        HWREG(INTREG+EN1) |= (1<<UART3_INTERRUPT_ENABLE);
    }
    else if(UARTNum == UART4)
    {
        HWREG(INTREG+EN1) |= (1<<UART4_INTERRUPT_ENABLE);
    }
    else if(UARTNum == UART5)
    {
        HWREG(INTREG+EN1) |= (1<<UART5_INTERRUPT_ENABLE);
    }
    else if(UARTNum == UART6)
    {
        HWREG(INTREG+EN1) |= (1<<UART6_INTERRUPT_ENABLE);
    }
    else if(UARTNum == UART7)
    {
        HWREG(INTREG+EN1) |= (1<<UART7_INTERRUPT_ENABLE);
    }

}

/****************************************************************************************/
/*    Function Description    : Enable the UART FIFO                                    */
/*    Parameter in            : uint8 index (index of the uart module 0 to 7)           */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : None                                                    */
/*    Return value            : None                                                    */
/****************************************************************************************/
static void UART_vidFifoEnable(uint8 Index)
{
    uint32  _ui32uartBaseAddress  = uint32_BaseAddress[gpas_UartConfig[Index].UartNum] ;
    // Enable the FIFO.//
    HWREG(_ui32uartBaseAddress + UART_O_LCRH) |= UART_LCRH_FEN;
}

/****************************************************************************************/
/*    Function Description    : Enable the GPIO clock 									*/
/*    Parameter in            : uint8 index (index of the uart module 0 to 7)           */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : None                        			                */
/*    Return value            : None                         						    */
/****************************************************************************************/
static void UART_vidEnable(uint8 Index)
{
    uint32  _ui32uartBaseAddress  = uint32_BaseAddress[gpas_UartConfig[Index].UartNum] ;
	// Enable the FIFO.//
    UART_vidFifoEnable(Index);
    // Enable RX, TX, and the UART.//
    HWREG(_ui32uartBaseAddress + UART_O_CTL) |= (UART_CTL_UARTEN | UART_CTL_TXE |   UART_CTL_RXE);
}


/****************************************************************************************/
/*    Function Description    : DISable the UART FIFO                                   */
/*    Parameter in            : uint8 index (index of the uart module 0 to 7)           */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : None                                                    */
/*    Return value            : None                                                    */
/****************************************************************************************/
static void UART_vidFifoDisable(uint8 Index)
{
    uint32  _ui32uartBaseAddress  = uint32_BaseAddress[gpas_UartConfig[Index].UartNum] ;
    // Disable the FIFO.//
    HWREG(_ui32uartBaseAddress + UART_O_LCRH) &= ~(UART_LCRH_FEN);
}

/****************************************************************************************/
/*    Function Description    : Enable the UART   	 									*/
/*    Parameter in            : uint8 index (index of the uart module 0 to 7)           */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : None                        			                */
/*    Return value            : None                         						    */
/****************************************************************************************/
static void UART_vidDisable(uint8 Index)
{
    uint32  _ui32uartBaseAddress  = uint32_BaseAddress[gpas_UartConfig[Index].UartNum] ;
	
	// Wait for end of TX.//
	// BUSY bit has to by 1 if the uart is not busy//
    while(GET_BIT(HWREG(_ui32uartBaseAddress + UART_FR_Offset),UART_FR_BUSY))
    {
    }
    // Disable the FIFO.//
    UART_vidFifoDisable(Index);
    // Disable the UART.//
    HWREG(_ui32uartBaseAddress + UART_O_CTL) &= ~(UART_CTL_UARTEN | UART_CTL_TXE |
                                      UART_CTL_RXE);
}



/****************************************************************************************/
/*    Function Description    : Enable the UART clock 									*/
/*    Parameter in            : uint8 index (index of the uart module 0 to 7)           */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : None                        			                */
/*    Return value            : None                         						    */
/****************************************************************************************/

void delay(uint32 counter)
{
    while(counter == 0)
    {
        counter--;
    }
}
static void UART_vidClockEnable(uint8 Index){
	uint8 UartNum = gpas_UartConfig[Index].UartNum;

	//SET_BIT(HWREG(RCGC_Base+RCGCUART),UartNum);
//	(*((volatile unsigned long *)(RCGC_Base+RCGC1 ))) |= (1<<UartNum)  ;
	HWREG(RCGC_Base+RCGC1) |= (1<<UartNum) ;
	HWREG(RCGC_Base+RCGCUART) |= (1<<UartNum);

	delay(2000);
}



/****************************************************************************************/
/*    Function Description    : Disable the UART clock 									*/
/*    Parameter in            : uint8 index (index of the uart module 0 to 7)           */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : None                        			                */
/*    Return value            : None                         						    */
/****************************************************************************************/
static void UART_vidClockDisable(uint8 Index){
	uint8 UartNum = gpas_UartConfig[Index].UartNum;
	
	CLR_BIT(HWREG(RCGC_Base+RCGC1),UartNum);
}


/****************************************************************************************/
/*    Function Description    : SET THE UART WORD LENGTH								*/
/*    Parameter in            : uint8 index (index of the uart module 0 to 7)           */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : None                        			                */
/*    Return value            : None                         						    */
/****************************************************************************************/
static void UART_vidSetWlen(uint8 Index)
{
    uint32  _ui32uartBaseAddress  = uint32_BaseAddress[gpas_UartConfig[Index].UartNum] ;
	Enum_WLEN_t  _WLEN     = gpas_UartConfig[Index].WLEN;

	/*Clear WLEN BITS(bit5,6) in UARTLCRH*/
	HWREG(_ui32uartBaseAddress+UARTLCRH) &= ~WLEN_BITS; 

	//SET THE WLENT USING UARTLCRH REG//
	HWREG(_ui32uartBaseAddress+UARTLCRH) |= (_WLEN);
}


/****************************************************************************************/
/*    Function Description    : This function Enable the SIR 					        */
/*    Parameter in            : uint32 ui32Base (uart address receiving the data from)  */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : none                                                    */
/*    Return value            : none                                                    */
/****************************************************************************************/
void UARTEnableTxISR(uint8 Index)
{
    // Enable SIR and SIRLP (if appropriate).//
    uint32  _ui32uartBaseAddress  = uint32_BaseAddress[gpas_UartConfig[Index].UartNum] ;
    /***********************************************************/
   // HWREG(_ui32uartBaseAddress + UART_O_CTL) |= (UART_CTL_SIREN);
    HWREG(_ui32uartBaseAddress + UARTIM)     |=  UART_IM_TXIM;
}

/****************************************************************************************/
/*    Function Description    : This function Enable the Rx SIR      			        */
/*    Parameter in            : uint32 ui32Base (uart address receiving the data from)  */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : none                                                    */
/*    Return value            : none                                                    */
/****************************************************************************************/
void UARTEnableRxSIR(uint8 Index)
{
    // Enable SIR and SIRLP (if appropriate).//
    uint32  _ui32uartBaseAddress  = uint32_BaseAddress[gpas_UartConfig[Index].UartNum] ;
    /***********************************************************/
   // HWREG(_ui32uartBaseAddress + UART_O_CTL) |= (UART_CTL_SIREN);
    HWREG(_ui32uartBaseAddress + UARTIM)     |=  UART_IM_RXIM;
}
/****************************************************************************************/
/*    Function Description    : This function Disable Tx SIR 					        */
/*    Parameter in            : uint32 ui32Base (uart address receiving the data from)  */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : none                                                    */
/*    Return value            : none                                                    */
/****************************************************************************************/
void UARTDisbleTxISR(uint8 Index)
{
	
    // Enable SIR and SIRLP (if appropriate).//
    uint32  _ui32uartBaseAddress  = uint32_BaseAddress[gpas_UartConfig[Index].UartNum] ;
    //HWREG(_ui32uartBaseAddress + UART_O_CTL) &= ~(UART_CTL_SIREN);
    HWREG(_ui32uartBaseAddress + UARTIM)     &=  ~(UART_IM_TXIM);
}

/****************************************************************************************/
/*    Function Description    : This function Disable Rx  SIR 					        */
/*    Parameter in            : uint32 ui32Base (uart address receiving the data from)  */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : none                                                    */
/*    Return value            : none                                                    */
/****************************************************************************************/
void UARTDisbleRxSIR(uint8 Index)
{
    // Enable SIR and SIRLP (if appropriate).//
    uint32  _ui32uartBaseAddress  = uint32_BaseAddress[gpas_UartConfig[Index].UartNum] ;
   // HWREG(_ui32uartBaseAddress + UART_O_CTL) &= ~(UART_CTL_SIREN);
    HWREG(_ui32uartBaseAddress + UARTIM)     &=  ~(UART_IM_RXIM);
}


/****************************************************************************************/
/*    Function Description    : This function Disable the SIR 					        */
/*    Parameter in            : uint32 ui32Base (uart address receiving the data from)  */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : none                                                    */
/*    Return value            : none                                                    */
/****************************************************************************************/
void UARTTxIntModeSet(uint8 Index, uint32 ui32Mode)
{
    uint32  _ui32uartBaseAddress  = uint32_BaseAddress[gpas_UartConfig[Index].UartNum] ;
    // Set or clear the EOT bit of the UART control register as appropriate. //
    HWREG(_ui32uartBaseAddress + UART_O_CTL) = ((HWREG(_ui32uartBaseAddress + UART_O_CTL) &
                                     ~(UART_TXINT_MODE_EOT |
                                       UART_TXINT_MODE_FIFO)) | ui32Mode);
}


/****************************************************************************************/
/*    Function Description    : Make the clock config as clock source based on the      */
/*							   sys clock and divisor									*/
/*								using GPIOPCTL register  							    */
/*    Parameter in            : uint8 index (index of the uart module 0 to 7)           */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : None                        			                */
/*    Return value            : None                         						    */
/****************************************************************************************/
static void UART_vidClockConfig(uint8 Index)
{
    uint32  _ui32uartBaseAddress  = uint32_BaseAddress[gpas_UartConfig[Index].UartNum] ;
	UART_Clock_CONFIG _UART_Clock_CONFIG = gpas_UartConfig[Index].clk_config;

    if( _UART_Clock_CONFIG == System_clock)
    {
    	// clr the first 4bits to 0x0//
    	HWREG(_ui32uartBaseAddress + UARTCC) &= ~(UART_CC_CS_M);
    }
    else if ( _UART_Clock_CONFIG == PIOSC)
    {
    	// clr the first 4bits to 0x0//
    	HWREG(_ui32uartBaseAddress + UARTCC) &= ~(UART_CC_CS_M);
    	// Set the first 4bits to 0x5//
    	HWREG(_ui32uartBaseAddress + UARTCC) |=  (UART_CC_CS_PIOSC);
    }
    else
    {

    }
}


/****************************************************************************************/
/*    Function Description    : This function check the confiugration parameters        */
/*    Parameter in            : uint8 index (index of the uart module 0 to 7)           */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : none                                                    */
/*    Return value            : uint8 returns ERROR or NO_ERROR                         */
/*****************************************************************************************/
static uint8 UART_ui8CheckConf(uint8 index)
{
    uint8 moduleStatus = NO_ERROR;

    if(gpas_UartConfig == NULL)
    {
        /*gpas_UartConfig can't be null, return error */
    }
    else{


    uint8  _UartNum                         = gpas_UartConfig[index].UartNum;
    uint32            _UARTSysClk           = gpas_UartConfig[index].UARTSysClk;
    uint8             _ClkDiv               = gpas_UartConfig[index].ClkDiv;
    uint32            _BaudRate             = gpas_UartConfig[index].BaudRate;
    Enum_WLEN_t       _WLEN                 = gpas_UartConfig[index].WLEN   ;
    UART_Clock_CONFIG _clk_config           = gpas_UartConfig[index].clk_config;
    TXCb_Fun                                = gpas_UartConfig[index].Tx_Cb;
    RXCb_Fun                                = gpas_UartConfig[index].Rx_Cb;



        /*Check if the Uart is Initialized*/
        if(UART_Initialized[index] == UART_INTIALIZED)
        {
            /*the module is INTIALIZED, report error*/
            moduleStatus = ERROR;
        }

        /*Check UartNum is valid*/
        else if(_UartNum >= UART_MAX_NUM)
        {
            /*the UART number is invalid, report error*/
            moduleStatus = ERROR;
        }

      /*Check uartPort is valid*/
//      else if(_uartPort > PORTF)
//      {
        /*the UART port is invalid, report error*/
//      moduleStatus = ERROR;
//      }

       /*Check UARTSysClk is valid*/
        else if (_UARTSysClk == NULL)
        {
            /*the UARTSysClk can't be NULL, report error */
            moduleStatus = ERROR;
        }

        /*Check ClkDiv is valid*/
        else if (_ClkDiv == NULL)
        {
            /*the ClkDiv can't be NULL, report error */
            moduleStatus = ERROR;
        }

        /*Check BaudRate is valid*/
        else if ( _BaudRate == NULL)
        {
        /*the BaudRate can't be NULL, report error */
        moduleStatus = ERROR;

        }
        /*Check WLEN is valid*/
        else if ( _WLEN  == LENGTH_NOT_DEFINED )
        {
            /*the Word LEN is invalid, report error */
            moduleStatus = ERROR;
        }
         /*Check clk_config is valid*/
         else if (_clk_config != System_clock  &&  _clk_config != PIOSC)
        {
            /*the Word LEN is invalid, report error */
            moduleStatus = ERROR;
        }

    /* Check ui32PortBaseAddress is valid*/
/*  else if (ui32PortBaseAddress != PORTA_APB_BASE || ui32PortBaseAddress != PORTA_AHB_BASE ||
             ui32PortBaseAddress != PORTB_APB_BASE || ui32PortBaseAddress != PORTB_AHB_BASE ||
             ui32PortBaseAddress != PORTC_APB_BASE || ui32PortBaseAddress != PORTC_AHB_BASE ||
             ui32PortBaseAddress != PORTD_APB_BASE || ui32PortBaseAddress != PORTD_AHB_BASE ||
             ui32PortBaseAddress != PORTE_APB_BASE || ui32PortBaseAddress != PORTE_AHB_BASE ||
             ui32PortBaseAddress != PORTF_APB_BASE || ui32PortBaseAddress != PORTF_AHB_BASE )
    {*/
        /*the ui32PortBaseAddress is invalid, report error */
/*      moduleStatus = ERROR;
    }*/
    else
    {

    }
    }

    return moduleStatus;
}
/****************************************************************************************/
/*    Function Description    : This function initializes the uart modules		        */
/*    Parameter in            : None												    */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : None				                                    */
/*    Return value            : None                         						    */
/****************************************************************************************/
void UART_vidInit(const str_UartConfig_t *_pas_UartConfig )
{

    InitGlobal_Variable();

    gpas_UartConfig  = _pas_UartConfig;
	uint8 UartCounter = 0 ;

	for(UartCounter = 0;UartCounter < UART_MAX_NUM; UartCounter++)
	{
		/*TODO CHECK THE MODULE INIT*/
		/*TODO CHECK THE GLOBL CONFIG*/
		/*TODO MODULE INIT VARIABLE NOT A*/

		/*check the configuration parameters*/
		
		/*8- To do 11:48*/
		if( UART_ui8CheckConf(UartCounter) == ERROR)
		{
			/*error in cofiguration parameters*/

		}else
		{
            //InitGlobal_Variable();
            // Enable the Clock for the UART      //
            UART_vidClockEnable(UartCounter);
            // ENable the Clock for the GPIO Port //
            UART_vidGpioClockEnable(UartCounter);
            // Enable The AFSEL , CONTROL And the Clock source REG //
            GPIO_vidEnableAfselAndControl(UartCounter);
            // Disable the UART                   //
            UART_vidDisable(UartCounter);
            // Set The BuadRate                   //
            UART_vidSetBuadRate(UartCounter);
            //CHOSE THE WORD LENGTH  USING UARTLCRH REGISTER//
            UART_vidSetWlen(UartCounter);
             //Configure the UART clock source USING UARTCC  //
            UART_vidClockConfig(UartCounter);
			//Enable the UART //
           // *(volatile uint32 *) (UART0 + UARTLCRH) = 0x70;
			UART_vidEnable(UartCounter);
#if (PROCESS_MODE == INTERRUPT )
            // Enable the SIR //
            UARTEnableRxSIR(UartCounter);
            UARTEnableTxISR(UartCounter);
            UARTTxIntModeSet(UartCounter,UART_TXINT_MODE_EOT);
#endif
			// set the UART INTIALIZED //
			INT_Enable(gpas_UartConfig[UartCounter].UartNum);
		    UART_Initialized[gpas_UartConfig[UartCounter].UartNum] = UART_INTIALIZED;

		}
		

	}
}


/****************************************************************************************/
/*    Function Description    : This function Transmits the data				        */
/*    Parameter in            : uint32 ui32Base (uart address receiving the data from)  */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : none                                                    */
/*    Return value            : None						                            */
/****************************************************************************************/

void UART_vidTransmit(uint8 channelNum , str_Transmit_Data_Info *DataInfo)
{
    uint32 bytesCounter ;

    uint8 *ptrToData       = DataInfo->ptr_DataToSend;
    uint32 dataLength      = DataInfo->Num_bytesTosend;
    uint32 uartBaseAddress = uint32_BaseAddress[gpas_UartConfig[channelNum].UartNum] ;
	/*to get*/

#ifdef	FIFO
	/*To do 10 done*/
	for(bytesCounter = DataInfo->currentByte ; bytesCounter < dataLength ; bytesCounter++)
	{
		/*if FIFO is not full*/
		
		/*21- To do 9:19*/
		if((HWREG(uartBaseAddress+UARTFR)&UART_FR_TXFF) == 0)
		{
			/*put byte into the FIFO*/
			HWREG(uartBaseAddress+ UARTDR) = *(ptrToData+bytesCounter);
			//HWREG(uartBaseAddress+ UARTDR) = 'm';
		}
		/*if FIFO is Full*/
		else
		{
		    //HWREG(_ui32uartBaseAddress + UART_O_CTL) |= ( UART_CTL_TXE);
			/*save how many bytes have been sent*/
			DataInfo->currentByte = bytesCounter;
			break;
		}
	}
	if(bytesCounter == dataLength){
	
		/*the request is done and all the data have been transmited*/
		/*Call back function to delete the request*/
	    DataInfo->currentByte = bytesCounter;

	}
#elif DMA
	 DMA( &ptrToData[0] , &ptrToData[dataLength-1] , ptrToData[0] , dataLength) ;

#endif

}

/****************************************************************************************/
/*    Function Description    : This function receives the data					        */
/*    Parameter in            : uint32 ui32Base (uart address receiving the data from)  */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : none                                                    */
/*    Return value            : uint8 returns ERROR or NO_ERROR                         */
/****************************************************************************************/
void UART_sint32Receive(void)
{
    uint32 _Num_bytesToReceive = gArrRxRequest->Num_bytesToReceive;
    uint8  channelNum          = gArrRxRequest->channelNum;
    uint8 i ;
    static uint8 intFlag = 0 ;
switch(ReceiveStateMachine)
{
	case IDLE:
			if(InterruptReceivedFlagCounter[channelNum] > 0 )
			{
				InterruptReceivedFlagCounter[channelNum]--;
				ReceiveStateMachine = INTERRUPT_LEVEL_REACHED;
			}
	break;

	case INTERRUPT_LEVEL_REACHED:	

           /*make it Ideal till the rest of bytes received*/
           if(( _Num_bytesToReceive - CounterBytesReceived[channelNum]) >= Uart_Level[channelNum].Rx_Level)
           {
               ReceiveStateMachine = IDLE;
           }
           	/*Recieved all*/
           	else if( _Num_bytesToReceive == CounterBytesReceived[channelNum] )
	        {
           	 ReceiveStateMachine = IDLE;
                /*Reset the Receive counter */
                CounterBytesReceived[channelNum] = 0;
               // HWREG(uint32_BaseAddress[UART0] + UARTICR) |= (UART_ICR_RXIC) ;
                /*Call back to the comm module*/
                (*RXCb_Fun)();
      		}
           	else/*if num of bytes reminded are less than the interrupt level*/
           	{
           	 ReceiveStateMachine = NUM_OF_REMINDED_BYTES_LESS_THAN_INTERRUPT_LEVEL;
           	}
	break;

	case NUM_OF_REMINDED_BYTES_LESS_THAN_INTERRUPT_LEVEL:
		if(  ((HWREG(uint32_BaseAddress[channelNum] + UARTFR))&(1<<RXFE)) == 0)
		{
             uint8 x ;
            x = HWREG(uint32_BaseAddress[channelNum] + UARTDR) ;
            gArrRxRequest->ptr_Buffer[CounterBytesReceived[channelNum]] = x ;
            /*check if all the data has been received*/
            CounterBytesReceived[channelNum]++;
		}
		if( _Num_bytesToReceive == CounterBytesReceived[channelNum] )
	        {
		        ReceiveStateMachine = IDLE;
                /*Reset the Receive counter */
                CounterBytesReceived[channelNum] = 0;
               // HWREG(uint32_BaseAddress[UART0] + UARTICR) |= (UART_ICR_RXIC) ;
                /*Call back to the comm module*/
                (*RXCb_Fun)();
      	}

		break;
	default:
		break;
  }

}

void DMA(uint32 *firstAdd , uint32 *LastAdd , uint8 FistData , uint32 BytesNum)
{


}
