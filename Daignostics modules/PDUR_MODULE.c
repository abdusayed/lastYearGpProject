/******************************************************************************
 * Module      : PduR Demo                                                    *
 * File Name   : PDUR_MODULE.c                                                *
 * Description : Source file of PduR Demo                                     *
 * Created on  : April 6, 2020                                                *
 ******************************************************************************/


#include "PDUR_MODULE.h"
#include "Dcm_Cbk.h"
#include "uart_stdio.h"

BufReq_ReturnType CopyRxResult;
BufReq_ReturnType StartOfRecResult;
BufReq_ReturnType result;
PduIdType  TxId;
uint8 TXBufferByte_1,TXBufferByte_2,TXBufferByte_3,TXBufferByte_4,TXBufferByte_5;
boolean PduR_DcmResponseFlag = FALSE;

uint8 Txarr[30];
PduInfoType TXInfo =
{
 g_UART0_BufferTX,
 NULL,
 5
};

uint32 Total_Len = 2;
const uint32 PDU_Len   = 2;



uint8 arrPT[] =  {0x3E, 0x80};

const PduInfoType infoPT =
{
 arrPT,
 NULL,
 2
};
const PduInfoType *info1PT = &TXInfo;



boolean key = TRUE;



/*******************************************************
 *    Test Cases for Dsl Sub-Module interfaces         *
 *******************************************************/

 /*
  * Start Of Reception test cases :
  *
  * There are eight test cases for this service
  *
  * 1- Request with non configured ID
  * 2- Request with total size equal to zero
  * 3- Request with total size larger than DCM buffer
  * 4- Physical Request that came across locked buffer
  * 5- Physical Tester present request came across locked buffer
  * 6- Functional Tester Present request belonging to another connection
  *
  * 7- All verifications are passed for global buffer
  * 8- All verifications are passed for local buffer
  *
  */




#if REQUEST_WITH_NON_CONFIGURED_ID

uint8 Buf[] = {0x22,0x01,0x10,0xF1,0x90};

const PduInfoType BInfo =
{
 Buf,
 NULL,
 5
};
const PduInfoType *Binfo_Ptr = &BInfo;

void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;

    Dcm_CopyTransmitData(TxId,&infoPT,NULL,NULL);

    TXBufferByte_1 = infoPT.SduDataPtr[0];
  }
  if(key == TRUE)
  {
      key = FALSE;

        /*
         * Expected value of StartOfRecResult is BUFREQ_E_NOT_OK
         */
      StartOfRecResult = Dcm_StartOfReception(20,Binfo_Ptr,2,NULL);

      if(StartOfRecResult == BUFREQ_OK)
      {
          CopyRxResult = CopyRequestData(20,Binfo_Ptr,NULL);
          if(CopyRxResult == BUFREQ_OK)
          {
              Dcm_TpRxIndication(20,CopyRxResult);
          }
      }
  }
}

#elif REQUEST_WITH_TOTAL_SIZE_EQUAL_TO_ZERO

void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;

    Dcm_CopyTransmitData(TxId,&infoPT,NULL,NULL);

    z = infoPT.SduDataPtr[0];
  }
  if(key == TRUE)
  {
      key = FALSE;

        /*
         * Expected value of StartOfRecResult is BUFREQ_OK
         */
      StartOfRecResult = Dcm_StartOfReception(1,info_Ptr,0,NULL);

      if(StartOfRecResult == BUFREQ_OK)
      {
          CopyRxResult = CopyRequestData(1,info_Ptr,NULL);
          if(CopyRxResult == BUFREQ_OK)
          {
              Dcm_TpRxIndication(1,CopyRxResult);
          }
      }
  }
}

#elif REQUEST_WITH_TOTAL_SIZE_LARGER_THAN_DCM_BUFFER

void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;

    Dcm_CopyTransmitData(TxId,&infoPT,NULL,NULL);

    z = infoPT.SduDataPtr[0];
  }
  if(key == TRUE)
  {
      key = FALSE;

        /*
         * Expected value of StartOfRecResult is BUFREQ_E_OVFL
         */
      StartOfRecResult = Dcm_StartOfReception(1,info_Ptr,100,NULL);

      if(StartOfRecResult == BUFREQ_OK)
      {
          CopyRxResult = CopyRequestData(1,info_Ptr,NULL);
          if(CopyRxResult == BUFREQ_OK)
          {
              Dcm_TpRxIndication(1,CopyRxResult);
          }
      }
  }
}
#elif REQUEST_CAME_ACROSS_LOCKED_BUFFER

uint8 Buf_ReadDID[] = {0x22,0x01,0x10,0xF1,0x90};

const PduInfoType RDidInfo =
{
 Buf_ReadDID,
 NULL,
 5
};
const PduInfoType *RDidinfo_Ptr = &RDidInfo;


void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;

    Dcm_CopyTransmitData(TxId,&infoPT,NULL,NULL);

    z = infoPT.SduDataPtr[0];
  }
  if(key == TRUE)
  {
      key = FALSE;

     StartOfRecResult = Dcm_StartOfReception(1,RDidinfo_Ptr,5,NULL);

      if(StartOfRecResult == BUFREQ_OK)
      {
          CopyRxResult = CopyRequestData(1,RDidinfo_Ptr,NULL);
          if(CopyRxResult == BUFREQ_OK)
          {
              Dcm_TpRxIndication(1,CopyRxResult);
          }
      }
  }
  else if(key == FALSE)
  {
      /*
       * Expected value of StartOfRecResult is BUFREQ_E_NOT_OK
       */
         StartOfRecResult = Dcm_StartOfReception(1,RDidinfo_Ptr,5,NULL);

         if(StartOfRecResult == BUFREQ_OK)
         {
           CopyRxResult = CopyRequestData(1,RDidinfo_Ptr,NULL);
           if(CopyRxResult == BUFREQ_OK)
           {
                Dcm_TpRxIndication(1,CopyRxResult);
           }
          }
    }
}

#elif PHYSICAL_TESTER_PRESENT_REQUEST_CAME_ACROSS_LOCKED_BUFFER

uint8 Buf_ReadDID[] = {0x22,0x01,0x10,0xF1,0x90};

/*Tester Present buf */
uint8 Buf_0x3E[] = {0x3E,0x80};

const PduInfoType TesInfo =
{
 Buf_0x3E,
 NULL,
 2
};

const PduInfoType RDidInfo =
{
 Buf_ReadDID,
 NULL,
 5
};
const PduInfoType *RDidinfo_Ptr = &RDidInfo;
const PduInfoType *Tesinfo_Ptr = &TesInfo;

