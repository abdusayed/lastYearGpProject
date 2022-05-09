#include"Platform_Types.h"

#ifndef uart_h
#define uart_h
#include "UART.h"
#endif

#define EMPTY  0
#define ENABLE  1
#define DISABLE 0


#define SENT_COMPLETE  2
#define COMM_IDLE  3
#define SENDING 4
#define REQUEST_RECEIVED  5
#define RX_MAXDATA__SIZE 5
#define MAX_REQUESTS 5

typedef void(*App_UartTx_Cbk)(void) ;
typedef void(*App_UartRx_Cbk)(void) ;

typedef struct{
    App_UartTx_Cbk Tx_Cb ;
    App_UartRx_Cbk Rx_Cb ;

}str_CbConfig ;

void   Uart_COMM_RxInit(str_CbConfig * ptr_Cfg_Str);
void   Uart_COMM_TXInit(str_CbConfig * strp_Data_Config);
void   UART_COMM_Init(const str_UartConfig_t *_pas_UartConfig);
void   UART_COMM_TxRequest(str_Transmit_Data_Info *strp_Data_Config);
void   UART_COMM_RxRequest(str_Receive_Data_Info *strp_Data_Config);
void   UART_COMM_SetFifoRXInterrupt(uint8 channel , uint32 NUM_Ofbytes);
void   UART_COMM_SetFifoTXInterrupt(uint8 channel , uint32 NUM_Ofbytes);
void   UART_COMM_TxMainFunction();
void   UART_COMM_RxMainFunction();
void   TX_Cb(void);
void   RX_Cb(void);
