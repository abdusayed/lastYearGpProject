/*****************************************************************************/
/*                          extern Variables                                 */
/*****************************************************************************/
#include"UART_PBCfg.h"
#include"UART_COMM.h"
#include"Platform_Types.h"


/*****************************************************************************/
/*                          Internal parameter for RX                        */
/*****************************************************************************/
static _Bool		  RX_FlageDataReciving;// flage to indicate the RX //
/*****************************************************************************/
/*                          Internal parameter for TX                        */
/*****************************************************************************/
static uint8  CurrentRequest  ;
uint16 BytesCounter ;
uint16 Number_Of_Bytes ;
uint8 *ptr_Data2Sent   ;
uint8 Transfer_Done = DISABLE ;
uint8 REQ_RECEIVED = DISABLE ;
// Array of pointer to the Data request //
str_Transmit_Data_Info *gArrTxRequest[MAX_REQUESTS];
str_Receive_Data_Info  *gArrRxRequest[MAX_REQUESTS];


uint32 POP_TxRequest  ;
uint32 PUSH_TxRequest ;

uint32 POP_RxRequest  ;
uint32 PUSH_RxRequest ;

App_UartTx_Cbk User_Tx_CBK;
App_UartRx_Cbk User_Rx_CBK;
/*****************************************************************************/
/*                          CallBackTxFunction                               */
/*****************************************************************************/
void TX_Cb(void)
{
		// The Currrent Data has been sent //
	/*
    if(gArrTxRequest[POP_TxRequest]->currentByte == gArrTxRequest[POP_TxRequest]->Num_bytesTosend )
	*/
    Transfer_Done = ENABLE;
    (*User_Tx_CBK)();

}

/*****************************************************************************/
/*                          CallBackTxFunction                               */
/*****************************************************************************/
void RX_Cb()
{

	//set flage to make dispatcher look at the new data//
	RX_FlageDataReciving  = ENABLE;
	//store in buffer and increament the index//


}

/*****************************************************************************/
/*                          CallBackTxFunction                               */
/*****************************************************************************/
static void comm_TxRest(void)
{
	BytesCounter	 = EMPTY;
	CurrentRequest   = COMM_IDLE;
	POP_TxRequest    = EMPTY ;
    PUSH_TxRequest   = EMPTY ;
    uint16 i = EMPTY ;
	for( i = EMPTY  ; i < MAX_REQUESTS ; i++)
	{
		gArrTxRequest[i] = EMPTY;
	}
}

void UART_COMM_Init(const str_UartConfig_t *_pas_UartConfig)
{
    UART_vidInit(_pas_UartConfig);
}

/*****************************************************************************/
/*                          CallBackTxFunction                               */
/*****************************************************************************/
static void Comm_RxRest(void)
{
    // Init the Buffer index    //
	// Reset the Receiving flag //
	RX_FlageDataReciving = EMPTY;
}

/*****************************************************************************/
/*                          Init Comm Module                                 */
/*****************************************************************************/
void Uart_COMM_TXInit(str_CbConfig * strp_Data_Config)
{
	comm_TxRest();
	// INIT THE TX parameter//	
	User_Tx_CBK = strp_Data_Config->Tx_Cb;
}
/*****************************************************************************/
/*                          Init RX MODULE                                   */
/*****************************************************************************/
void Uart_COMM_RxInit(str_CbConfig * ptr_Cfg_Str)
{
    // INIT THE RX PARAMETER //
    Comm_RxRest();
	User_Rx_CBK = ptr_Cfg_Str->Rx_Cb;


}
/*****************************************************************************/
/*                          Request Function                                 */
/*****************************************************************************/
void   UART_COMM_TxRequest(str_Transmit_Data_Info *strp_Data_Config)
{
	/* CHECK FOR THE EMPTY INDEX*/
	if(gArrTxRequest[PUSH_TxRequest] == EMPTY)
	{
		/* CHANGE THE STATE OF THE CURRENT TRANSMITE BYTE */
	    gArrTxRequest[PUSH_TxRequest]= strp_Data_Config;
	    
	    /*put number of bytes sent equal to zero */
	    gArrTxRequest[PUSH_TxRequest]->currentByte = 0;
	    
        /* MOVE THE PUSH POINTER TO THE NEXT INDEX */
        PUSH_TxRequest++;
	}
	else if(PUSH_TxRequest == MAX_REQUESTS)
	{
	    /*move the push pointer to the first element in the array*/
		PUSH_TxRequest = EMPTY ;
	}
	else
	{
		// REPORT Error The buffer is Full
	}
}
/*****************************************************************************/
/*                          Request Function                                 */
/*****************************************************************************/
void UART_COMM_SetFifoRXInterrupt(uint8 channel , uint32 NUM_Ofbytes)
{
    SetFifoRXInterrupt_TriggerLevel(channel , NUM_Ofbytes);

}
/*****************************************************************************/
/*                          Request Function                                 */
/*****************************************************************************/
void UART_COMM_SetFifoTXInterrupt(uint8 channel , uint32 NUM_Ofbytes)
{
    SetFifoTXInterrupt_TriggerLevel(channel , NUM_Ofbytes);

}
/*****************************************************************************/
/*                          Request Function                                 */
/*****************************************************************************/
void   UART_COMM_RxRequest(str_Receive_Data_Info *strp_Data_Config)
{
    /* CHECK FOR THE EMPTY INDEX*/
    if(gArrRxRequest[PUSH_RxRequest] == EMPTY)
    {
        /* CHANGE THE STATE OF THE CURRENT TRANSMITE BYTE */
        gArrRxRequest[PUSH_RxRequest]= strp_Data_Config;
        /* MOVE THE PUSH POINTER TO THE NEXT INDEX */
        PUSH_RxRequest++;
    }
    else if(PUSH_RxRequest == MAX_REQUESTS)
    {
        /*move the push pointer to the first element in the array*/
        PUSH_RxRequest = EMPTY ;
    }
    else
    {
        // REPORT Error The buffer is Full
    }
}

