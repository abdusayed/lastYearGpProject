/******************************************************************************
 * Module      : Application Demo                                             *
 * File Name   : DiagHandler.c                                                *
 * Description : Source file of Application Demo Services                     *
 * Created on  : April 6, 2020                                                *
 ******************************************************************************/

#include "DiagHandler.h"
#include <stdlib.h>
#include <time.h>
#include <uart_stdio.h>

static boolean Compare_Key(uint16 Tester_Key,uint16 Actual_Key);


uint8 AppBuff[18];
boolean keyL = FALSE;
boolean keyD = FALSE;
boolean keyR = FALSE;
boolean VIN_Key = TRUE;
uint16 Lev1_GetSeed = 0;
uint16 Lev1_CompareKey = 0;
uint16 DataLengthTemp = 1;
uint16 DataLengthth = 1;




/*******************
 * Read Data By ID *
 *******************/









Std_ReturnType EngineCoolantTemp_ReadSyn(uint8* Data)
{

 Data[0] = 0xA6;

 return E_OK;
}
Std_ReturnType EngineSpeed_ReadSyn(uint8* Data)
{
  Data[0] = 0x07;
  Data[1] = 0x50;
  return E_OK;
}


uint8 VIN_NUM[]={0x05,0x2F,0x19,0x05,0x30, 0x49};

Std_ReturnType UDS_batteryPositiveVoltageConditionCheckRead(Dcm_NegativeResponseCodeType* ErrorCode)
{
    return E_OK;
}




Std_ReturnType UDS_batteryPositiveVoltageDataReadDataLengthSyn(uint16* DataLength)
{
    *DataLength = 1;

    return E_OK;
}

#define Rte_Call_Dcm_Pp_0xF100_VINNum(Data)  UDS_batteryPositiveVoltageDataReadDataLengthSyn(Data)

Std_ReturnType UDS_batteryPositiveVoltageDataReadSyn(uint8* Data)
{
    Data[0] = 0x8C;
    return E_OK;
}

Std_ReturnType UDS_VINNum_ConditionCheckRead(Dcm_NegativeResponseCodeType* ErrorCode)
{
    return E_OK;
}
Std_ReturnType UDS_VINNum_DataReadDataLengthASyn(Dcm_OpStatusType OpStatus, uint16* DataLength)
{
    Std_ReturnType result;

    if (keyL == FALSE)
    {
        keyL = TRUE;
      result = DCM_E_PENDING;
    }
    else
    {
        *DataLength = 18;
        result = E_OK;
    }
     return result;
}

Std_ReturnType UDS_VINNum_DataReadASyn(Dcm_OpStatusType OpStatus,uint8* Data)
{
    Std_ReturnType result;
    int i;
    if(TRUE == VIN_Key)
    {
      VIN_Key = FALSE;
      result = DCM_E_PENDING;
    }
    else
    {
        for(i = 0; i<6; i++)
        {
            Data[i] = VIN_NUM[i];
        }
        result = E_OK;
    }
    return result;
}





Std_ReturnType ThrottlePosition_ReadSyn(Dcm_OpStatusType OpStatus,uint8* Data)
{
  Std_ReturnType result;
  if (keyL == FALSE)
  {
      keyL = TRUE;
    result = DCM_E_PENDING;
  }
  else
  {
      Data[0] = 0x66;

      result = E_OK;
  }
   return result;
}
#if SECURITY_ACCESS_TEST_FAILD_CASES_PENDING
Std_ReturnType UDS_GetSeed_Lev1ASyn(Dcm_OpStatusType OpStatus, uint8* Seed, Dcm_NegativeResponseCodeType* ErrorCode)
{
    Std_ReturnType result;
   if (FALSE == keyL)
   {
       keyL = TRUE;
       result = DCM_E_PENDING;
   }
   else
   {
   srand(time(0)+65536);
   Lev1_GetSeed = (rand() % 65536);
    Seed[0] = (Lev1_GetSeed >> 8) & 0xFF;
    Seed[1] = (Lev1_GetSeed & 0xFF);
    result = E_OK;
   }
   return result;
}
#endif



