/******************************************************************************
 * Module      : Application Demo                                             *
 * File Name   : DiagHandler.h                                                *
 * Description : Header file of Application Demo Services                     *
 * Created on  : April 6, 2020                                                *
 ******************************************************************************/

#ifndef DIAGHANDLER_H_
#define DIAGHANDLER_H_

#include "Std_Types.h"
#include "Dcm_Types.h"

extern void RoutinResultMain_0x0202(void);

extern void Convert_To_TowsComplement(uint16 Seed,uint16 *Key);

extern Std_ReturnType UDS_batteryPositiveVoltageConditionCheckRead(Dcm_NegativeResponseCodeType* ErrorCode);

extern Std_ReturnType UDS_batteryPositiveVoltageDataReadDataLengthSyn(uint16* DataLength);

extern Std_ReturnType UDS_batteryPositiveVoltageDataReadSyn(uint8* Data);

extern Std_ReturnType UDS_VINNum_ConditionCheckRead(Dcm_NegativeResponseCodeType* ErrorCode);

extern Std_ReturnType UDS_VINNum_DataReadDataLengthASyn(Dcm_OpStatusType OpStatus, uint16* DataLength);

extern Std_ReturnType UDS_VINNum_DataReadASyn(Dcm_OpStatusType OpStatus,uint8* Data);

extern Std_ReturnType UDS_GetSeed_Lev1ASyn(Dcm_OpStatusType OpStatus,
                                           uint8* Seed,
                                           Dcm_NegativeResponseCodeType* ErrorCode);

extern Std_ReturnType UDS_CompareKey_Lev1ASyn(const uint8* Key,
                                              Dcm_OpStatusType OpStatus,
                                              Dcm_NegativeResponseCodeType* ErrorCode);

extern Std_ReturnType UDS_VINNum_DataWriteASyn (const uint8* Data,
                                                Dcm_OpStatusType OpStatus,
                                                Dcm_NegativeResponseCodeType* ErrorCode);

extern Std_ReturnType StartRoutine_0x0202(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType* ErrorCode);

extern Std_ReturnType StoptRoutine_0x0202(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType* ErrorCode);

extern Std_ReturnType ReqRoutineRes_0x0202(Dcm_OpStatusType OpStatus,
                                           uint8* dataOutVar,
                                           uint16* variableDataLength,
                                           Dcm_NegativeResponseCodeType* ErrorCode);
Std_ReturnType ThrottlePosition_WriteSyn(const uint8* Data,Dcm_OpStatusType OpStatus,Dcm_NegativeResponseCodeType* ErrorCode);
Std_ReturnType EngineSpeed_WriteSyn(const uint8* Data,uint16 DataLength, Dcm_NegativeResponseCodeType* ErrorCode);
Std_ReturnType EngineCoolantTemp_WriteSyn(const uint8* Data , Dcm_NegativeResponseCodeType* ErrorCode);
Std_ReturnType ThrottlePosition_ReadSyn(Dcm_OpStatusType OpStatus,uint8* Data);
Std_ReturnType EngineCoolantTemp_ReadSyn(uint8* Data);
Std_ReturnType EngineSpeed_ReadSyn(uint8* Data);
#endif /* DIAGHANDLER_H_ */
