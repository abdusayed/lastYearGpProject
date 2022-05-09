/*
 * Dem.h
 *
 *  Created on: Feb 7, 2021
 *      Author: Mounir
 */

#ifndef DEM_H_
#define DEM_H_

#include "Dem_Types.h"
/*-------------[defines for event related data records]---------------------*/

#if (defined DEM_ALL_RECORD_NUM)
#error DEM_ALL_RECORD_NUM already defined
#endif
/** \brief Record number to request all freeze frames / extended data records of a selected DTC */
#define DEM_ALL_RECORD_NUM                    0xFFU

#if (defined DEM_FIRST_FF_RECORD_NUM)
#error DEM_FIRST_FF_RECORD_NUM already defined
#endif
/** \brief Starting record number to search for all freeze frame data
 **
 ** If OBDSupport is enabled the starting record number shall be 0x00U
 ** corresponding to OBD FF */
#if (DEM_OBD_Support == STD_ON)
#define DEM_FIRST_FF_RECORD_NUM               0x00U
#else
#define DEM_FIRST_FF_RECORD_NUM               0x01U
#endif

#if (defined DEM_FIRST_ED_RECORD_NUM)
#error DEM_FIRST_ED_RECORD_NUM already defined
#endif
/** \brief Starting record number to search for all extended data records */
#define DEM_FIRST_ED_RECORD_NUM               0x01U

#if (defined DEM_MAX_FF_RECORD_NUM)
#error DEM_MAX_FF_RECORD_NUM already defined
#endif
/** \brief Maximum value for freeze frame record */
#define DEM_MAX_FF_RECORD_NUM                 0xFEU

#if (defined DEM_MAX_ED_RECORD_NUM)
#error DEM_MAX_ED_RECORD_NUM already defined
#endif
/** \brief Maximum value for extended data record */
#define DEM_MAX_ED_RECORD_NUM                 0xEFU

#if (defined DEM_END_OF_RECORD_SEARCH)
#error DEM_END_OF_RECORD_SEARCH already defined
#endif
/** \brief End of valid record number search */
#define DEM_END_OF_RECORD_SEARCH              0xFFU

#if (defined DEM_OBD_FF_RECORD_NUM)
#error DEM_OBD_FF_RECORD_NUM already defined
#endif
/** \brief Used in functions for selecting the OBD FF */
#define DEM_OBD_FF_RECORD_NUM                 0x00U
/*---------------------[defines for extended data record]-------------------*/
#if (defined DEM_UNSUPPORTED_OBD_EDR)
#error DEM_UNSUPPORTED_OBD_EDR already defined
#endif
/** \brief Extended data record number not supported by configuration */
#define DEM_UNSUPPORTED_OBD_EDR               0x00U

#if (defined DEM_ALL_OBD_EDR)
#error DEM_ALL_OBD_EDR already defined
#endif
/** \brief Record number to request all OBD extended data records of a selected DTC */
#define DEM_ALL_OBD_EDR                       0xFEU

#if (defined DEM_FIRST_OBD_EDR)
#error DEM_FIRST_OBD_EDR already defined
#endif
/** \brief Starting record number to search for OBD related extended data record */
#define DEM_FIRST_OBD_EDR                     0x90U

#define DEM_IS_UNMASKED_BIT_SET(Byte, Mask) \
  (((Byte) & (uint8)(~((uint8)(Mask)))) != 0U)

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


#endif /* DEM_H_ */