void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;

    result = Dcm_CopyTransmitData(TxId,&TXInfo,NULL,NULL);
    Dcm_TpTxConfirmation(TxId,result);

    TXBufferByte_1 = TXInfo.SduDataPtr[0];
    TXBufferByte_2 = TXInfo.SduDataPtr[1];
    TXBufferByte_3 = TXInfo.SduDataPtr[2];
    TXBufferByte_4 = TXInfo.SduDataPtr[3];
  }
  if(key == TRUE)
  {
      key = FALSE;

     StartOfRecResult = Dcm_StartOfReception(2,RDidinfo_Ptr,5,NULL);

      if(StartOfRecResult == BUFREQ_OK)
      {
          CopyRxResult = CopyRequestData(2,RDidinfo_Ptr,NULL);
          if(CopyRxResult == BUFREQ_OK)
          {
              Dcm_TpRxIndication(2,CopyRxResult);
          }
      }
  }
  else if(key == FALSE)
  {
      /*
       * Expected value of StartOfRecResult is BUFREQ_E_NOT_OK
       */
         StartOfRecResult = Dcm_StartOfReception(2,Tesinfo_Ptr,2,NULL);

         if(StartOfRecResult == BUFREQ_OK)
         {
           CopyRxResult = CopyRequestData(2,Tesinfo_Ptr,NULL);
           if(CopyRxResult == BUFREQ_OK)
           {
                Dcm_TpRxIndication(2,CopyRxResult);
           }
          }
    }
}
#elif ALL_VERIFICATIONS_PASSED_GLOBAL_BUFFER

uint8 Req_Data[] = {0x3E, 0x80};
const PduInfoType PduInfo =
{
 Req_Data,
 NULL,
2
};
const PduInfoType *info_Ptr = &PduInfo;

void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;

    Dcm_CopyTransmitData(TxId,&infoPT,NULL,NULL);

    TXBufferByte_1 = infoPT.SduDataPtr[0];
  }
  if(key == TRUE)
  {
      key = FALSE;

        /*
         * Expected value of StartOfRecResult is BUFREQ_E_OK
         */
      StartOfRecResult = Dcm_StartOfReception(2,info_Ptr,2,NULL);

      if(StartOfRecResult == BUFREQ_OK)
      {
          CopyRxResult = CopyRequestData(2,info_Ptr,NULL);
          if(CopyRxResult == BUFREQ_OK)
          {
              Dcm_TpRxIndication(2,CopyRxResult);
          }
      }
  }
}
#elif ALL_VERIFICATIONS_PASSED_LOCAL_BUFFER

uint8 Buf_ReadDID[] = {0x22,0x01,0x10,0xF1,0x90};

/*Tester Present buf */
uint8 Buf_0x3E[] = {0x3E,0x80};

const PduInfoType TesInfo =
{
 Buf_0x3E,
 NULL,
 2
};

const PduInfoType RDidInfo =
{
 Buf_ReadDID,
 NULL,
 5
};
const PduInfoType *RDidinfo_Ptr = &RDidInfo;
const PduInfoType *Tesinfo_Ptr = &TesInfo;

void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;

    Dcm_CopyTransmitData(TxId,&infoPT,NULL,NULL);

    z = infoPT.SduDataPtr[0];
  }
  if(key == TRUE)
  {
      key = FALSE;

     StartOfRecResult = Dcm_StartOfReception(2,RDidinfo_Ptr,5,NULL);

      if(StartOfRecResult == BUFREQ_OK)
      {
          CopyRxResult = CopyRequestData(2,RDidinfo_Ptr,NULL);
          if(CopyRxResult == BUFREQ_OK)
          {
              Dcm_TpRxIndication(2,CopyRxResult);
          }
      }
  }
  else if(key == FALSE)
  {
      /*
       * Expected value of StartOfRecResult is BUFREQ_E_OK
       */
         StartOfRecResult = Dcm_StartOfReception(1,Tesinfo_Ptr,2,NULL);

         if(StartOfRecResult == BUFREQ_OK)
         {
           CopyRxResult = CopyRequestData(1,Tesinfo_Ptr,NULL);
           if(CopyRxResult == BUFREQ_OK)
           {
                Dcm_TpRxIndication(2,CopyRxResult);
           }
         }
    }
}


#elif DCM_DSL_DIAG_RESP_MAX_NUM_RESP_PEND_EXCEEDED

uint8 Buf_ReadDID[] = {0x22,0x01,0x0A};

const PduInfoType RDidInfo =
{
 Buf_ReadDID,
 NULL,
 3
};
const PduInfoType *RDidinfo_Ptr = &RDidInfo;

void Pdur_main(void)
{
    uint8 a,b,c,d,e,f,g,h,i,j,k,m,n,l;
    uint32 len;
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;
    Dcm_CopyTransmitData(TxId,&TXInfo,NULL,NULL);
    len = TXInfo.SduLength;
    a = TXInfo.SduDataPtr[0];  //0x62
    b = TXInfo.SduDataPtr[1];  //0x01
    c = TXInfo.SduDataPtr[2];  //0x10
    d = TXInfo.SduDataPtr[3];  //0x8C
    e = TXInfo.SduDataPtr[4];  //0xF1
    f = TXInfo.SduDataPtr[5];  //0x90
    g = TXInfo.SduDataPtr[6];  //0x57
    h = TXInfo.SduDataPtr[7];  //0x30
    i = TXInfo.SduDataPtr[8];  //0x4C
    j = TXInfo.SduDataPtr[9];  //0x30
    k = TXInfo.SduDataPtr[21]; //0x32
    m = TXInfo.SduDataPtr[22]; //0x36
    n = TXInfo.SduDataPtr[23];
  }
  if(key == TRUE)
    {
        key = FALSE;
        StartOfRecResult = AcceptNewConnection(2,RDidinfo_Ptr,3,NULL);
        if(StartOfRecResult == BUFREQ_OK)
        {
            CopyRxResult = CopyRequestData(2,RDidinfo_Ptr,NULL);
            if(CopyRxResult == BUFREQ_OK)
            {
                Dcm_PduRToDslIndication(2,CopyRxResult);
            }
        }
    }
  }





/*
 * CopyRx Test Cases:
 */

#elif GLOBAL_LOCKED_BUFFER_PROVIDED_PDUR_BUT_EMPTY
uint8 Req_Data[] = {0x3E, 0x80};
const PduInfoType PduInfo =
{
 Req_Data,
 NULL,
0
};
const PduInfoType *info_Ptr = &PduInfo;

void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;

    Dcm_CopyTransmitData(TxId,&infoPT,NULL,NULL);

    z = infoPT.SduDataPtr[0];
  }
  if(key == TRUE)
  {
      key = FALSE;


      StartOfRecResult = Dcm_StartOfReception(2,info_Ptr,2,NULL);

      if(StartOfRecResult == BUFREQ_OK)
      {
          /*
           * Expected value of CopyRxResult is BUFREQ_OK
           */
          CopyRxResult = Dcm_CopyRxData(2,info_Ptr,NULL);
          if(CopyRxResult == BUFREQ_OK)
          {
              Dcm_TpRxIndication(20,CopyRxResult);
          }
      }
  }
}

