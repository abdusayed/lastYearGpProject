/*
 * Dem_Stc.h
 *
 *  Created on: Mar 24, 2021
 *      Author: Mounir
 */
#ifndef DEM_STC_H_
#define DEM_STC_H_
#include"Rte_Dem_Type.h"
#ifndef Platform_Types
#define Platform_Types
#include "Platform_Types.h"
#endif

typedef struct
{
    uint16 EventId ;
    Dem_EventStatusType Status ;
}Dem_ErrorQueueEntryType;
/** This type is used as index type for the error-queue
 **
 ** Its size (uint8) is given by configuration. */
typedef uint8 Dem_ErrorQueueIdxType;

/*-------------------Event ID-----------------*/
/** Symbolic name of invalid event ID */
#define DEM_EVENT_ID_INVALID 0U
/** Symbolic name of event ID that must be ignored during processing
 ** of the queue since it got invalidated */
#define DEM_EVENT_ID_IGNORE  0x1FFFU

/*--------------------Error IDs------------------*/

/** DET error code for invalid configuration */
#define DEM_E_PARAM_CONFIG    0x10U
/** DET error code for AR 4.3 in case an API function is called with
 **  a parameter value, which is not allowed by active configuration */
#define DEM_E_WRONG_CONFIGURATION  0x10U
/** DET error code for invalid address */
#define DEM_E_PARAM_POINTER   0x11U
/** DET error code for invalid data */
#define DEM_E_PARAM_DATA      0x12U
/** DET error code for invalid length */
#define DEM_E_PARAM_LENGTH    0x13U
/** DET error code for wrong initialization status */
#define DEM_E_UNINIT          0x20U
/** DET error code for unfulfilled return values from an SW-C */
#define DEM_E_INTEGRATION     0x41U
/** DET error code for unfulfilled pre-conditions for an API call */
#define DEM_E_WRONG_CONDITION 0x40U
/** DET error code for wrong call-context in multi-core case */
#define DEM_E_WRONG_CONTEXT   0x42U
/** DET error code for AR 4.3 in case Dem initialization fails */
#define DEM_E_INIT_FAILED  0x14U
/** DET error code for AR 4.3 in case Dem_DcmGetAvailableOBDMIDs is
 ** called with invalid OBDMID */
#define DEM_E_INVALID_OBDMID  0x50U

typedef struct
{
  uint32                  DTC;                 /**< Single DTC or DTC group */
  Dem_EventIdType         EventId;
            /**< Id of the first event, matching the DTC selection criteria */
  Dem_DTCOriginType       DTCOrigin;           /**< Event memory of the DTC */
  Dem_DTCFormatType       DTCFormat;                 /**< Format of the DTC */
  uint8                   RecordNumber;
                           /**< Record number selected to access event data */
  uint8                   NextRecNum;
} Dem_DTCInfoType;

typedef struct
{
  Dem_DTCInfoType        DTCInfo;
                           /**< DTC selection criteria and matching eventId */
  Dem_SelectorStatusType SelectorStatus;
                         /**< Current status/result of the DTC selection operation - for RFM */
  Dem_SelectionStatusType SelectionStatus;
                  /**< Prototype Selection mechanism */
} Dem_DTCSelectionType;

typedef struct
{
    /** next EventId to be cleared */
    Dem_EventIdType NextEventId;
    /** \brief Global ClearDTC run state */
    uint8 RunState;
    /** Event status/data modified flag */
    boolean AnyEventModified;
    /** Unique ClientId of the caller */
    uint8 ClientId;
    /** Result of the clearing operation */
    Std_ReturnType OperationResult;

}Dem_ClearDtcStatusType;

#endif /* DEM_STC_H_ */
