/*
 * Dem_EventStatusType.h
 *
 *  Created on: Feb 10, 2021
 *      Author: Mounir
 */

#ifndef RTE_DEM_TYPE_H_
#define RTE_DEM_TYPE_H_
#ifndef Platform_Types
#define Platform_Types
#include "Platform_Types.h"
#endif

/****************configure*************************/
#define MAXNUNBEROFEVENTS DEMEVENTPARAMETER_SIZE
/**************************************************/
typedef uint8 Dem_EventStatusType;
#define DEM_EVENT_STATUS_PASSED                (Dem_EventStatusType)0x00U
#define DEM_EVENT_STATUS_FAILED                (Dem_EventStatusType)0x01U
#define DEM_EVENT_STATUS_PREPASSED             (Dem_EventStatusType)0x02U
#define DEM_EVENT_STATUS_PREFAILED             (Dem_EventStatusType)0x03U
#define DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED (Dem_EventStatusType)0x04U

typedef uint8 Dem_DebounceResetStatusType ;
#define DEM_DEBOUNCE_STATUS_FREEZE  (Dem_DebounceResetStatusType)0x00
#define DEM_DEBOUNCE_STATUS_RESET   (Dem_DebounceResetStatusType)0x01

/********Rte_Dem_Type.h************/
typedef uint8 Dem_DTCFormatType ;
#define  DEM_DTC_FORMAT_OBD   (Dem_DTCFormatType)0
#define  DEM_DTC_FORMAT_UDS   (Dem_DTCFormatType)1
#define  DEM_DTC_FORMAT_J1939 (Dem_DTCFormatType)2


typedef uint16 Dem_EventIdType   ;

typedef uint8 Dem_InitMonitorReasonType;
#define DEM_INIT_MONITOR_CLEAR 			 (Dem_InitMonitorReasonType)0x01
#define DEM_INIT_MONITOR_RESTART	    	 (Dem_InitMonitorReasonType)0x02
#define DEM_INIT_MONITOR_REENABLED	   	 	 (Dem_InitMonitorReasonType)0x03
#define DEM_INIT_MONITOR_STORAGE_REENABLED  (Dem_InitMonitorReasonType)0x04

typedef uint8 Dem_MonitorDataType;

typedef uint8 Dem_EventStatusExtendedType;
//typedef uint16  Dem_EventIdType;



/**----------UDS Bits---------------*/
typedef uint8 Dem_UdsStatusByteType ;
/**testFailed bit of the UDS status byte. Indicates the result of the
most recently performed test*/
#define  DEM_UDS_STATUS_TF      (Dem_UdsStatusByteType)0x01
/**testFailedThisOperationCycle bit of the UDS status byte. Indicates
whether or not a diagnostic test has reported a testFailed
result at any time during the current operation cycle*/
#define  DEM_UDS_STATUS_TFTOC   (Dem_UdsStatusByteType)0x02
/**pendingDTC bit of the UDS status byte. Indicates whether or
not a diagnostic test has reported a testFailed result at any time
during the current or last completed operation cycle*/
#define  DEM_UDS_STATUS_PDTC    (Dem_UdsStatusByteType)0x04
/**confirmedDTC bit of the UDS status byte. Indicates whether a
malfunction was detected enough times to warrant that the DTC
is desired to be stored in long-term memory*/
#define  DEM_UDS_STATUS_CDTC    (Dem_UdsStatusByteType)0x08
/**testNotCompletedSinceLastClear bit of the UDS status byte. Indicates
whether a DTC test has ever run and completed since
the last time a call was made to ClearDiagnosticInformation*/
#define  DEM_UDS_STATUS_TNCSLC  (Dem_UdsStatusByteType)0x10
/**testFailedSinceLastClear bit of the UDS status byte. Indicates
whether a DTC test has completed with a failed result since the
last time a call was made to ClearDiagnosticInformation.*/
#define  DEM_UDS_STATUS_TFSLC   (Dem_UdsStatusByteType)0x20
/**testNotCompletedThisOperationCycle bit of the UDS status byte.
Indicates whether a DTC test has ever run and completed during
the current operation cycle.*/
#define  DEM_UDS_STATUS_TNCTOC  (Dem_UdsStatusByteType)0x40
/**warningIndicatorRequested bit of the UDS status byte. Report
the status of any warning indicators associated with a particular
DTC.*/
#define  DEM_UDS_STATUS_WIR     (Dem_UdsStatusByteType)0x80

typedef uint8 Dem_DTCOriginType ;
/*Event information located in
the primary memory*/
#define DEM_DTC_ORIGIN_PRIMARY_MEMORY       (Dem_DTCOriginType)0x0001
/*Event information located in
the Mirror memory*/
#define DEM_DTC_ORIGIN_MIRROR_MEMORY        (Dem_DTCOriginType)0x0002
/*Event information located in
the mirror memory*/
#define DEM_DTC_ORIGIN_PERMANENT_MEMORY     (Dem_DTCOriginType)0x0003
/*Event information located in
the PERMANENT memory*/
#define DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY  (Dem_DTCOriginType)0x0004
/*Selects all memories which are storing OBD events
(specified by configuration)*/
#define DEM_DTC_ORIGIN_USERDEFINED_MEMORY   (Dem_DTCOriginType)0x0005


typedef uint8 Dem_SelectorStatusType;
/** \brief No DTC selection requested */
#define DEM_DTC_SELECTOR_NO_REQUEST                       0x00U

/** \brief DTC selection requested but not yet processed */
#define DEM_DTC_SELECTOR_NOT_PROCESSED                    0x01U

/** \brief No matching DTC in the requested format and origin found */
#define DEM_DTC_SELECTOR_WRONG_DTC                        0x02U

/** \brief Requested DTC origin does not exist */
#define DEM_DTC_SELECTOR_WRONG_DTC_ORIGIN                 0x03U

/** \brief DTC selection request is for a DTC group */
#define DEM_DTC_SELECTOR_DTC_GROUP                        0x04U

/** \brief Event matching the single DTC selection request found and cached */
#define DEM_DTC_SELECTOR_SINGLE_DTC_EVID_CACHED           0x05U

typedef uint8 Dem_SelectionStatusType;
/** \brief No DTC is selected */
#define DEM_SELECTED_NONE                         0x00U

/** \brief DTC selected */
#define DEM_SELECTED_DTC                          0x01U

/** \brief Wrong DTC format */
#define DEM_SELECTED_CHK_WRONG_DTC                0x02U

/** \brief Wrong DTC Origin */
#define DEM_SELECTED_CHK_WRONG_ORIGIN             0x03U

/** \brief DTC selection check is successful */
#define DEM_SELECTED_CHK_OK                       0x04U

/** \brief Freeze Frame Data selected */
#define DEM_SELECTED_FFD               0x05U

/** \brief Extended Data Record selected */
#define  DEM_SELECTED_EDR              0x06U
#endif /* RTE_DEM_TYPE_H_ */