#if SECURITY_ACCESS_GET_SEED_AND_COMPARE_KEY
Std_ReturnType UDS_GetSeed_Lev1ASyn(Dcm_OpStatusType OpStatus, uint8* Seed, Dcm_NegativeResponseCodeType* ErrorCode)
{
   srand(time(0)+65536);
   Lev1_GetSeed = (rand() % 65536);
    Seed[0] = (Lev1_GetSeed >> 8) & 0xFF;
    Seed[1] = (Lev1_GetSeed & 0xFF);
    return E_OK;
}
#endif
void Convert_To_TowsComplement(uint16 Seed,uint16 *Key)
{
    *Key = Seed ^ 0xFFFF;
    *Key += 1;
}

static boolean Compare_Key(uint16 Tester_Key,uint16 Actual_Key)
{
    boolean status;

    if (Tester_Key ^ Actual_Key)
    {
       status = FALSE;
    }
    else
    {
        status = TRUE;
    }
    return status;
}

Std_ReturnType UDS_GetSeed_Lev1ASyn(Dcm_OpStatusType OpStatus, uint8* Seed, Dcm_NegativeResponseCodeType* ErrorCode)
{
    srand(time(0)+65536);
    Lev1_GetSeed = (rand() % 65536);
    Seed[0] = (Lev1_GetSeed >> 8) & 0xFF;
    Seed[1] = (Lev1_GetSeed & 0xFF);
    return E_OK;
}



Std_ReturnType UDS_CompareKey_Lev1ASyn(const uint8* Key, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType* ErrorCode )
{
    Std_ReturnType result;
    uint16 Tester_Key;
    Tester_Key = ((uint16)Key[0] << 8);
    Tester_Key += ((uint16)Key[1]);

    Convert_To_TowsComplement(Lev1_GetSeed,&Lev1_CompareKey);

    if (TRUE == Compare_Key(Tester_Key,Lev1_CompareKey))
    {
      result = E_OK;
    }
    else
    {
        result = DCM_E_COMPARE_KEY_FAILED;
        //result = E_OK;
    }
    return result;
}

#if SECURITY_ACCESS_TEST_FAILD_CASES_PENDING

Std_ReturnType UDS_CompareKey_Lev1ASyn(const uint8* Key, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType* ErrorCode )
{
    Std_ReturnType result;
    uint16 Tester_Key;
    if(FALSE == keyD)
    {
        keyD = TRUE;
        result = DCM_E_PENDING;
    }
    else
    {
        Tester_Key = ((uint16)Key[0] << 8);
        Tester_Key += ((uint16)Key[1]);
        Convert_To_TowsComplement(Lev1_GetSeed,&Lev1_CompareKey);
        if (TRUE == Compare_Key(Tester_Key,Lev1_CompareKey))
        {
          result = E_OK;
        }
        else
        {
            result = DCM_E_COMPARE_KEY_FAILED;
        }
    }
    return result;
}
#endif

#if SECURITY_ACCESS_GET_SEED_AND_COMPARE_KEY
Std_ReturnType UDS_CompareKey_Lev1ASyn(const uint8* Key, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType* ErrorCode )
{
    Std_ReturnType result;
    uint16 Tester_Key;
    Tester_Key = ((uint16)Key[0] << 8);
    Tester_Key += ((uint16)Key[1]);
    Convert_To_TowsComplement(Lev1_GetSeed,&Lev1_CompareKey);
    if (TRUE == Compare_Key(Tester_Key,Lev1_CompareKey))
    {
      result = E_OK;
    }
    else
    {
        result = DCM_E_COMPARE_KEY_FAILED;
    }
    return result;
}
#endif