#elif COPYING_LARGE_DATA_IN_GLOBAL_BUFFER
uint8 Req_Data [] = {0xBB, 0x10,0x15,0x20,0x25,0x30,0x35,0xBD};
uint8 Req_Data1[] = {0xAC, 0x50,0x55,0x60,0x65,0x70,0x80,0xAD};
uint8 Req_Data2[] = {0xBC, 0x92,0x94,0x96,0x98,0xA8,0xA8,0xDC};
const PduInfoType PduInfo =
{
 Req_Data,
 NULL,
8
};
const PduInfoType *info_Ptr = &PduInfo;
const PduInfoType PduInfo1 =
{
 Req_Data1,
 NULL,
8
};
const PduInfoType *info_Ptr1 = &PduInfo1;
const PduInfoType PduInfo2 =
{
 Req_Data2,
 NULL,
8
};
const PduInfoType *info_Ptr2 = &PduInfo2;

uint8 i;
void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;

    Dcm_CopyTransmitData(TxId,&infoPT,NULL,NULL);

    z = infoPT.SduDataPtr[0];
  }
  if(key == TRUE)
  {
      key = FALSE;


      StartOfRecResult = Dcm_StartOfReception(2,info_Ptr,24,NULL);

      if(StartOfRecResult == BUFREQ_OK)
      {
          /* You need to check values inside copyRx req service
           * Expected value of CopyRxResult is BUFREQ_OK
           */
          CopyRxResult = Dcm_CopyRxData(2,info_Ptr,NULL);
          for (i = 0; i<2;i++)
          {

              if((CopyRxResult == BUFREQ_OK) && (i == 0))
              {
                CopyRxResult = Dcm_CopyRxData(2,info_Ptr1,NULL);
              }
              else if ((CopyRxResult == BUFREQ_OK) && (i == 1))
              {

                  CopyRxResult = Dcm_CopyRxData(2,info_Ptr2,NULL);
              }

          }
          if(CopyRxResult == BUFREQ_OK)
          {
              Dcm_TpRxIndication(20,CopyRxResult);
          }
      }
  }
}
#elif COPYING_TESTER_PRESENT_DATA_IN_LOCAL_BUFFER

uint8 Buf_ReadDID[] = {0x22,0x01,0x10,0xF1,0x90};

/*Tester Present buf */
uint8 Buf_0x3E[] = {0x3E,0x80};

const PduInfoType TesInfo =
{
 Buf_0x3E,
 NULL,
 2
};

const PduInfoType RDidInfo =
{
 Buf_ReadDID,
 NULL,
 5
};
const PduInfoType *RDidinfo_Ptr = &RDidInfo;
const PduInfoType *Tesinfo_Ptr = &TesInfo;

void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;

    Dcm_CopyTransmitData(TxId,&infoPT,NULL,NULL);

    z = infoPT.SduDataPtr[0];
  }
  if(key == TRUE)
  {
      key = FALSE;

     StartOfRecResult = Dcm_StartOfReception(2,RDidinfo_Ptr,5,NULL);

      if(StartOfRecResult == BUFREQ_OK)
      {
          CopyRxResult = CopyRequestData(2,RDidinfo_Ptr,NULL);
          if(CopyRxResult == BUFREQ_OK)
          {
              Dcm_TpRxIndication(2,CopyRxResult);
          }
      }
  }
  else if(key == FALSE)
  {
      /*
       * Expected value of StartOfRecResult is BUFREQ_E_OK
       */
         StartOfRecResult = Dcm_StartOfReception(1,Tesinfo_Ptr,2,NULL);

         if(StartOfRecResult == BUFREQ_OK)
         {
          /* you need to check buffer data inside copyRx service
           * Expected value of CopyRxResult is BUFREQ_OK
           */
            CopyRxResult = CopyRequestData(1,Tesinfo_Ptr,NULL);
           if(CopyRxResult == BUFREQ_OK)
           {
                Dcm_TpRxIndication(2,CopyRxResult);
           }
         }
    }
}


/*
 * Rx_Indication Test Cases:
 */

#elif PDUR_CALLING_WITH_PARA_E_NOT_OK

uint8 Req_Data[] = {0x3E, 0x80};
const PduInfoType PduInfo =
{
 Req_Data,
 NULL,
2
};
const PduInfoType *info_Ptr = &PduInfo;

void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;

    Dcm_CopyTransmitData(TxId,&infoPT,NULL,NULL);

    z = infoPT.SduDataPtr[0];
  }
  if(key == TRUE)
  {
      key = FALSE;

        /*
         * Expected value of StartOfRecResult is BUFREQ_E_OK
         */
      StartOfRecResult = Dcm_StartOfReception(2,info_Ptr,2,NULL);

      if(StartOfRecResult == BUFREQ_OK)
      {
          CopyRxResult = CopyRequestData(2,info_Ptr,NULL);
          if(CopyRxResult == BUFREQ_OK)
          {
              /*
               * Expected to release rx buffer and reset s3Server if non default session active
               */

              Dcm_TpRxIndication(2,E_NOT_OK);
          }
      }
  }
}



#elif PDUR_CALLING_WITH_PARA_E_OK_GLOBAL_BUFFER_USED

uint8 Req_Data[] = {0x3E, 0x80};
const PduInfoType PduInfo =
{
 Req_Data,
 NULL,
2
};
const PduInfoType *info_Ptr = &PduInfo;

void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;

    Dcm_CopyTransmitData(TxId,&infoPT,NULL,NULL);

    z = infoPT.SduDataPtr[0];
  }
  if(key == TRUE)
  {
      key = FALSE;

        /*
         * Expected value of StartOfRecResult is BUFREQ_E_OK
         */
      StartOfRecResult = Dcm_StartOfReception(2,info_Ptr,2,NULL);

      if(StartOfRecResult == BUFREQ_OK)
      {
          CopyRxResult = CopyRequestData(2,info_Ptr,NULL);
          if(CopyRxResult == BUFREQ_OK)
          {
              /*
               * Expected to forward request to DSD
               */

              Dcm_TpRxIndication(2,E_OK);
          }
      }
  }
}

#elif PDUR_CALLING_WITH_PARA_E_OK_LOCAL_BUFFER_USED

uint8 Buf_ReadDID[] = {0x22,0x01,0x10,0xF1,0x90};

/*Tester Present buf */
uint8 Buf_0x3E[] = {0x3E,0x80};

