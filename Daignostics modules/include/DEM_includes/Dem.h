/*
 * Dem.h
 *
 *  Created on: Feb 7, 2021
 *      Author: Mounir
 */

#ifndef DEM_H_
#define DEM_H_

#include "Dem_Types.h"
#include "Event.h"


typedef struct
{
     DemEventParameter_s *EventParameter;
     DemDTC_s            *Dtc;
     DemEnableConditionGroup_s *EnableConditionGroup;
     DemFreezeFrameClass_s     *FreezeFrameClass    ;
     DemGroupOfDTC_s           *GroupOfDTC;
     DemComponent_s           * Component ;
}Dem_ConfigType;

//TODO
#define DEM_MAX_SIZE_EXT_DATA 4
#define DEM_ACTIVE 0
void Dem_PreInit(void) ; //
void Dem_Init(Dem_ConfigType* ConfigPtr); //
void Dem_Shutdown(void);
void Dem_MainFunction(void);

Std_ReturnType Dem_SetEventStatus(Dem_EventIdType EventId, Dem_EventStatusType EventStatus); //
Std_ReturnType Dem_SetEventAvailable(Dem_EventIdType EventId, boolean AvailableStatus );
Std_ReturnType Dem_GetEventUdsStatus( Dem_EventIdType EventId, Dem_UdsStatusByteType* UDSStatusByte );
Std_ReturnType Dem_ResetEventStatus(Dem_EventIdType EventId); //
Std_ReturnType Dem_ResetEventDebounceStatus(Dem_EventIdType EventId,Dem_DebounceResetStatusType DebounceResetStatus);

Std_ReturnType Dem_ClearDTC( uint8 ClientId ); //
Std_ReturnType Dem_GetDTCSuppression( uint8 ClientId, boolean* SuppressionStatus );
Std_ReturnType Dem_GetFaultDetectionCounter( Dem_EventIdType EventId, sint8* FaultDetectionCounter );
Std_ReturnType Dem_SetEnableCondition( uint8 EnableConditionID, boolean ConditionFulfilled );
Std_ReturnType Dem_GetDTCOfEvent (Dem_EventIdType EventId, Dem_DTCFormatType DTCFormat, uint32* DTCOfEvent);
Std_ReturnType Dem_GetStatusOfDTC(uint8 ClientId , uint8* DTCStatus);
Std_ReturnType Dem_ClearPrestoredFreezeFrame(Dem_EventIdType EventId);
Std_ReturnType Dem_GetDTCStatusAvailabilityMask( uint8 ClientId, Dem_UdsStatusByteType* DTCSt3atusMask );
Std_ReturnType Dem_DisableDTCSetting( uint8 ClientId ) ; //!!
Std_ReturnType Dem_SetOperationCycleState(uint8 operationCycleId, Dem_OperationCycleStateType cycleState);
Std_ReturnType Dem_SelectDTC(uint8 ClientId,uint32 DTC,Dem_DTCFormatType DTCFormat,Dem_DTCOriginType DTCOrigin);
Std_ReturnType Dem_GetFunctionalUnitOfDTC(uint8 ClientId,uint8* DTCFunctionalUnit);
Std_ReturnType Dem_GetSeverityOfDTC(uint8 ClientId,Dem_DTCSeverityType* DTCSeverity);
Std_ReturnType Dem_GetNextFilteredDTC(uint8 ClientId, uint32 *dtc, uint8 *dtcStatus);
Std_ReturnType Dem_GetNumberOfFilteredDtc(uint8 ClientId,uint16 *numberOfFilteredDTC);
Std_ReturnType Dem_SetDTCFilter( uint8 ClientId,uint8 DTCStatusMask,Dem_DTCFormatType DTCFormat,Dem_DTCOriginType DTCOrigin, boolean FilterWithSeverity,Dem_DTCSeverityType DTCSeverityMask, boolean FilterForFaultDetectionCounter);



#endif /* DEM_H_ */
