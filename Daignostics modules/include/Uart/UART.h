#include"Platform_Types.h"

/*****************************************************/
/*                                                   */
/* CLOCK CONFIG                                      */
/*                                                   */
/*****************************************************/

typedef uint8 UART_Clock_CONFIG;
#define System_clock  ((0x0))
#define PIOSC         ((0x5))

#define UART_MAX_NUM 1
/*****************************************************/
/* 												     */
/* UART Base Addresses 								 */
/* 												     */
/*****************************************************/

/*enum not config*/
/*5- To do 10:35 ( line 10 to 20 should be moved to uart.c)*/
typedef uint8 Enum_WLEN_t;
#define LENGTH_5BIT (Enum_WLEN_t)(0x0<<5)
#define LENGTH_6BIT (Enum_WLEN_t)(0x1<<5)
#define LENGTH_7BIT (Enum_WLEN_t)(0x2<<5)
#define LENGTH_8BIT (Enum_WLEN_t)(0x3<<5)
#define LENGTH_NOT_DEFINED ((0x4))



#define UART0 (0u)
#define UART1 (1u)
#define UART2 2
#define UART3 3
#define UART4 4
#define UART5 5
#define UART6 6
#define UART7 7

#define GPIOPCTL_OFFSET 0x52C
#define ZERO_MASK_PIN0_PIN1 0Xffffff00
#define ZERO_MASK_PIN4_PIN5 0Xff00ffff
#define ZERO_MASK_PIN6_PIN7 0X00ffffff

#define GPIOPCTL_ENABLE_UART 0x00000011
#define GPIOPCTL_ENABLE_UART1 0x00000002


#define UART_FR_Offset 0x018



#define ERROR 1
#define NO_ERROR 0
#define NULL 0

/*2- To Do 10:27*/
typedef void(*pf_UartTx_Cbk)(void) ;
typedef void(*pf_UartRx_Cbk)(void) ;


typedef struct
{
   uint8   UartNum ;

   uint32  UARTSysClk;

   uint8   ClkDiv;

   uint32  BaudRate;

   Enum_WLEN_t WLEN ;

   UART_Clock_CONFIG clk_config;

   pf_UartRx_Cbk Rx_Cb;
   pf_UartTx_Cbk Tx_Cb;

}str_UartConfig_t;

typedef struct
{
	/*pointer to the data to be sent*/
    uint8 *ptr_DataToSend  ;

	/*length of the data to be sent*/
    uint32 Num_bytesTosend ;

	/*variable to detecte how many bytes of the data length have been sent*/
	uint32 currentByte;

}str_Transmit_Data_Info ;

typedef struct
{
    /*pointer to the buffer to put the data to be recieved in*/
    uint8 *ptr_Buffer  ;

    /*length of the data to be recieved*/
    uint32 Num_bytesToReceive ;

    uint8 channelNum ;
}str_Receive_Data_Info ;




/*6- To do 11:26*/
void UART_vidInit(const str_UartConfig_t *_pas_UartConfig);
void UART_vidTransmit(uint8 channelNum , str_Transmit_Data_Info *DataInfo);
void UART_sint32Receive(void);
void SetFifoRXInterrupt_TriggerLevel(uint8 channel , uint32 NUM_Ofbytes);
void SetFifoTXInterrupt_TriggerLevel(uint8 channel , uint32 NUM_Ofbytes);

/*Interrupt handlers*/
void UART0_Handler (void);
void UART1_Handler (void);
void UART2_Handler (void);
void UART3_Handler (void);
void UART4_Handler (void);
void UART5_Handler (void);
void UART6_Handler (void);
void UART7_Handler (void);