const PduInfoType TesInfo =
{
 Buf_0x3E,
 NULL,
 2
};

const PduInfoType RDidInfo =
{
 Buf_ReadDID,
 NULL,
 5
};
const PduInfoType *RDidinfo_Ptr = &RDidInfo;
const PduInfoType *Tesinfo_Ptr = &TesInfo;

void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;

    Dcm_CopyTransmitData(TxId,&infoPT,NULL,NULL);

    z = infoPT.SduDataPtr[0];
  }
  if(key == TRUE)
  {
      key = FALSE;

     StartOfRecResult = Dcm_StartOfReception(2,RDidinfo_Ptr,5,NULL);

      if(StartOfRecResult == BUFREQ_OK)
      {
          CopyRxResult = CopyRequestData(2,RDidinfo_Ptr,NULL);
          if(CopyRxResult == BUFREQ_OK)
          {

              Dcm_TpRxIndication(2,CopyRxResult);
          }
      }
  }
  else if(key == FALSE)
  {
      /*
       * Expected value of StartOfRecResult is BUFREQ_E_OK
       */
         StartOfRecResult = Dcm_StartOfReception(1,Tesinfo_Ptr,2,NULL);

         if(StartOfRecResult == BUFREQ_OK)
         {
           CopyRxResult = CopyRequestData(1,Tesinfo_Ptr,NULL);
           if(CopyRxResult == BUFREQ_OK)
           {
               /*
                * Resetting of S3server
                */
                Dcm_TpRxIndication(1,CopyRxResult);
           }
         }
    }
}


/*******************************************************
 *           Test Cases for DSD Sub-Module             *
 *******************************************************/


#elif SID_OUT_OF_RANGE

uint8 Req_Data[] = {0xFF, 0x80};
const PduInfoType PduInfo =
{
 Req_Data,
 NULL,
2
};
const PduInfoType *info_Ptr = &PduInfo;

void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;

    Dcm_CopyTransmitData(TxId,&TXInfo,NULL,NULL);
                                          /* Expected value*/
    TXBufferByte_1 = TXInfo.SduDataPtr[0]; /* 0x7F */
    TXBufferByte_2 = TXInfo.SduDataPtr[1]; /* 0xFF */
    TXBufferByte_3 = TXInfo.SduDataPtr[2]; /* 0x31 DCM_E_REQUESTOUTOFRANGE*/
  }
  if(key == TRUE)
  {
      key = FALSE;

        /*
         * Expected value of StartOfRecResult is BUFREQ_E_OK
         */
      StartOfRecResult = Dcm_StartOfReception(2,info_Ptr,2,NULL);

      if(StartOfRecResult == BUFREQ_OK)
      {
          CopyRxResult = CopyRequestData(2,info_Ptr,NULL);
          if(CopyRxResult == BUFREQ_OK)
          {
              Dcm_TpRxIndication(20,CopyRxResult);
          }
      }
  }
}

#elif SID_NOT_SUPPORTED

uint8 Req_Data[] = {0x30, 0x80};
const PduInfoType PduInfo =
{
 Req_Data,
 NULL,
2
};
const PduInfoType *info_Ptr = &PduInfo;

void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;

    Dcm_CopyTransmitData(TxId,&TXInfo,NULL,NULL);
                                          /* Expected value*/
    TXBufferByte_1 = TXInfo.SduDataPtr[0]; /* 0x7F */
    TXBufferByte_2 = TXInfo.SduDataPtr[1]; /* 0x30 */
    TXBufferByte_3 = TXInfo.SduDataPtr[2]; /* 0x11 DCM_E_SERVICENOTSUPPORTED*/
  }
  if(key == TRUE)
  {
      key = FALSE;

        /*
         * Expected value of StartOfRecResult is BUFREQ_E_OK
         */
      StartOfRecResult = Dcm_StartOfReception(2,info_Ptr,2,NULL);

      if(StartOfRecResult == BUFREQ_OK)
      {
          CopyRxResult = CopyRequestData(2,info_Ptr,NULL);
          if(CopyRxResult == BUFREQ_OK)
          {
              Dcm_TpRxIndication(20,CopyRxResult);
          }
      }
  }
}

#elif NON_DEFAULT_SERVICE

uint8 Req_Data[] = {0x22, 0x80};
const PduInfoType PduInfo =
{
 Req_Data,
 NULL,
2
};
const PduInfoType *info_Ptr = &PduInfo;

void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;

    Dcm_CopyTransmitData(TxId,&TXInfo,NULL,NULL);
                                          /* Expected value*/
    TXBufferByte_1 = TXInfo.SduDataPtr[0]; /* 0x7F */
    TXBufferByte_2 = TXInfo.SduDataPtr[1]; /* 0x30 */
    TXBufferByte_3 = TXInfo.SduDataPtr[2]; /* 0x7F DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION*/
  }
  if(key == TRUE)
  {
      key = FALSE;

        /*
         * Expected value of StartOfRecResult is BUFREQ_E_OK
         */
      StartOfRecResult = Dcm_StartOfReception(2,info_Ptr,2,NULL);

      if(StartOfRecResult == BUFREQ_OK)
      {
          CopyRxResult = CopyRequestData(2,info_Ptr,NULL);
          if(CopyRxResult == BUFREQ_OK)
          {
              Dcm_TpRxIndication(20,CopyRxResult);
          }
      }
  }
}

#elif SERVICE_WITH_SECURITY_LEV_1

uint8 Buf_ReadDID[] = {0x22,0x01,0x10,0xF1,0x90};

/*Tester Present buf */
uint8 Buf_0x10[] = {0x10, DCM_EXTENDED_DIAGNOSTIC_SESSION};

const PduInfoType TesInfo =
{
 Buf_0x10,
 NULL,
 2
};

const PduInfoType RDidInfo =
{
 Buf_ReadDID,
 NULL,
 5
};
const PduInfoType *RDidinfo_Ptr = &RDidInfo;
const PduInfoType *Sessinfo_Ptr = &TesInfo;