/*****************************************************************************/
/*                          TxMainFunction                                   */
/*      COMMIDEAL        -(Request)---->    REQUEST_RECEIVED                 */
/*      REQUEST_RECEIVED -(Start send)->    SENDING                          */
/*      SENDING          -(TX_CB)------>    SENTCOMPLETE                     */
/*      SENTCOMPLETE     -(Request)---->    SENDING                          */
/*****************************************************************************/
void   UART_COMM_TxMainFunction(void)
{
    uint32 _Num_bytesTosend = gArrTxRequest[POP_TxRequest]->Num_bytesTosend;
    uint32 _currentByte     = gArrTxRequest[POP_TxRequest]->currentByte;
	/*12- to do 12:14*/
	// STATE MACHINE //
	switch(CurrentRequest)
	{

	case(COMM_IDLE):
        if((gArrTxRequest[POP_TxRequest] != EMPTY))
         {
           CurrentRequest = REQUEST_RECEIVED ;
         }
        else
        {
           /*Do Nothing*/
        }
	break;
	case(SENDING):
	        /*check if there is bytes not sent yet in the current request*/
         if(_Num_bytesTosend > _currentByte )
         {
             UART_vidTransmit( 0 , gArrTxRequest[POP_TxRequest]);
         }else if(Transfer_Done == ENABLE)
         {
             CurrentRequest = SENT_COMPLETE;
         }else
         {
             /*Do Nothing*/
         }
        
	break;
	case(REQUEST_RECEIVED):
        /* SEND THE CURRENT BYTE TO THE UART */
         UART_vidTransmit( 0 , gArrTxRequest[POP_TxRequest]);
        // CHANG THE STATE OF THE CURRENT BYTE BEING TRANSMITTED//
        CurrentRequest = SENDING ;
	
     break;
	case(SENT_COMPLETE):
		
         gArrTxRequest[POP_TxRequest++] = EMPTY ;  
        // Check if the pop pointer reached to the max index//
        if(POP_TxRequest == MAX_REQUESTS)
        {
            // Reset the pop pointer (make it points to the first element in the array) //
            POP_TxRequest = EMPTY ;
        }else
        {
            /*Do Nothing*/
        }
        
        if((gArrTxRequest[POP_TxRequest] != EMPTY))
        {
           CurrentRequest = REQUEST_RECEIVED ;
        }else
        {
            /*Do Nothing*/
        }
        
        // Clear the transmite request //
        //User CallBack Fun//
		// Check if the whole Data has been transmitted//
	break;

	default:

	break;
	}
}
/*****************************************************************************/
/*                          RxMainFunction                                   */
/*****************************************************************************/
void   UART_COMM_RxMainFunction(void)
{	// check the flage //
    UART_sint32Receive();
	if (RX_FlageDataReciving )
	{
		//TODO DEFINE COMM PACKED
		// clear the flage to stop checking till next byte //
		RX_FlageDataReciving= DISABLE;
		(*User_Rx_CBK)() ;
		 // call application funcation to indicate the receiving finished
		//User_Rx_CBK(&Rx_Buffer,RX_Buffer_Index );
	}
}
