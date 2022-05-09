
#include "UART_COMM.h"
#include "GPio_Driver.h"
#include "UART_PBCfg.h"


str_CbConfig Tx_Rx_Cb ;
uint8 data[] = "mohamed";
uint8 ReceiveBuffer[10];

str_Transmit_Data_Info tx_data ;
str_Receive_Data_Info  Rx_data ;

str_PortConfig_t portcfg ;
uint8 x = 0 ;
void tx_cb()
{
    x++;
    UART_COMM_TxRequest(&tx_data);
}
void Rx_cb()
{
   x++;
   UART_COMM_RxRequest(&Rx_data);
}
void main()
{
  // (*((volatile unsigned long *)0x400FE104)) |= 0x1 ;
    portcfg.Port = PORTB ;
    UART_COMM_Init( &UartConfig);

    Tx_Rx_Cb.Tx_Cb = tx_cb ;
    Tx_Rx_Cb.Rx_Cb = Rx_cb ;

    tx_data.ptr_DataToSend = data;
    tx_data.currentByte = 0 ;
    tx_data.Num_bytesTosend =  7 ;

    Rx_data.ptr_Buffer = ReceiveBuffer;
    Rx_data.Num_bytesToReceive = 10;
    Rx_data.channelNum = 0 ;

    Uart_COMM_TXInit(&Tx_Rx_Cb);
    Uart_COMM_RxInit(&Tx_Rx_Cb);
    UART_COMM_TxRequest(&tx_data);
    UART_COMM_RxRequest(&Rx_data);
    UART_COMM_SetFifoRXInterrupt(1, 10);
    while(1)
    {
        UART_COMM_TxMainFunction();
        UART_COMM_RxMainFunction();
    };
}