void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;

    Dcm_CopyTransmitData(TxId,&TXInfo,NULL,NULL);
                                            /* Expected value*/
    TXBufferByte_1 = TXInfo.SduDataPtr[0]; /* 0x7F */
    TXBufferByte_2 = TXInfo.SduDataPtr[1]; /* 0x30 */
    TXBufferByte_3 = TXInfo.SduDataPtr[2]; /* 0x33 DCM_E_SECURITYACCESSDENIED*/

  }
  if(key == TRUE)
  {
      key = FALSE;

     StartOfRecResult = Dcm_StartOfReception(2,Sessinfo_Ptr,2,NULL);

      if(StartOfRecResult == BUFREQ_OK)
      {
          CopyRxResult = CopyRequestData(2,Sessinfo_Ptr,NULL);
          if(CopyRxResult == BUFREQ_OK)
          {
              Dcm_TpRxIndication(2,CopyRxResult);
          }
      }
  }
  else if(key == FALSE)
  {
      /*
       * Expected value of StartOfRecResult is BUFREQ_E_OK
       */
         StartOfRecResult = Dcm_StartOfReception(2,RDidinfo_Ptr,5,NULL);

         if(StartOfRecResult == BUFREQ_OK)
         {
           CopyRxResult = CopyRequestData(2,RDidinfo_Ptr,NULL);
           if(CopyRxResult == BUFREQ_OK)
           {
                Dcm_TpRxIndication(2,CopyRxResult);
           }
         }
    }
}


#elif SERVICE_WITH_SUPPRESSED_POS_RES

uint8 Req_Data[] = {0x10, 0x82};
const PduInfoType PduInfo =
{
 Req_Data,
 NULL,
2
};
const PduInfoType *info_Ptr = &PduInfo;

void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;

    Dcm_CopyTransmitData(TxId,&infoPT,NULL,NULL);

    TXBufferByte_1 = infoPT.SduDataPtr[0];
  }
  if(key == TRUE)
  {
      key = FALSE;

        /*
         * Expected value of StartOfRecResult is BUFREQ_E_OK
         */
      StartOfRecResult = Dcm_StartOfReception(2,info_Ptr,2,NULL);

      if(StartOfRecResult == BUFREQ_OK)
      {
          CopyRxResult = CopyRequestData(2,info_Ptr,NULL);
          if(CopyRxResult == BUFREQ_OK)
          {
              Dcm_TpRxIndication(2,CopyRxResult);
          }
      }
  }
}


/**********************************
 *  Test Cases for DSP Sub-Module *
 **********************************/


/*
 * Tester present and session control test cases
 */

#elif SESSION_CONTROL_WITHOUT_TESTER_PRESENT

uint8 arrP[] = {0x10,DCM_EXTENDED_DIAGNOSTIC_SESSION};

const PduInfoType infoP =
{
 arrP,
 NULL,
 2
};
const PduInfoType *info1P = &infoP;

void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;
    Dcm_CopyTransmitData(TxId,&TXInfo,NULL,NULL);
                                        /* Expected value*/
    TXBufferByte_1 = TXInfo.SduDataPtr[0]; /* 0x50 */
    TXBufferByte_2 = TXInfo.SduDataPtr[1]; /* 0x02 */
    TXBufferByte_3 = TXInfo.SduDataPtr[2];

  }
  if(key == TRUE)
  {
      key = FALSE;
      StartOfRecResult = AcceptNewConnection(2,info1P,2,NULL);
      if(StartOfRecResult == BUFREQ_OK)
      {
          CopyRxResult = CopyRequestData(2,info1P,NULL);
          if(CopyRxResult == BUFREQ_OK)
          {
              Dcm_PduRToDslIndication(2,CopyRxResult);
          }
      }
  }
}
#elif PHYSICAL_TESTER_PRESENT_WITHOUT_SESSION_CONTROL

uint8 Buf_TesterPresent[] = {0x3E, 0x00};

const PduInfoType TpInfo =
{
 Buf_TesterPresent,
 NULL,
 2
};
const PduInfoType *Tpinfo_Ptr = &TpInfo;

void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;
    Dcm_CopyTransmitData(TxId,&TXInfo,NULL,NULL);
                                        /* Expected value*/
        TXBufferByte_1 = TXInfo.SduDataPtr[0]; /* 0x7F */
        TXBufferByte_2 = TXInfo.SduDataPtr[1]; /* 0x3E */
        TXBufferByte_3 = TXInfo.SduDataPtr[2]; /* 0x7F */

  }
  if(key == TRUE)
  {
      key = FALSE;
      StartOfRecResult = AcceptNewConnection(2,Tpinfo_Ptr,2,NULL);
      if(StartOfRecResult == BUFREQ_OK)
      {
          CopyRxResult = CopyRequestData(2,Tpinfo_Ptr,NULL);
          if(CopyRxResult == BUFREQ_OK)
          {
              Dcm_PduRToDslIndication(2,CopyRxResult);
          }
      }
  }
}
#elif SESSION_CONTROL_WITH_FUNCTIONAL_TESTER_PRESENT

uint8 arrP[] = {0x10,DCM_EXTENDED_DIAGNOSTIC_SESSION};

const PduInfoType infoP =
{
 arrP,
 NULL,
 2
};
const PduInfoType *info1P = &infoP;

uint8 Buf_TesterPresent[] =  {0x3E, 0x80};

const PduInfoType TpInfo =
{
 Buf_TesterPresent,
 NULL,
 2
};
const PduInfoType *Tpinfo_Ptr = &TpInfo;


void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;
    Dcm_CopyTransmitData(TxId,&TXInfo,NULL,NULL);

  }
  if(key == TRUE)
  {
      key = FALSE;
      StartOfRecResult = AcceptNewConnection(2,info1P,2,NULL);
      if(StartOfRecResult == BUFREQ_OK)
      {
          CopyRxResult = CopyRequestData(2,info1P,NULL);
          if(CopyRxResult == BUFREQ_OK)
          {
              Dcm_PduRToDslIndication(2,CopyRxResult);
          }
      }
  }

  else if(key == FALSE)
  {
      StartOfRecResult = AcceptNewConnection(1,Tpinfo_Ptr,2,NULL);
       if(StartOfRecResult == BUFREQ_OK)
       {
           CopyRxResult = CopyRequestData(1,Tpinfo_Ptr,NULL);
          if(CopyRxResult == BUFREQ_OK)
          {
              Dcm_PduRToDslIndication(1,CopyRxResult);
          }
       }
  }

}

/*
 * Read Data By ID test cases
 */

#elif READ_DATA_BY_ID_WITH_INVALID_SESSION

uint8 Buf_ReadDID[] = {0x22,0x01,0x10};

const PduInfoType RDidInfo =
{
 Buf_ReadDID,
 NULL,
 3
};
const PduInfoType *RDidinfo_Ptr = &RDidInfo;

void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;
    result = Dcm_CopyTransmitData(TxId,&TXInfo,NULL,NULL);
    Dcm_TpTxConfirmation(TxId,result);
    TXBufferByte_1 = TXInfo.SduDataPtr[0]; //0x7F
    TXBufferByte_2 = TXInfo.SduDataPtr[1]; //0x27
    TXBufferByte_3 = TXInfo.SduDataPtr[2]; //0x37
  }
  if(key == TRUE)
    {
        key = FALSE;
        StartOfRecResult = AcceptNewConnection(2,RDidinfo_Ptr,3,NULL);
        if(StartOfRecResult == BUFREQ_OK)
        {
            CopyRxResult = CopyRequestData(2,RDidinfo_Ptr,NULL);
            if(CopyRxResult == BUFREQ_OK)
            {
                Dcm_PduRToDslIndication(2,CopyRxResult);
            }
        }
    }
  }


#elif READ_DATA_BY_ID_WITH_VALID_SESSION

uint8 Counter = 0;
uint32 totalLength = 2;

uint8 Buf_ReadDID[5] = {0x10,DCM_EXTENDED_DIAGNOSTIC_SESSION};

PduInfoType RDidInfo =
{
 Buf_ReadDID,
 NULL,
 2
};
const PduInfoType *RDidinfo_Ptr = &RDidInfo;

void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;
    result = Dcm_CopyTransmitData(TxId,&TXInfo,NULL,NULL);
    Dcm_TpTxConfirmation(TxId,result);
    TXBufferByte_1 = TXInfo.SduDataPtr[0]; //0x7F
    TXBufferByte_2 = TXInfo.SduDataPtr[1]; //0x27
    TXBufferByte_3 = TXInfo.SduDataPtr[2]; //0x37
    if (Counter == 0)
    {
        key = TRUE;
        Buf_ReadDID[0] = 0x22;
        Buf_ReadDID[1] = 0x01;
        Buf_ReadDID[2] = 0x10;
        RDidInfo.SduLength = 3;
        totalLength = 3;
        Counter++;
    }
    /*
    else if (counter == 1)
    {
        Buf_ReadDID[0] = 0x22;
        Buf_ReadDID[1] = 0x01;
        Buf_ReadDID[2] = 0x10;
        RDidInfo.SduLength = 3;
        totalLength = 3;
    }
    */

  }
  if(key == TRUE)
    {
        key = FALSE;
        StartOfRecResult = AcceptNewConnection(2,RDidinfo_Ptr,totalLength,NULL);
        if(StartOfRecResult == BUFREQ_OK)
        {
            CopyRxResult = CopyRequestData(2,RDidinfo_Ptr,NULL);
            if(CopyRxResult == BUFREQ_OK)
            {
                Dcm_PduRToDslIndication(2,CopyRxResult);
            }
        }
    }
  }


#elif READ_DATA_BY_ID_WITH_VALID_SESSION_VALID_SEC

uint16 Key_Send , Seed;
uint8 Counter = 0;
uint32 totalLength = 2;

uint8 Buf_ReadDID[5] = {0x10,DCM_EXTENDED_DIAGNOSTIC_SESSION};

PduInfoType RDidInfo =
{
 Buf_ReadDID,
 NULL,
 2
};
const PduInfoType *RDidinfo_Ptr = &RDidInfo;

void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;
    result = Dcm_CopyTransmitData(TxId,&TXInfo,NULL,NULL);
    Dcm_TpTxConfirmation(TxId,result);
    TXBufferByte_1 = TXInfo.SduDataPtr[0]; //0x7F
    TXBufferByte_2 = TXInfo.SduDataPtr[1]; //0x27
    TXBufferByte_3 = TXInfo.SduDataPtr[2]; //0x37
    TXBufferByte_4 = TXInfo.SduDataPtr[3];
    TXBufferByte_5 = TXInfo.SduDataPtr[4];
    if (Counter == 1)
    {
       key = TRUE;
       Counter++;
    }
    else if (Counter == 0)
    {
        key = TRUE;
        Buf_ReadDID[0] = 0x27;
        Buf_ReadDID[1] = 0x01;

        RDidInfo.SduLength = 2;
        totalLength = 2;
        Counter++;
    }

    else if (Counter == 2)
    {
        key = TRUE;
        Buf_ReadDID[0] = 0x27;
        Buf_ReadDID[1] = 0x02;
        Seed  = ((uint16)TXInfo.SduDataPtr[2] << 8);
        Seed += (uint16)TXInfo.SduDataPtr[3];

        Convert_To_TowsComplement(Seed,&Key_Send);


        Buf_ReadDID[2] = (Key_Send >> 8) & 0xFF;
        Buf_ReadDID[3] = (Key_Send & 0xFF);

        RDidInfo.SduLength = 4;
        totalLength =4;
        Counter++;
    }
    else if (Counter == 3)
    {
            key = TRUE;
            Buf_ReadDID[0] = 0x22;
            Buf_ReadDID[1] = 0x01;
            Buf_ReadDID[2] = 0x10;
            RDidInfo.SduLength = 3;
            totalLength = 3;
    }


  }
  if(key == TRUE)
    {
        key = FALSE;
        StartOfRecResult = AcceptNewConnection(2,RDidinfo_Ptr,totalLength,NULL);
        if(StartOfRecResult == BUFREQ_OK)
        {
            CopyRxResult = CopyRequestData(2,RDidinfo_Ptr,NULL);
            if(CopyRxResult == BUFREQ_OK)
            {
                Dcm_PduRToDslIndication(2,CopyRxResult);
            }
        }
    }
  }



#elif READ_DATA_BY_ID_TWO_DID_SYN_ASYN

uint8 Buf_ReadDID[] = {0x22,0x01,0x0A};

const PduInfoType RDidInfo =
{
 Buf_ReadDID,
 NULL,
 3
};
const PduInfoType *RDidinfo_Ptr = &RDidInfo;

void Pdur_main(void)
{
    uint8 a,b,c,d,e,f,g,h,i,j,k,m,n,l,o,q,r,s;
    uint32 len;
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;
    Dcm_CopyTransmitData(TxId,&TXInfo,NULL,NULL);
    len = TXInfo.SduLength;
    a = TXInfo.SduDataPtr[0]; //0x62
    b = TXInfo.SduDataPtr[1]; //0x01
    c = TXInfo.SduDataPtr[2]; //0x10
    d = TXInfo.SduDataPtr[3]; //0x8C
    e = TXInfo.SduDataPtr[4]; //0xF1
    f = TXInfo.SduDataPtr[5]; //0x90
    g = TXInfo.SduDataPtr[6]; //0x57
    h = TXInfo.SduDataPtr[7]; //0x30
    i = TXInfo.SduDataPtr[8]; //0x4C
    j = TXInfo.SduDataPtr[9]; //0x30
    k = TXInfo.SduDataPtr[10]; //0x32
    m = TXInfo.SduDataPtr[11]; //0x36
    n = TXInfo.SduDataPtr[12];
    l = TXInfo.SduDataPtr[14];
    o = TXInfo.SduDataPtr[15];
    q = TXInfo.SduDataPtr[16];
    r = TXInfo.SduDataPtr[17];
    s = TXInfo.SduDataPtr[18];
  }
  if(key == TRUE)
    {
        key = FALSE;
        StartOfRecResult = AcceptNewConnection(2,RDidinfo_Ptr,3,NULL);
        if(StartOfRecResult == BUFREQ_OK)
        {
            CopyRxResult = CopyRequestData(2,RDidinfo_Ptr,NULL);
            if(CopyRxResult == BUFREQ_OK)
            {
                Dcm_PduRToDslIndication(2,CopyRxResult);
            }
        }
    }
  }
#elif SECURITY_ACCESS_BEFORE_BOOT_TIMER_EXPIRED

uint8 Buf_TesterPresent[5] = {0x27, 0x01};

 PduInfoType TpInfo =
{
 Buf_TesterPresent,
 NULL,
 2
};
const PduInfoType *Tpinfo_Ptr = &TpInfo;
uint8 a,b,c;
uint8 counter = 0;
boolean Keys = TRUE;
uint32 totalSize = 2;
void Pdur_main(void)
{

  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;
   result = Dcm_CopyTransmitData(TxId,&TXInfo,NULL,NULL);
    Dcm_TpTxConfirmation(TxId,result);
    TXBufferByte_1 = TXInfo.SduDataPtr[0]; //0x7F
    TXBufferByte_2 = TXInfo.SduDataPtr[1]; //0x27
    TXBufferByte_3 = TXInfo.SduDataPtr[2]; //0x37
    if (SID_NEGATIVE_RESPONSE == TXBufferByte_1)
    {
        key = TRUE;
    }
  }
  if(key == TRUE)
  {
      key = FALSE;
      StartOfRecResult = AcceptNewConnection(2,Tpinfo_Ptr,totalSize,NULL);
      if(StartOfRecResult == BUFREQ_OK)
      {
          CopyRxResult = CopyRequestData(2,Tpinfo_Ptr,NULL);
          if(CopyRxResult == BUFREQ_OK)
          {
              Dcm_PduRToDslIndication(2,CopyRxResult);
          }
      }
  }
}
#elif SECURITY_ACCESS_GET_SEED_AND_COMPARE_KEY

uint8 Buf_sec[5] = {0x27,0x01};
uint16 Key_Send , Seed;
 PduInfoType TpInfo =
{
 Buf_sec,
 NULL,
 2
};
const PduInfoType *Tpinfo_Ptr = &TpInfo;
uint8 a,b,c;
uint8 counter = 0;
boolean Keys = TRUE;
uint32 totalSize = 2;
void Pdur_main(void)
{

  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;
    result = Dcm_CopyTransmitData(TxId,&TXInfo,NULL,NULL);
    Dcm_TpTxConfirmation(TxId,result);
    TXBufferByte_1 = TXInfo.SduDataPtr[0];
    a = TXInfo.SduDataPtr[1];
    b = TXInfo.SduDataPtr[2];
    c = TXInfo.SduDataPtr[3];
    if (SID_NEGATIVE_RESPONSE == TXBufferByte_1)
    {
        key = TRUE;
    }
    else if(TXBufferByte_1 == 0x67)
    {

        key = TRUE;

        Seed  = ((uint16)TXInfo.SduDataPtr[2] << 8);
        Seed += (uint16)TXInfo.SduDataPtr[3];

        Convert_To_TowsComplement(Seed,&Key_Send);

        Buf_sec[1] = 0x02;
        Buf_sec[2] = (Key_Send >> 8) & 0xFF;
        Buf_sec[3] = (Key_Send & 0xFF);

        TpInfo.SduLength = 4;
        totalSize =4;

    }

  }
  if(key == TRUE)
  {
      key = FALSE;
      StartOfRecResult = AcceptNewConnection(2,Tpinfo_Ptr,totalSize,NULL);
      if(StartOfRecResult == BUFREQ_OK)
      {
          CopyRxResult = CopyRequestData(2,Tpinfo_Ptr,NULL);
          if(CopyRxResult == BUFREQ_OK)
          {
              Dcm_PduRToDslIndication(2,CopyRxResult);
          }
      }
  }
}


#elif SECURITY_ACCESS_TEST_FAILD_CASES_PENDING

uint8 Buf_sec[5] = {0x27, 0x01};
uint16 Key_Send , Seed;
 PduInfoType TpInfo =
{
 Buf_sec,
 NULL,
 2
};
const PduInfoType *Tpinfo_Ptr = &TpInfo;
uint8 a,b,c;
uint8 counter = 0;
boolean Keys = TRUE;
uint32 totalSize = 2;
void Pdur_main(void)
{

  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;
    result = Dcm_CopyTransmitData(TxId,&TXInfo,NULL,NULL);
    Dcm_TpTxConfirmation(TxId,result);
    TXBufferByte_1 = TXInfo.SduDataPtr[0]; //0x67
    a = TXInfo.SduDataPtr[1]; //0x01
    b = TXInfo.SduDataPtr[2]; //0x36
    c = TXInfo.SduDataPtr[3]; //0x57
    if ((SID_NEGATIVE_RESPONSE == TXBufferByte_1) && (counter < 4))
    {
        key = TRUE;
        counter++;
    }
    else if((TXBufferByte_1 == 0x67) && (Keys == TRUE))
    {
        Seed  = ((uint16)TXInfo.SduDataPtr[2] << 8);
        Seed += (uint16)TXInfo.SduDataPtr[3];

        Keys = FALSE;
        key = TRUE;
        Buf_sec[1] = 0x02;
        Buf_sec[2] = 0x50;
        Buf_sec[3] = 0xA9;
        TpInfo.SduLength = 4;
        totalSize =4;
        counter++;
    }
    else if(counter >= 4)
    {
        key = TRUE;

        Convert_To_TowsComplement(Seed,&Key_Send);

        Buf_sec[1] = 0x02;
        Buf_sec[2] = (Key_Send >> 8) & 0xFF;
        Buf_sec[3] = (Key_Send & 0xFF);

        TpInfo.SduLength = 4;
        totalSize =4;
    }
  }
  if(key == TRUE)
  {
      key = FALSE;
      StartOfRecResult = AcceptNewConnection(2,Tpinfo_Ptr,totalSize,NULL);
      if(StartOfRecResult == BUFREQ_OK)
      {
          CopyRxResult = CopyRequestData(2,Tpinfo_Ptr,NULL);
          if(CopyRxResult == BUFREQ_OK)
          {
              Dcm_PduRToDslIndication(2,CopyRxResult);
          }
      }
  }
}
#elif ROUTINE_CONTROL_TESTING
uint16 Key_Send , Seed;
uint8 Counter = 0;
uint32 totalLength = 2;

uint8 Buf_ReadDID[5] = {0x10,0x02};

PduInfoType RDidInfo =
{
 Buf_ReadDID,
 NULL,
 2
};
const PduInfoType *RDidinfo_Ptr = &RDidInfo;

void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;
    result = Dcm_CopyTransmitData(TxId,&TXInfo,NULL,NULL);
    Dcm_TpTxConfirmation(TxId,result);
    TXBufferByte_1 = TXInfo.SduDataPtr[0]; //0x7F
    TXBufferByte_2 = TXInfo.SduDataPtr[1]; //0x27
    TXBufferByte_3 = TXInfo.SduDataPtr[2]; //0x37
    TXBufferByte_4 = TXInfo.SduDataPtr[3];
    TXBufferByte_5 = TXInfo.SduDataPtr[4];
    if(Counter == 1)
    {
        key = TRUE;
        Buf_ReadDID[1] = 0x03;
        Counter++;
    }
    else if (Counter == 0)
    {
        key = TRUE;
        Buf_ReadDID[0] = 0x31;
        Buf_ReadDID[1] = 0x01;
        Buf_ReadDID[2] = 0x02;
        Buf_ReadDID[3] = 0x02;
        RDidInfo.SduLength = 4;
        totalLength = 4;
        Counter++;
    }

    else if (Counter == 2)
    {
        key = TRUE;
        Buf_ReadDID[0] = 0x27;
        Buf_ReadDID[1] = 0x02;
        Seed  = ((uint16)TXInfo.SduDataPtr[2] << 8);
        Seed += (uint16)TXInfo.SduDataPtr[3];

        Convert_To_TowsComplement(Seed,&Key_Send);


        Buf_ReadDID[2] = (Key_Send >> 8) & 0xFF;
        Buf_ReadDID[3] = (Key_Send & 0xFF);

        RDidInfo.SduLength = 4;
        totalLength =4;
        Counter++;
    }
    else if (Counter == 3)
    {
            key = TRUE;
            Buf_ReadDID[0] = 0x22;
            Buf_ReadDID[1] = 0x01;
            Buf_ReadDID[2] = 0x10;
            RDidInfo.SduLength = 3;
            totalLength = 3;
    }


  }
  if(key == TRUE)
    {
        key = FALSE;
        StartOfRecResult = AcceptNewConnection(2,RDidinfo_Ptr,totalLength,NULL);
        if(StartOfRecResult == BUFREQ_OK)
        {
            CopyRxResult = CopyRequestData(2,RDidinfo_Ptr,NULL);
            if(CopyRxResult == BUFREQ_OK)
            {
                Dcm_PduRToDslIndication(2,CopyRxResult);
            }
        }
    }
  }

#elif WRITE_DATA_BY_ID

//uint8 Buf_ReadDID[] = {0x2E,0xF1,0x90,0x57,0x30,0x4C,0x30,0x30,0x30,0x30,0x34,0x33,0x4D,0x42,0x35,0x34,0x31,0x33,0x30,0x32,0x36};

uint8 Buf_ReadDID[] = {0x2E,0x01,0x0A,0x05,0x10,0x15,0x20,0x25,0x30,0x35,0x40,0x45,0x50,0x55,0x60,0x65,0x70,0x75};

const PduInfoType RDidInfo =
{
 Buf_ReadDID,
 NULL,
 18
};
const PduInfoType *RDidinfo_Ptr = &RDidInfo;

void Pdur_main(void)
{
  if (TRUE == PduR_DcmResponseFlag)
  {
    PduR_DcmResponseFlag = FALSE;
    result = Dcm_CopyTransmitData(TxId,&TXInfo,NULL,NULL);
    Dcm_TpTxConfirmation(TxId,result);
    TXBufferByte_1 = TXInfo.SduDataPtr[0]; //0x7F
    TXBufferByte_2 = TXInfo.SduDataPtr[1]; //0x27
    TXBufferByte_3 = TXInfo.SduDataPtr[2]; //0x37
  }
  if(key == TRUE)
    {
        key = FALSE;
        StartOfRecResult = AcceptNewConnection(2,RDidinfo_Ptr,18,NULL);
        if(StartOfRecResult == BUFREQ_OK)
        {
            CopyRxResult = CopyRequestData(2,RDidinfo_Ptr,NULL);
            if(CopyRxResult == BUFREQ_OK)
            {
                Dcm_PduRToDslIndication(2,CopyRxResult);
            }
        }
    }
  }

#elif PRESENTATION_DEMO
uint32 xo, ReqLen = 3;
uint16 Key_Send , Seed;
uint8 Buf_ReadDID[5] = {0x22,0xF1,0x90};

PduInfoType RDidInfo =
{
     g_UART0_BufferRX,
     NULL,
     3
};

const PduInfoType *RDidinfo_Ptr = &RDidInfo;

void Pdur_main(void)
{
    uint8 result;

    if (TRUE == PduR_DcmResponseFlag)
    {
        PduR_DcmResponseFlag = FALSE;
        result = Dcm_CopyTransmitData(TxId,&TXInfo,NULL,NULL);
        Dcm_TpTxConfirmation(TxId,result);
        g_UART0_BufferTX[TXInfo.SduLength] = 0;
        g_UART0_TransmitFlag = true;
    }

    if(g_UART0_DeliveryFlag == TRUE)
    {
        g_UART0_DeliveryFlag = FALSE;
        RDidInfo.SduLength = g_UART0_DeliveredBytes;
        StartOfRecResult = AcceptNewConnection(2,RDidinfo_Ptr,RDidInfo.SduLength,NULL);
        if(StartOfRecResult == BUFREQ_OK)
        {
            CopyRxResult = CopyRequestData(2,RDidinfo_Ptr,NULL);
            if(CopyRxResult == BUFREQ_OK)
            {
                Dcm_PduRToDslIndication(2, CopyRxResult);
            }
        }
    }
}


#endif



/******************************************************************************
 * Service Name      : PduR_DcmTransmit                                       *
 * DCM_SWS_FUNC      : YES                                                    *
 * Sync/Async        : Synchronous                                            *
 * Reentrancy        : Non reentrant                                          *
 * Parameters(in)    : 1-TxPduId                                              *
 *                     2-PduInfo                                              *
 * Parameters(inOut) : None                                                   *
 * Parameters(out)   : None                                                   *
 * Return value      : None                                                   *
 * Description       : This Function used to Indicate PduR Module to call     *
 *                     CopyTxData when Dcm Response is ready.                 *
 ******************************************************************************/

Std_ReturnType PduR_DcmTransmit(PduIdType TxPduId, PduInfoType *TxPduInfo)
{
    Std_ReturnType ret = E_NOT_OK;

    PduR_DcmResponseFlag = TRUE;
    TxId = TxPduId;
    TXInfo.SduLength = TxPduInfo->SduLength;
    ret = E_OK;

    return ret;
}
