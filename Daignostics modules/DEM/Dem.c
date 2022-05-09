#include "Dem.h"
#include "Dem_Cfg.h"
#include "Dem_LCfg.h"
#include "Dem_Stc.h"



//  ------------- SW-C or other BSW modules -------------/
// --------------The Dem module provides a configuration table to combine event related data (freeze
//frames & extended data) with a specific DTC number, etc. (refer to chapter 7.7.7.4).


typedef uint8 ModuleState ;
#define MODULE_INTAILIZED    (ModuleState)0
#define MODULE_UN_INTAILIZED (ModuleState)1
#define MODULE_PREINTAILIZED    (ModuleState)2
#define MODULE_UN_PREINTAILIZED (ModuleState)3


#define DEM_NO_DTC 0
#define STD_ON (1U)

typedef uint8 Dem_DebounceAlgoNameType;
//#define   DEM_NO_DEBOUNCE                  (Dem_DebounceAlgoNameType)0 // monitor
#define DEM_DEBOUNCE_COUNTER_BASED             (Dem_DebounceAlgoNameType)1
#define DEM_DEBOUNCE_MONITORINTERNAL_BASED     (Dem_DebounceAlgoNameType)2
#define DEM_DEBOUNCE_TIME_BASED                (Dem_DebounceAlgoNameType)3

#define DEM_CONFIRMATION_CNTR_MAX (uint8)255
#define DEM_CLIENT_ID_INVALID -1

/*------------------[defines for ClearDtc]----------------------------------*/

/** Run state value of an async. ClearDtc process: Not running, IDLE */
#define DEM_CLEARDTC_STATE_IDLE 0U
/** Run state value of an async. ClearDtc process: Running, PROCESSING_RAM */
#define DEM_CLEARDTC_STATE_PROCESSING_RAM 1U
/** Run state value of an async. ClearDtc process: Running, PROCESSING_NVRAM */
#define DEM_CLEARDTC_STATE_PROCESSING_NVRAM 2U
/** Run state value of an async. ClearDtc process: Done with PROCESSING_NVRAM, FAILED */
#define DEM_CLEARDTC_STATE_FAILED 3U
/** Run state value of an async. ClearDtc process: Done with PROCESSING_NVRAM, FINISHED */
#define DEM_CLEARDTC_STATE_FINISHED 4U

//TODO
extern DemEventParameter_s DemEventParameter[DEMEVENTPARAMETER_SIZE];
extern DemDebounceAlgorithmClass_s DemDebounceAlgorithmClass[5];//TODO
extern DemDebounceCounterBasedClass_s DemDebounceCounterBasedClass[5];
extern DemClient_s DemClient[DEMCLIENT_SIZE] ;
DemCallbackEventDataChanged_s DemCallbackEventDataChanged[5];

//TODO adging block id used in NVM
uint16 BlockId;
DemCallbackInitMForEFnc_s DemCallbackInitMForE[5];

// DtcFilterType
typedef struct {
    Dem_EventStatusExtendedType dtcStatusMask;
    Dem_DTCKindType             dtcKind;
    Dem_DTCOriginType           dtcOrigin;
    Dem_DTCFormatType           DTCFormat;                          /**< output-format of DTC */
    Dem_FilterWithSeverityType  filterWithSeverity;
    Dem_DTCSeverityType         dtcSeverityMask;
    Dem_FilterForFDCType        filterForFaultDetectionCounter;
    uint16                      faultIndex;
} DtcFilterType;

/*
 * Allocation of DTC filter parameters
 */
static DtcFilterType dtcFilter;



typedef struct
{
    Dem_EventIdType eventId;
    DemEventParameter_s * EventParamterRef ;
    sint8  faultDetectionCounter;
    sint8  maxFaultDetectionCounter;
    sint16 occurrence;
    boolean errorStatusChanged;
    uint8 confirmationCounter;
    Dem_UdsStatusByteType eventStatus;
}EventStatusRecType;

// DisableDtcStorageType
typedef struct {
    boolean                     storageDisabled;
    Dem_DTCGroupType            dtcGroup;
    Dem_DTCKindType             dtcKind;
} DisableDtcStorageType;

// Types for storing different event data on event memory
typedef struct {
    Dem_EventIdType             eventId;
    uint16                      occurrence;
    Dem_UdsStatusByteType       eventStatus;
    uint8                       confirmationCounter;
    uint16                checksum;
} EventRecType;

typedef uint16 ChecksumType;
//TODO configration
typedef struct {
    Dem_EventIdType         eventId;
    Dem_FreezeFrameKindType kind;
    uint16                  occurrence;
    uint16                  dataSize;
    uint8                   recordNumber;
    uint32                  timeStamp;
    uint8                   data[DEMMAXNUMBERPRESTOREDFF];
    ChecksumType            checksum;
} FreezeFrameRecType;

typedef struct {
    Dem_EventIdType     eventId;
    uint8               data[DEM_MAX_SIZE_EXT_DATA];
    ChecksumType        checksum;
} ExtDataRecType;

// Types for storing different event aging counter
typedef struct {
    Dem_EventIdType     eventId;
    uint8               agingCounter;/** @req Dem019 */
    ChecksumType        checksum;
} HealingRecType;

/*
 * TRUE:    priMemAgingBuffer changed,
 * FALSE:   priMemAgingBuffer not changed
 */
static boolean AgingIsModified = FALSE;

uint8 Monitor_Status[MAXNUNBEROFEVENTS];
extern DemEnableConditionGroup_s DemEnableConditionGroup[DEMENABLECONDITIONGROUP_SIZE];


ModuleState Dem_ModuleState = MODULE_UN_INTAILIZED;

/*
 * Allocation of local event status buffer
 */
static EventStatusRecType   eventStatusBuffer[MAXNUNBEROFEVENTS];

/*
 * Allocation of operation cycle state list
 */
static Dem_OperationCycleStateType operationCycleStateList[DEMOPERATIONCYCLE_SIZE];
/*
 * contains the Events status buffer
 * */
Dem_MonitorStatusType MonitorStatusBuffer[MAXNUNBEROFEVENTS];
/*
 * Allocation of Disable/Enable DTC storage parameters
 */
static DisableDtcStorageType disableDtcStorage;

/*
 * Allocation of primary event memory ramlog (after init) in uninitialized memory
 */
//TODO
#define DemMaxNumberEventEntryPrimary MAXNUNBEROFEVENTS

Dem_ClearDtcStatusType Dem_ClearDtcStatus ;

EventRecType                priMemEventBuffer[DemMaxNumberEventEntryPrimary]; //has to be #define

HealingRecType              priMemAgingBuffer[MAXNUNBEROFEVENTS];
//DemAvailabilitySupport_Enum DemAvailabilitySupport_obj ;

Dem_DTCSelectionType Dem_DTCSelection[DEMCLIENT_SIZE] ;
/*
 * Allocation of pre-init event memory (used between pre-init and init)
 */
static FreezeFrameRecType   preInitFreezeFrameBuffer[DEMMAXNUMBERPRESTOREDFF];
/*
 * Allocation of primary event memory ramlog (after init) in uninitialized memory
 */
/** @req DEM162 */
static FreezeFrameRecType   priMemFreezeFrameBuffer[DEMMAXNUMBERPRESTOREDFF];
/*
 * Allocation of operation cycle state list
 */
static Dem_OperationCycleStateType operationCycleStateList[DEMOPERATIONCYCLE_SIZE];

ExtDataRecType      priMemExtDataBuffer[ DEME3TENDEDDATACLASS_SIZE];

/** Queue holding the errors appeared before Dem_Init(), or to be
 ** entered or updated in event memory after Dem_Init()
 */
#define DEM_BSW_ERROR_BUFFER_SIZE DEMBSWERRORBUFFERSIZE

Dem_ErrorQueueEntryType Dem_ErrorQueue[ DEM_BSW_ERROR_BUFFER_SIZE ];

/** Index of first entry in queue to read */
static Dem_ErrorQueueEntryType Dem_ErrorQueueReadIdx;

/** Index of next entry in queue to write */
static Dem_ErrorQueueEntryType Dem_ErrorQueueWriteIdx;


/***************memset*********************/
static void *memset (void *dest, uint16 val, uint16 len)
{
  uint8 *ptr = dest;
  while (len-- > 0)
  {
    *ptr++ = val;
  }
  return dest;
}
/********************************************************************************************/
/* Service name:                                                                            */
/* Parameters (in):                                                                         */
/* Parameters (inout):                                                                      */
/* Parameters (out):                                                                        */
/* Description:                                                                             */
/********************************************************************************************/
Std_ReturnType Dem_ResetEventDebounceStatus(Dem_EventIdType EventId, Dem_DebounceResetStatusType DebounceResetStatus)
{

}

/****************************************************************************/
/* Procedure:   checkDtcGroup                                               */
/* Description: Return TRUE if "dtc" match the events DTC or "dtc" is       */
/*              "DEM_DTC_GROUP_ALL_DTCS" otherwise FALSE.                   */
/****************************************************************************/
static boolean checkDtcGroup(uint32 dtc, const DemEventParameter_s *eventParam)
{
    boolean result = FALSE;

    if (dtc == DEM_DTC_GROUP_ALL_DTCS) {
        result = TRUE;
    }
    else {
        if (eventParam->DemDTCRef_ptr != NULL)
        {
            if (eventParam->DemDTCRef_ptr->DemDtcValue == dtc) {
                result = TRUE;
            }
        }
    }
    return result;
}

/********************************************************************************************/
/* Service name:      checkEventIdExist                                                     */
/* Parameters (in):   EventId                                                               */
/* Parameters (inout):EventIdParam                                                          */
/* Parameters (out):  EventIdParam                                                          */
/* Description:       Returns the pointer to event id parameters of "eventId" in            */
/*                    "*eventIdParam" if not found NULL is returned.                        */
/********************************************************************************************/
static void checkEventIdExist(Dem_EventIdType EventId ,DemEventParameter_s **EventIdParam )
{
    uint16 i = 0 ;
    boolean EventIdFound = FALSE ;
    /* Lookup the correct event id parameters */
    for( i = 0 ; (i <MAXNUNBEROFEVENTS) && (EventIdFound == FALSE) ; i++ )
    {
        if(eventStatusBuffer[i].eventId == EventId)
        {
            EventIdFound =TRUE;
        }
    }
    if(EventIdFound == TRUE)
    {
        *EventIdParam = eventStatusBuffer[i-1].EventParamterRef ;
    }
    else
    {
        *EventIdParam = NULL;
    }
}

/************************************************************************************************/
/* Procedure:   lookupEventStatusRec                                                            */
/* Description: Returns the pointer to event id parameters of "eventId" in "*eventStatusBuffer",*/
/*              if not found NULL is returned.                                                  */
/************************************************************************************************/
static void lookupEventStatusRec(Dem_EventIdType eventId, EventStatusRecType **const eventStatusRec)
{
    uint8 i;
    boolean eventIdFound = FALSE;

    for (i = 0; (i < MAXNUNBEROFEVENTS) && (eventIdFound == FALSE); i++)
    {
        if(eventStatusBuffer[i].eventId == eventId)
        {
            eventIdFound = TRUE;
        }
    }
    if (eventIdFound == TRUE)
    {
        *eventStatusRec = &eventStatusBuffer[i-1];
    }
    else
    {
        *eventStatusRec = NULL;
    }
}
/********************************************************************************************/
/* Service name:  Dem_getDebounceAlgoNameType                                               */
/* Parameters (in):   EventId                                                               */
/* Parameters (inout):                                                                      */
/* Parameters (out):                                                                        */
/* Description:                                                                             */
/********************************************************************************************/
static Dem_DebounceAlgoNameType Dem_getDebounceAlgoNameType (Dem_EventIdType EventId)
{

    EventStatusRecType *EventIdParam ;
    lookupEventStatusRec(EventId, &EventIdParam) ;
    uint8 DBname ;

    if(EventIdParam != NULL)
    {
        switch(eventStatusBuffer[EventId-1].EventParamterRef->DemDebounceAlgorithmClass_type)
        {
        case DEMDEBOUNCECOUNTERBASED_CONTAINER_TYPE:
            DBname = DEM_DEBOUNCE_COUNTER_BASED;
            break;
        case DEMDEBOUNCETIMEBASECLASS_REFERENCE_TYPE:
            DBname = DEM_DEBOUNCE_TIME_BASED ;
            break;
        case DEMDEBOUNCEMONITORINTERNAL_CONTAINER_TYPE :
            DBname = DEM_DEBOUNCE_MONITORINTERNAL_BASED;
            break;
        default:
            break;
        }

    }
    else
    {

        // error
    }
    return DBname ;
}
/*################################# */
sint8 MAX(sint8 num1, sint8 num2)
{
    return (num1 > num2 ) ? num1 : num2;
}
/*################################# */
/********************************************************************************************/
/* Service name:      DebounceCounterBased                                                  */
/* Parameters (in):   reportedStatus ,  statusRecord                                        */
/* Parameters (inout):                                                                      */
/* Parameters (out):  Dem_EventStatusType                                                   */
/* Description:       Returns the result of the debouncing                                  */
/********************************************************************************************/

static Dem_EventStatusType DebounceCounterBased(Dem_EventStatusType reportedStatus, EventStatusRecType* statusRecord)
{
    Dem_EventStatusType return_status ;
   /*DemDebounceAlgorithmClass tool bug*/
    const DemDebounceCounterBasedClass_s *CBRef = DemDebounceAlgorithmClass[statusRecord->EventParamterRef \
                                                                     ->DemDebounceAlgorithmClass_startingIndex].DebounceAlgorithm.DemDebounceCounterBasedClassRef_ptr;
    switch (reportedStatus)
    {
    case DEM_EVENT_STATUS_PREFAILED:
        /* check if the counter is less than the counterFailedThreshold sint8 --- uint16#####*/
        if( (statusRecord->faultDetectionCounter) < (CBRef->DemDebounceCounterFailedThreshold) )
        {
            /*check if the JumpDown  is active and if the faultDetectionCounter is less than the jumpUp value --[SWS_Dem_00425]--*/
            if( ( CBRef->DemDebounceCounterJumpDown == TRUE)  && (sint16)(statusRecord->faultDetectionCounter) < (CBRef->DemDebounceCounterJumpUpValue))
            {
                /*----[SWS_Dem_00425]----*/
                (statusRecord->faultDetectionCounter) = (CBRef->DemDebounceCounterJumpUpValue) ;
            }
            else
            {
                /*increment the faultDetectionCounter by InStepStize and check if it reached the Thershold */
                if( ((sint16)(statusRecord->faultDetectionCounter) +(CBRef->DemDebounceCounterIncrementStepSize)) < (CBRef->DemDebounceCounterFailedThreshold))
                {
                    /*if it didn't reach the Threshold value Increment the faultDetectionCounter*/
                    statusRecord->faultDetectionCounter += (sint8)CBRef->DemDebounceCounterIncrementStepSize ;
                }
                else
                {
                    /*if it reached the Threshold value save Threshold value in the counter----[SWS_Dem_00416]----*/
                    statusRecord->faultDetectionCounter = (sint8)CBRef->DemDebounceCounterFailedThreshold ;
                }
            }
        }

    break;
    case DEM_EVENT_STATUS_PREPASSED:
        /* check if the counter is less than the counterFailedThreshold sint8 --- uint16#####*/
        if( (statusRecord->faultDetectionCounter) > (CBRef->DemDebounceCounterPassedThreshold) )
        {
            /*check if the JumpDown  is active and if the faultDetectionCounter is less than the jumpUp value --[SWS_Dem_00425]--*/
            if( ( CBRef->DemDebounceCounterJumpDown == TRUE)  && (sint16)(statusRecord->faultDetectionCounter) > (CBRef->DemDebounceCounterJumpDownValue))
            {
                /*----[SWS_Dem_00423]----*/
                (statusRecord->faultDetectionCounter) = (CBRef->DemDebounceCounterJumpDownValue) ;
            }
            else
            {
                /*increment the faultDetectionCounter by InStepStize and check if it reached the Thershold */
                if( ((sint16)(statusRecord->faultDetectionCounter) - (CBRef->DemDebounceCounterDecrementStepSize)) > (CBRef->DemDebounceCounterPassedThreshold))
                {
                    /*if it didn't reach the Threshold value Increment the faultDetectionCounter*/
                    statusRecord->faultDetectionCounter -= (sint8)CBRef->DemDebounceCounterDecrementStepSize ;
                }
                else
                {
                    /*if it reached the Threshold value save Threshold value in the counter----[SWS_Dem_00416]----*/
                    statusRecord->faultDetectionCounter = (sint8)CBRef->DemDebounceCounterPassedThreshold ;
                }
            }
        }

    break;
    case DEM_EVENT_STATUS_FAILED:
        statusRecord->faultDetectionCounter = (sint8)CBRef->DemDebounceCounterFailedThreshold ;

    break;
    case DEM_EVENT_STATUS_PASSED:
        statusRecord->faultDetectionCounter = (sint8)CBRef->DemDebounceCounterPassedThreshold ;

    break;
    default:
        //Report an error
        //DET_REPORTERROR(MODULE_ID_DEM, 0, DEM_PREDEBOUNCE_COUNTER_BASED_ID, DEM_E_PARAM_DATA);
    break;
    }
    /*Save the processed status of the event*/
    sint16 CFThreshold  = (sint8)CBRef->DemDebounceCounterFailedThreshold;
    sint16 CPThreshold  = (sint8)CBRef->DemDebounceCounterPassedThreshold;
    if(statusRecord->faultDetectionCounter == CFThreshold)
    {
        return_status = DEM_EVENT_STATUS_FAILED ;
    }
    else if(statusRecord->faultDetectionCounter == CPThreshold)
    {
        return_status = DEM_EVENT_STATUS_PASSED;
    }
    else
    {
        return_status = reportedStatus;
    }
    statusRecord->maxFaultDetectionCounter = MAX(statusRecord->maxFaultDetectionCounter , statusRecord->faultDetectionCounter);
    return return_status;
}



static void handleFaultConfirmation(const DemEventParameter_s *eventParam, EventStatusRecType *eventStatusRecPtr)
{
    if( eventStatusRecPtr->confirmationCounter < DEM_CONFIRMATION_CNTR_MAX )
    {
        eventStatusRecPtr->confirmationCounter++;
    }
    if( eventStatusRecPtr->confirmationCounter >= eventParam->DemEventConfirmationThreshold )
    {
        //confirmedDTC
        eventStatusRecPtr->eventStatus |= DEM_UDS_STATUS_CDTC;
    }
}
/********************************************************************************************/
/* Service name:          updateEventStatusRec                                              */
/* Parameters (in):       eventParam , eventParam , createIfNotExist , eventStatusRec       */
/* Parameters (inout):                                                                      */
/* Parameters (out):                                                                        */
/* Description:  Update the status of "eventId", if not exist and "createIfNotExist" is     */
/*               true a new record is created                                               */
/********************************************************************************************/
static void updateEventStatusRec(uint16 EventId, Dem_EventStatusType eventStatus, boolean createIfNotExist, EventStatusRecType *eventStatusRec)
{
    EventStatusRecType *eventStatusRecPtr;
    sint8 faultCounterBeforeDebounce = 0;
    sint8 faultCounterAfterDebounce = 0;

    lookupEventStatusRec(EventId, &eventStatusRecPtr);

    if((eventStatusRecPtr == NULL) && (createIfNotExist == TRUE))
    {
        lookupEventStatusRec(DEMEVENTPARAMETER_ID_0, &eventStatusRec);
        if( eventStatusRecPtr!= NULL )
        {
            eventStatusRecPtr->eventId                  = EventId ;
            eventStatusRecPtr->EventParamterRef         = &DemEventParameter[EventId] ;
            eventStatusRecPtr->faultDetectionCounter    = 0 ;
            eventStatusRecPtr->maxFaultDetectionCounter = 0 ;
            eventStatusRecPtr->occurrence               = 0 ;
            eventStatusRecPtr->errorStatusChanged       = FALSE;
            eventStatusRecPtr->confirmationCounter      = 0 ;
            eventStatusRecPtr->eventStatus              = DEM_UDS_STATUS_TNCSLC | DEM_UDS_STATUS_TNCTOC ;
        }
        else
        {
            //Error
            //DET_REPORTERROR(MODULE_ID_DEM, 0, DEM_UPDATE_EVENT_STATUS_ID, DEM_E_EVENT_STATUS_BUFF_FULL);
        }
    }
    else if( eventStatusRecPtr != NULL)
    {
        //GET the faultDetection counter of the event
        faultCounterBeforeDebounce = eventStatusBuffer[EventId-1].faultDetectionCounter;
        uint8 Result;
        Result = Dem_getDebounceAlgoNameType(eventStatusBuffer[EventId-1].eventId );

        if(Result == DEM_DEBOUNCE_COUNTER_BASED )
        {
            eventStatus = DebounceCounterBased(eventStatus ,&eventStatusBuffer[EventId-1]);
        }
        else if(Result == DEM_DEBOUNCE_TIME_BASED)
        {
            //TimeBase
        }
        else
        {
            //DET_REPORTERROR(MODULE_ID_DEM, 0, DEM_UPDATE_EVENT_STATUS_ID, DEM_E_NOT_IMPLEMENTED_YET);
        }

        faultCounterAfterDebounce = eventStatusBuffer[EventId-1].faultDetectionCounter;
        eventStatusBuffer[EventId-1].errorStatusChanged = FALSE;

        if (eventStatus == DEM_EVENT_STATUS_FAILED)
        {
            if ((eventStatusBuffer[EventId-1].eventStatus & DEM_UDS_STATUS_TF) == 0)
            {
                eventStatusBuffer[EventId-1].errorStatusChanged = TRUE;
                if((eventStatusBuffer[EventId-1].eventStatus & DEM_UDS_STATUS_TFTOC) == 0 )
                {
                        /* First fail this operation cycle */
                        /*[SWS_Dem_CONSTR_06122]*/
                        handleFaultConfirmation(&eventStatusBuffer[EventId-1], eventStatusRecPtr);
                        if( (eventStatusBuffer[EventId-1].eventStatus | DEM_UDS_STATUS_CDTC) != 0  )
                        {
                            eventStatusBuffer[EventId-1].occurrence++;
                        }
                }
                                         /*--------------Figure 7.21----------------*/
                eventStatusBuffer[EventId-1].eventStatus |= (DEM_UDS_STATUS_TF | DEM_UDS_STATUS_TFTOC | DEM_UDS_STATUS_TFSLC );
                eventStatusBuffer[EventId-1].eventStatus &= (Dem_UdsStatusByteType)~(DEM_UDS_STATUS_TNCSLC | DEM_UDS_STATUS_TNCTOC);
            }

        }
        if (eventStatus == DEM_EVENT_STATUS_PASSED)
        {
            if (eventStatusBuffer[EventId-1].eventStatus & (DEM_UDS_STATUS_TF | DEM_UDS_STATUS_TNCTOC))
            {
                  eventStatusBuffer[EventId-1].errorStatusChanged = TRUE;
                  eventStatusBuffer[EventId-1].eventStatus &= ~DEM_UDS_STATUS_TF;
                  eventStatusBuffer[EventId-1].eventStatus &= ~(DEM_UDS_STATUS_TNCSLC | DEM_UDS_STATUS_TNCTOC);
                  /* (DemCallbackEventDataChanged[eventStatusRecPtr->EventParamterRef->DemCallbackEventUdsStatusChanged_startingIndex]\
                           .DemCallbackEventDataChangedFnc)(EventId);
                   */

            }


        }
        if ((eventStatus == DEM_EVENT_STATUS_PREFAILED)\
                    && (faultCounterBeforeDebounce <= 0) && (faultCounterAfterDebounce > 0))
        {
            eventStatusBuffer[EventId-1].errorStatusChanged = TRUE;
        }
        memcpy(eventStatusRec, eventStatusRecPtr, sizeof(EventStatusRecType));

    }
    else
    {
        eventStatusBuffer[EventId-1].eventId =DEMEVENTPARAMETER_ID_0;
        eventStatusBuffer[EventId-1].faultDetectionCounter = 0;
        eventStatusBuffer[EventId-1].maxFaultDetectionCounter = 0;
        eventStatusBuffer[EventId-1].occurrence = 0;
        eventStatusBuffer[EventId-1].eventStatus = DEM_UDS_STATUS_TNCTOC | DEM_UDS_STATUS_TNCSLC;
        eventStatusBuffer[EventId-1].errorStatusChanged = FALSE;
        eventStatusBuffer[EventId-1].confirmationCounter = 0;

   }
}

/*********************************************************************************************/
/* Procedure:   storeEventPriMem                                                             */
/* Description: Store the event data of "eventStatus->eventId" in "priMemEventBuffer",       */
/*              if non existent a new entry is created.                                      */
/*********************************************************************************************/
static void storeEventPriMem(const DemEventParameter_s *eventParam, const EventStatusRecType *eventStatus)
{
    boolean eventIdFound = FALSE;
    boolean eventIdFreePositionFound=FALSE;
    uint16 i;

    // Lookup event ID
    for (i = 0; (i < DemMaxNumberEventEntryPrimary) && (eventIdFound == FALSE); i++)
    {
        if(priMemEventBuffer[i].eventId == eventStatus->eventId)
        {
            eventIdFound = TRUE ;
        }
    }
    if (eventIdFound != FALSE) {
        // Update event found
        priMemEventBuffer[i-1].occurrence = eventStatus->occurrence;
        priMemEventBuffer[i-1].eventStatus = eventStatus->eventStatus;
        priMemEventBuffer[i-1].confirmationCounter = eventStatus->confirmationCounter;
    }
    else
    {
        for (i=0; (i < DemMaxNumberEventEntryPrimary) && (eventIdFreePositionFound == FALSE); i++)
        {
            /* in init function has to init it to NULL */
            /* Search for Free space */
            if(priMemEventBuffer[i].eventId == DEMEVENTPARAMETER_ID_0)
            {
                eventIdFreePositionFound =TRUE ;
            }

        }
        if (eventIdFreePositionFound == TRUE)
        {
            priMemEventBuffer[i-1].eventId = eventStatus->eventId;
            priMemEventBuffer[i-1].occurrence = eventStatus->occurrence;
            priMemEventBuffer[i-1].eventStatus = eventStatus->eventStatus;
            priMemEventBuffer[i-1].confirmationCounter = eventStatus->confirmationCounter;
        }
        else
        {
            //error
            //DET_REPORTERROR(MODULE_ID_DEM, 0, DEM_STORE_EVENT_PRI_MEM_ID, DEM_E_PRI_MEM_EVENT_BUFF_FULL)
        }
    }
}
/************************************************************************************************/
/* Procedure:   storeEventEvtMem                                                                */
/* Description: Store the event data of "eventStatus->eventId" in event memory according to     */
/*              "eventParam" destination option.                                                */
/************************************************************************************************/
static void storeEventEvtMem( DemEventParameter_s *eventParam, EventStatusRecType *eventStatus)
{
        switch (eventParam->DemDTCRef_ptr->DemDTCAttributesRef_ptr->DemMemoryDestinationRef_type)
        {
        /*-------[SWS_Dem_00934]---*/
        case DEMPRIMARYMEMORY_REFERENCE_TYPE:
            storeEventPriMem(eventParam, eventStatus);
        break;

        case DEMUSERDEFINEDMEMORY_REFERENCE_TYPE:
        case DEMMIRRORMEMORY_REFERENCE_TYPE:
        break;
        default:
        break;
        }
        if(eventParam->DemDTCRef_ptr == NULL)
        {
            storeEventPriMem(eventParam, eventStatus);

        }
}

/************************************************************************************************/
/* Procedure:   getEventStatusRec                                                               */
/* Description: Returns the status record of "eventId" in "eventStatusRec"                      */
/************************************************************************************************/
static void getEventStatusRec(Dem_EventIdType eventId, EventStatusRecType *eventStatusRec)
{
    EventStatusRecType *eventStatusRecPtr;

    // Lookup event ID
    lookupEventStatusRec(eventId, &eventStatusRecPtr);

    if (eventStatusRecPtr != NULL)
    {
        // Copy the record
        memcpy(eventStatusRec, eventStatusRecPtr, sizeof(EventStatusRecType));
    }
    else {
        eventStatusRec->eventId = DEMEVENTPARAMETER_ID_0;
    }
}

/**********************************************************************************************/
/* Procedure:   checkDtcOrigin                                                                */
/* Description: Return TRUE if "dtcOrigin" match any of the events DTCOrigin otherwise FALSE. */
/**********************************************************************************************/
static void checkDtc(uint8 ClientId)
{
    Dem_SelectorStatusType NewSelectorStatus = Dem_DTCSelection[ClientId].SelectorStatus;
    /* extract DTC related information of client to local variables */
    const uint32            DTC       = Dem_DTCSelection[ClientId].DTCInfo.DTC;
    const Dem_DTCFormatType DTCFormat = Dem_DTCSelection[ClientId].DTCInfo.DTCFormat;
    const Dem_DTCOriginType DTCOrigin = Dem_DTCSelection[ClientId].DTCInfo.DTCOrigin;

    if ((DTCFormat != DEM_DTC_FORMAT_OBD) && (DTCFormat != DEM_DTC_FORMAT_UDS) )
    {
          NewSelectorStatus = DEM_DTC_SELECTOR_WRONG_DTC;

    }
    else if ((DTCOrigin != DEM_DTC_ORIGIN_PRIMARY_MEMORY)   &&
             (DTCOrigin != DEM_DTC_ORIGIN_MIRROR_MEMORY)    &&
             (DTCOrigin != DEM_DTC_ORIGIN_PERMANENT_MEMORY) &&
             (DTCOrigin != DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY) )
     {
          NewSelectorStatus = DEM_DTC_SELECTOR_WRONG_DTC_ORIGIN;
     }
    /* check the DTC value */
    else if( DTC > 0xFFFFFFU)
    {
         NewSelectorStatus  = DEM_DTC_SELECTOR_WRONG_DTC;
    }
#if (DEM_OBD_Support == STD_ON)
    else if (DTCFormat == DEM_DTC_FORMAT_OBD)
    {
      /* selection of a single DTC in OBD format is not supported by any
       * dependent APIs of Dem_SelectDTC() */
      NewSelectorStatus = DEM_DTC_SELECTOR_WRONG_DTC;
    }
#endif
    Dem_DTCSelection[ClientId].SelectorStatus = NewSelectorStatus ;
}

/************************************************************************************************/
/* Procedure:   Dem_GetEventAvailable                                                           */
/* Description: check if the event is available                                                 */
/************************************************************************************************/
static boolean Dem_GetEventAvailable (Dem_EventIdType EventId)
{
    boolean Result = FALSE ;
    DemEventParameter_s *EventIdParam ;
    checkEventIdExist( EventId ,&EventIdParam );
    if(EventIdParam != NULL)
    {
        if (EventIdParam->DemEventAvailable == TRUE)
        {
            Result = TRUE ;
        }
        else
        {
            Result = FALSE;
        }
    }
    return Result ;
}
/*******************************************************************************************/
/* Procedure:   storeFreezeFrameDataPriMem                                                 */
/* Description: store FreezeFrame data record in primary memory                            */
/*******************************************************************************************/
static void storeFreezeFrameDataPriMem(const DemEventParameter_s *eventParam, const FreezeFrameRecType *freezeFrame)
{
    boolean eventIdFound = FALSE;
    boolean eventIdFreePositionFound=FALSE;
    boolean displacementPositionFound=FALSE;
    FreezeFrameRecType *freezeFrameLocal;
    uint16 i;

    /* Check if already stored */
    for (i = 0; (i<DEMPRIMARYMEMORY_SIZE) && (eventIdFound == FALSE); i++){
        if((priMemFreezeFrameBuffer[i].eventId == eventParam->DemEventKind) && (priMemFreezeFrameBuffer[i].recordNumber == freezeFrame->recordNumber))
        {
            eventIdFound = TRUE ;

        }
    }
    if (eventIdFound == TRUE) {
        memcpy(&priMemFreezeFrameBuffer[i-1], freezeFrame, sizeof(FreezeFrameRecType));
    }
        else {
            for (i = 0; (i < DEMPRIMARYMEMORY_SIZE) && (eventIdFreePositionFound == FALSE); i++){
                if(priMemFreezeFrameBuffer[i].eventId == DEMEVENTPARAMETER_ID_0)
                {
                    eventIdFreePositionFound = TRUE;
                }
            }
            if (eventIdFreePositionFound == TRUE) {
                memcpy(&priMemFreezeFrameBuffer[i-1], freezeFrame, sizeof(FreezeFrameRecType));
            }
            else {
                   //TODO SHOULD MAKE DISPLACMENT
                   // DET_REPORTERROR(MODULE_ID_DEM, 0, DEM_STORE_FF_DATA_PRI_MEM_ID, DEM_E_PRI_MEM_FF_DATA_BUFF_FULL);
            }
        }

}
/********************************************************************************************/
/* Procedure:   storeFreezeFrameDataEvtMem                                                  */
/* Description: Store the freeze frame data in event memory according to                    */
/*              "eventParam" destination option                                             */
/********************************************************************************************/
static void storeFreezeFrameDataEvtMem(const DemEventParameter_s *eventParam, const FreezeFrameRecType *freezeFrame)
{
    uint16 i ;
    for(i = 0 ; (i < DEMPRIMARYMEMORY_SIZE) ; i++)
    {
        switch (eventParam->DemDTCRef_ptr->DemDTCAttributesRef_ptr->DemMemoryDestinationRef_type)
        {
        /*-------[SWS_Dem_00934]---*/
        case DEMPRIMARYMEMORY_REFERENCE_TYPE:
            storeFreezeFrameDataPriMem(eventParam, freezeFrame);
        break;

        case DEMUSERDEFINEDMEMORY_REFERENCE_TYPE:
        case DEMMIRRORMEMORY_REFERENCE_TYPE:
        break;
        default:
        break;
        }

    }

}
/**********************************************************************************************************/
/* Procedure:   deleteFreezeFrameDataPriMem                                                               */
/* Description: Delete the FreezFrame from the primary memory                                             */
/**********************************************************************************************************/
static void deleteFreezeFrameDataPriMem(const DemEventParameter_s *eventParam)
{
    uint16 i;
    for (i = 0; i<DEMPRIMARYMEMORY_SIZE; i++){
        if (priMemFreezeFrameBuffer[i].eventId == eventParam->DemEventId)
        {
            memset(&priMemFreezeFrameBuffer[i], 0, sizeof(FreezeFrameRecType));
        }
    }
}

/**********************************************************************************************************/
/* Procedure:   lookupFreezeFrameDataPriMem                                                               */
/* Description: Returns TRUE if the requested event id is found, "freezeFrame"                            */
/*              points to the found data.                                                                 */
/**********************************************************************************************************/
static boolean lookupFreezeFrameDataPriMem(Dem_EventIdType eventId,uint8 recordNumber, FreezeFrameRecType **freezeFrame)
{
    boolean eventIdFound = FALSE;
    uint16 i;

    for (i = 0; (i < DEMPRIMARYMEMORY_SIZE) && (eventIdFound == FALSE); i++) {
        if((priMemFreezeFrameBuffer[i].eventId == eventId) && (priMemFreezeFrameBuffer[i].recordNumber == recordNumber))
        {
            eventIdFound = TRUE ;
        }
    }

    if (eventIdFound == TRUE) {
        *freezeFrame = &priMemFreezeFrameBuffer[i-1];
    }
    return eventIdFound;
}
/**********************************************************************************************************/
/* Procedure:   deleteExtendedDataPriMem                                                                  */
/* Description: Delete the extended data of "eventParam->eventId" from "priMemExtDataBuffer".             */
/**********************************************************************************************************/
static void deleteExtendedDataPriMem(const DemEventParameter_s *eventParam)
{
    boolean eventIdFound = FALSE;
    uint16 i;
    // Check if already stored
    for (i = 0;(i<DEME3TENDEDDATACLASS_SIZE) && (eventIdFound == FALSE); i++){
        if(priMemExtDataBuffer[i].eventId == eventParam->DemEventId )
        {
            eventIdFound = TRUE;
        }
    }

    if (eventIdFound == TRUE) {
        // Yes, clear record
        memset(&priMemExtDataBuffer[i-1], 0, sizeof(ExtDataRecType));
    }
}
/**********************************************************************************************************/
/* Procedure:   resetEventStatusRec                                                                       */
/* Description: Reset the status record of "eventParam->eventId" from "eventStatusBuffer".                */
/**********************************************************************************************************/
static void resetEventStatusRec(const DemEventParameter_s *eventParam)
{
    EventStatusRecType *eventStatusRecPtr;
    // Lookup event ID
    lookupEventStatusRec(eventParam->DemEventId, &eventStatusRecPtr);

    if (eventStatusRecPtr != NULL) {
        // Reset event record
        eventStatusRecPtr->faultDetectionCounter = 0;
        eventStatusRecPtr->maxFaultDetectionCounter = 0;
        eventStatusRecPtr->eventStatus = ( DEM_UDS_STATUS_TNCTOC| DEM_UDS_STATUS_TNCSLC);
        eventStatusRecPtr->errorStatusChanged = FALSE;
        eventStatusRecPtr->occurrence = 0;
        eventStatusRecPtr->confirmationCounter = 0;
    }
}

/********************************************************************************************/
/* Service name:  Dem_TriggerDebounceAlgorithmBehavior                                                */
/* Parameters (in):   EventId                                                               */
/* Parameters (inout):                                                                      */
/* Parameters (out):                                                                        */
/* Description:                                                                             */
/********************************************************************************************/
static void Dem_TriggerDebounceAlgorithmBehavior(Dem_EventIdType EventId)
{
    DemDebounceBehavior_Enum DebounceBehavior ;
    Dem_DebounceAlgoNameType DebounceAlgo = Dem_getDebounceAlgoNameType(EventId);

    //EventStatusRecType *EventIdParam ;
    //lookupEventStatusRec(EventId, &EventIdParam) ;
    switch (DebounceAlgo)
    {
    //TODO TOOL
    case DEM_DEBOUNCE_COUNTER_BASED:
        DebounceBehavior = DemDebounceAlgorithmClass[eventStatusBuffer[EventId-1].EventParamterRef->DemDebounceAlgorithmClass_startingIndex]\
                          .DebounceAlgorithm.DemDebounceCounterBasedClassRef_ptr->DemDebounceBehavior;
        break;

    case DEM_DEBOUNCE_TIME_BASED:
        DebounceBehavior = DemDebounceAlgorithmClass[eventStatusBuffer[EventId-1].\
                           EventParamterRef->DemDebounceAlgorithmClass_startingIndex]\
                          .DebounceAlgorithm.DemDebounceTimeBaseRef_ptr->DemDebounceBehavior;
        break;

    default:
        break;
    }
    if (DebounceBehavior == DEM_DEBOUNCE_FREEZE)
    {
      /* freeze corresponding debounce counter */

      // freeze ???
    }
    else if (DebounceBehavior == DEM_DEBOUNCE_RESET)
    {
      /* reset corresponding debounce counter */
        //EventStatusRecType *eventStatusRecPtr;
        //lookupEventStatusRec(EventId, &eventStatusRecPtr);
        //If Dem_SetEventAvailable is called with AvailableStatus == �false�,
        //the Dem shall set the UDS status shall be set to 0x00 for this ev
        eventStatusBuffer[EventId-1].faultDetectionCounter = 0 ;
    }
    else
    {
      /* DebounceBehavior is DEM_DEBOUNCE_CONTINUE. This ensures
         backward compatibility. */
    }
}

/********************************************************************************************/
/* Procedure:   deleteEventPriMem                                                           */
/* Description: Delete the event data of "eventParam->eventId" from "priMemEventBuffer".    */
/********************************************************************************************/
static void deleteEventPriMem(const DemEventParameter_s *eventParam)
{
    boolean eventIdFound = FALSE;
    uint16 i;
    for (i = 0; (i < DemMaxNumberEventEntryPrimary) && (eventIdFound == FALSE); i++)
    {
        if(priMemEventBuffer[i].eventId == eventParam->DemEventId)
        {
            eventIdFound = TRUE ;
        }
    }
    if (eventIdFound == TRUE)
    {
        memset(&priMemEventBuffer[i-1], 0, sizeof(EventRecType));
    }
}
/********************************************************************************************/
/* Procedure:   setOperationCycleState                                                      */
/* Description: Change the operation state of "operationCycleId" to "cycleState"            */
/*              and updates stored event connected to this cycle id.                        */
/*              Returns E_OK if operation was successful else E_NOT_OK..                    */
/********************************************************************************************/
static Std_ReturnType  setOperationCycleState(uint8 operationCycleId, Dem_OperationCycleStateType  cycleState)
{
    uint16 i;
    Std_ReturnType returnCode = E_OK;
    if (operationCycleId < DEMOPERATIONCYCLE_SIZE)
    {
        switch(cycleState)
        {
        case DEM_CYCLE_STATE_START:
            operationCycleStateList[operationCycleId] = cycleState;
            for (i = 0; i < MAXNUNBEROFEVENTS; i++)
            {
                /*search for the eventid for that operation cycle id*/
                if ((eventStatusBuffer[i].eventId != DEMEVENTPARAMETER_ID_0) && (eventStatusBuffer[i].EventParamterRef-> \
                        DemOperationCycleRef_ptr->DemOperationCycleId == operationCycleId))
                {
                    /*[SWS_Dem_00389]*/
                    eventStatusBuffer[i].eventStatus &= ~DEM_UDS_STATUS_TFTOC;
                    eventStatusBuffer[i].eventStatus |= DEM_UDS_STATUS_TNCTOC;
                    /*callback in case of starting or restarting*/
                    //TODO

                  /*  (DemCallbackInitMForE[eventStatusBuffer[i].EventParamterRef->DemCallbackInitMForE_startingIndex].
                            DemCallbackInitMForEFnc)(DEM_INIT_MONITOR_REENABLED); */

                }
            }
            break;
        case DEM_CYCLE_STATE_END:
            operationCycleStateList[operationCycleId] = cycleState;
            // Lookup event ID
            for (i = 0; i < MAXNUNBEROFEVENTS; i++)
            {
                if ((eventStatusBuffer[i].eventId != DEMEVENTPARAMETER_ID_0) && (eventStatusBuffer[i].EventParamterRef-> \
                        DemOperationCycleRef_ptr->DemOperationCycleId == operationCycleId))
                {
                    if ((!(eventStatusBuffer[i].eventStatus & DEM_UDS_STATUS_TFTOC))
                            && (!(eventStatusBuffer[i].eventStatus & DEM_UDS_STATUS_TNCTOC)))
                    {
                        // Clear pendingDTC bit
                        eventStatusBuffer[i].eventStatus &= ~DEM_UDS_STATUS_PDTC;
                        storeEventEvtMem(eventStatusBuffer[i].EventParamterRef, &eventStatusBuffer[i]);
                    }
                }
            }
            break;
        default:
            //DET_REPORTERROR(MODULE_ID_DEM, 0, DEM_SETOPERATIONCYCLESTATE_ID, DEM_E_PARAM_DATA);
            returnCode = E_NOT_OK;
            break;
        }

    }
    else
    {
            //DET_REPORTERROR(MODULE_ID_DEM, 0, DEM_SETOPERATIONCYCLESTATE_ID, DEM_E_PARAM_DATA);
            returnCode = E_NOT_OK;
    }
    return returnCode;
}

/************************************************************************************************/
/* Procedure:   lookupAgingRecPriMem                                                            */
/* Description: Returns the pointer to event id parameters of "eventId" in                      */
/*               "*priMemAgingBuffer",  if not found NULL is returned.                          */
/************************************************************************************************/

/**
 * @brief <b>lookupAgingRecPriMem</b>
 * 
 * 
 * @param
 * @param
 * @return
 * @details
 */

static boolean lookupAgingRecPriMem(Dem_EventIdType eventId, const HealingRecType **agingRec)
{
    uint16 i;
    boolean agingRecFound = FALSE;

    for (i = 0; i < MAXNUNBEROFEVENTS && (agingRecFound == FALSE); i++)
    {
        if(priMemAgingBuffer[i].eventId == eventId)
        {
            agingRecFound = TRUE;
        }

    }

    if(agingRecFound){
        *agingRec = &priMemAgingBuffer[i-1];
    }
    else{
        *agingRec = NULL;
    }

    return agingRecFound;

}

/**
 * @brief <b>deleteAgingRecPriMem</b>
 * delete aging record in primary memory
 * 
 * @param eventParam pointer to This container contains the configuration (parameters) for events
 * @details
 */
static void deleteAgingRecPriMem(const DemEventParameter_s *eventParam)
{
    uint16 i;

    for (i = 0; i<MAXNUNBEROFEVENTS; i++)
    {
        if (priMemAgingBuffer[i].eventId == eventParam->DemEventId)
        {
            memset(&priMemAgingBuffer[i], 0, sizeof(HealingRecType));
        }
    }


}

/**
 * @brief <b>handleAging</b>
 * according to the operation state of "operationCycleId" to
 * "cycleState" , handle the aging relatived data
 * 
 * @param   operationCycleId  Identification of operation cycle, like power cycle, driving cycle 
 * @param   cycleState contains operation cycle state values, which can be reported via Dem_SetOperationCycleState()
 * @return  E_OK if operation was successful else E_NOT_OK.
 * @details
 */
static Std_ReturnType handleAging(uint8 operationCycleId, Dem_OperationCycleStateType cycleState)
{
    uint16 i;
    Std_ReturnType returnCode = E_OK;
    HealingRecType *agingRecLocal = NULL;
    boolean agingRecFound = FALSE;

    if (operationCycleId < DEMOPERATIONCYCLE_SIZE)
    {
        switch(cycleState)
        {
        case DEM_CYCLE_STATE_START:
            break;
        case DEM_CYCLE_STATE_END :
            for (i = 0; i < MAXNUNBEROFEVENTS; i++)
            {
                if(eventStatusBuffer[i].eventId != DEMEVENTPARAMETER_ID_0)
                {
                    if(eventStatusBuffer[i].EventParamterRef->DemDTCRef_ptr->DemDTCAttributesRef_ptr->DemAgingAllowed == TRUE
                            && eventStatusBuffer[i].EventParamterRef->DemDTCRef_ptr->DemDTCAttributesRef_ptr->DemAgingCycleRef_ptr->DemOperationCycleId == operationCycleId)
                    {
                        if((eventStatusBuffer[i].eventStatus & DEM_UDS_STATUS_PDTC)\
                            && (!(eventStatusBuffer[i].eventStatus & DEM_UDS_STATUS_TFTOC))\
                            && (!(eventStatusBuffer[i].eventStatus & DEM_UDS_STATUS_TNCTOC)))
                        {
                            agingRecFound = lookupAgingRecPriMem(eventStatusBuffer[i].eventId, (const HealingRecType **)(&agingRecLocal));
                            if(agingRecFound)
                            {
                                agingRecLocal->agingCounter++;
                                if(agingRecLocal->agingCounter > eventStatusBuffer[i].EventParamterRef->DemDTCRef_ptr->DemDTCAttributesRef_ptr->DemAgingCycleCounterThreshold)
                                {
                                    deleteAgingRecPriMem(eventStatusBuffer[i].EventParamterRef);
                                    eventStatusBuffer[i].eventStatus &= (~DEM_UDS_STATUS_CDTC);
                                    eventStatusBuffer[i].eventStatus &= (~DEM_UDS_STATUS_PDTC);
                                    eventStatusBuffer[i].eventStatus &= (~DEM_UDS_STATUS_WIR);
                                    eventStatusBuffer[i].confirmationCounter = 0;
                                    storeEventEvtMem(eventStatusBuffer[i].EventParamterRef, &eventStatusBuffer[i]);

                                }
                                AgingIsModified = TRUE;
                                agingRecFound = lookupAgingRecPriMem(DEMEVENTPARAMETER_ID_0, (const HealingRecType **)(&agingRecLocal));
                                if(agingRecFound == TRUE)
                                {
                                    agingRecLocal->eventId = eventStatusBuffer[i].eventId;
                                    agingRecLocal->agingCounter++;
                                    AgingIsModified = TRUE;
                                }
                                else{
                                    /* primary memory of aging records is full. */
                                }
                            }
                         }
                      }
                    }
                }
        default:
            returnCode = E_NOT_OK;
            break;
            }
    }
    else
    {
        //DET_REPORTERROR(MODULE_ID_DEM, 0, DEM_SETOPERATIONCYCLESTATE_ID, DEM_E_PARAM_DATA);
        returnCode = E_NOT_OK;
     }
    return returnCode;
}

/********************************************************************************************/
/* Procedure:   storeAgingRecPerMem                                                         */
/* Description: store aging records in NVRam                                                */
/********************************************************************************************/
static void storeAgingRecPerMem(uint16 AgingBlockId)
{
  //save the adging value to the NVM
}


/**
 * @brief <b>Dem_GetDTCSelection</b>
 * store aging records in NVRam
 * 
 * @param ClientId Unique clientid, assignedtotheinstanceofthecalling module  
 * @param DTCSelection Receives the DTCSelection info for clientid
 * @details
 */
static void Dem_GetDTCSelection( uint8 ClientId,Dem_DTCSelectionType *DTCSelection)
{
  DTCSelection->DTCInfo.DTC       = Dem_DTCSelection[ClientId].DTCInfo.DTC;
  DTCSelection->DTCInfo.EventId   = Dem_DTCSelection[ClientId].DTCInfo.EventId;
  DTCSelection->DTCInfo.DTCOrigin = Dem_DTCSelection[ClientId].DTCInfo.DTCOrigin;
  DTCSelection->DTCInfo.DTCFormat = Dem_DTCSelection[ClientId].DTCInfo.DTCFormat;
  DTCSelection->SelectorStatus    = Dem_DTCSelection[ClientId].SelectorStatus;

}

/********************************************************************************************/
/* Procedure:   matchEventWithDtcFilter                                                     */
/* Description: Returns TRUE if the event pointed by "event" fulfill                        */
/*              the "dtcFilter" global filter settings.                                     */
/********************************************************************************************/
static boolean matchEventWithDtcFilter(const EventStatusRecType *eventRec , uint8 Clientid)
{
    boolean dtcMatch = FALSE;

    // Check status
    if ((dtcFilter.dtcStatusMask == DEM_DTC_STATUS_MASK_ALL) || (eventRec->eventStatus & dtcFilter.dtcStatusMask)) {
        if (eventRec->EventParamterRef != NULL)
        {
            // Check dtcKind
            if ( dtcFilter.dtcKind == Dem_DTCSelection[Clientid].DTCInfo.DTCKind)
            {
                // Check dtcOrigin
                if (dtcFilter.dtcOrigin == Dem_DTCSelection[Clientid].DTCInfo.DTCOrigin)
                {
                    // Check severity
                    if ((dtcFilter.filterWithSeverity == DEM_FILTER_WITH_SEVERITY_NO)
                        || ((dtcFilter.filterWithSeverity == DEM_FILTER_WITH_SEVERITY_YES)))
                    {
                        // Check fault detection counter
                        if ((dtcFilter.filterForFaultDetectionCounter == DEM_FILTER_FOR_FDC_NO)
                            || ((dtcFilter.filterWithSeverity == DEM_FILTER_FOR_FDC_YES)))
                        {
                            dtcMatch = TRUE;
                        }
                    }
                }
            }
        }
    }

    return dtcMatch;
}

/**
 * @brief <b></b>
 * 
 * 
 * @param
 * @param
 * @return
 * @details
 */

/**
 *  @brief <b>Dem_ClearPrestoredFreezeFrame</b>
 *  Clears a prestored freeze frame of a specific event. This API can only
 *  be used through the RTE and therefore no declaration is exported via
 *  Dem.h.
 *  @param EventId Identification of an event by assigned EventId
 *  @return Std_ReturnType which is OK or Not-Ok
 *  @see
 *  @details
 */
Std_ReturnType Dem_ClearPrestoredFreezeFrame(Dem_EventIdType EventId)
{
    Std_ReturnType returnCode = E_NOT_OK;
#if( DEMDEVERRORDETECT ==  STD_ON)
    if(Dem_ModuleState == MODULE_UN_INTAILIZED)
    {
        //Report an error
        //DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_UN);

    }
    else if ( EventId == DEMEVENTPARAMETER_ID_0)
    {
        //Report an error
        //DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_PARAM_DATA);
    }
   /* else if (EventId > MAXNUNBEROFEVENTS)
    {
       //DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_WRONG_CONFIGURATION);
    }*/
#endif
    else
    {
         DemEventParameter_s * EventIdParam ;
        FreezeFrameRecType *freezeFrame;
        boolean Result;
        //check the existence of the event
        checkEventIdExist(EventId , &EventIdParam);
        if(EventIdParam != NULL)
        {
            switch (EventIdParam->DemDTCRef_ptr->DemDTCAttributesRef_ptr->DemMemoryDestinationRef_type)
            {

            case DEMPRIMARYMEMORY_REFERENCE_TYPE:
                Result = lookupFreezeFrameDataPriMem(EventId,EventIdParam->DemDTCRef_ptr->DemDTCAttributesRef_ptr-> \
                                            DemFreezeFrameRecNumClassRef_ptr->DemFreezeFrameRecordClassRef_ptr->DemFreezeFrameRecordNumber, &freezeFrame) ;
                if(Result == TRUE)
                {
                    memset((void*)freezeFrame, 0, sizeof(FreezeFrameRecType));
                }
            break;

            case DEMUSERDEFINEDMEMORY_REFERENCE_TYPE:
            case DEMMIRRORMEMORY_REFERENCE_TYPE:
            break;
            default:
            break;
            }
        }
    }
    return returnCode;
}

/**
 *  @brief <b>Dem_SetEventStatus</b>
 *  Called by SW-Cs or BSW modules to report monitor status information to
 *  the Dem. BSW modules calling Dem_SetEventStatus can safely ignore
 *  the return value.
 *  @param EventId Identification of an event by assigned EventId
 *  @param EventStatus Monitor test result
 *  @return Std_ReturnType which is OK or Not-Ok
 *  @see
 *  @details
 */
Std_ReturnType Dem_SetEventStatus(Dem_EventIdType EventId, Dem_EventStatusType EventStatus)
{
    Std_ReturnType Return_Value = E_NOT_OK;
    volatile EventStatusRecType eventStatusLocal;
    DemEventParameter_s *eventParam;

#if( DEMDEVERRORDETECT ==  STD_ON)
    if(Dem_ModuleState == MODULE_PREINTAILIZED)
    {
        //Report an error
        //DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_UNINIT);
        //save the event in the error Buffer
        if( DemEventParameter[EventId-1].DemEventKind == DEM_EVENT_KIND_BSW )
        {
            Dem_ErrorQueue[EventId-1].EventId  = EventId ;
        }
        else
        {
            Return_Value = E_NOT_OK;
        }
    }
    else if (EventId == DEMEVENTPARAMETER_ID_0)
    {
        //Report an error
        //DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_PARAM_DATA);
        Return_Value = E_NOT_OK;
    }
    /*else if (EventId > MAXNUNBEROFEVENTS)
    {
       //DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_WRONG_CONFIGURATION);
    }*/
    else if (((EventStatus != DEM_EVENT_STATUS_PASSED) &&
              (EventStatus != DEM_EVENT_STATUS_FAILED)) &&
              ((EventStatus != DEM_EVENT_STATUS_PREPASSED) &&
              (EventStatus != DEM_EVENT_STATUS_PREFAILED))
             )
    {
      // DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_PARAM_DATA);
        Return_Value = E_NOT_OK;
    }
    else if(Dem_GetEventAvailable(EventId) == FALSE)
    {
        /* event is disabled so reporting shall be skipped */
    }
#endif
    else
    {
        checkEventIdExist(EventId , &eventParam);
        if(eventParam != NULL)
        {
            if( operationCycleStateList[eventStatusBuffer[EventId-1].EventParamterRef->DemOperationCycleRef_ptr->DemOperationCycleId] == DEM_CYCLE_STATE_START)
            {
                if(eventStatusBuffer[EventId-1].EventParamterRef->DemEnableConditionGroupRef_ptr->DemEnableConditionRef_ptr->DemEnableConditionStatus == TRUE)
                {
                    /*Update the EventStatus*/
                    updateEventStatusRec(EventId, EventStatus, TRUE, &eventStatusLocal);
                    if( eventStatusBuffer[EventId-1].errorStatusChanged == TRUE )
                    {
                        /*Store the event iN the memory*/
                        storeEventEvtMem(eventStatusBuffer[EventId-1].EventParamterRef, &eventStatusBuffer[EventId-1]);
                        Return_Value = E_OK;
                        //TODO check for freeze frame Queue to store the freezframe
                    }
                 }
              }
         }
         else
         {

         }
      }
 return Return_Value ;
}
/**
 *  @brief <b>Dem_ResetEventStatus</b>
 *  Resets the event failed status. This API can only be used through the
 *  RTE and therefore no declaration is exported via Dem.h.
 *  @param EventId Identification of an event by assigned EventId
 *  @return Std_ReturnType which is OK or Not-Ok
 *  @details
 *
 */
Std_ReturnType Dem_ResetEventStatus(Dem_EventIdType EventId)
{
    Std_ReturnType returnCode = E_OK;
#if( DEMDEVERRORDETECT ==  STD_ON)
    if(Dem_ModuleState == MODULE_UN_INTAILIZED)
    {
        //Report an error
        //DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_UNINIT);
        returnCode = E_NOT_OK;
    }
    else if ( EventId == DEMEVENTPARAMETER_ID_0)
    {
        //Report an error
        //DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_PARAM_DATA);
        returnCode = E_NOT_OK;
    }
   /* else if (EventId > MAXNUNBEROFEVENTS)
    {
       //DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_WRONG_CONFIGURATION);
        returnCode = E_NOT_OK;
    } */
    else if(Dem_GetEventAvailable(EventId) == FALSE)
    {
        /* event is disabled so reporting shall be skipped */
    }
#endif
    else
    {
        EventStatusRecType *eventStatusPtr;
        lookupEventStatusRec( EventId,&eventStatusPtr);
        if( eventStatusPtr!= NULL)
        {
            /* reset of failed qualification-result is allowed only if event
             * is not already tested this operation cycle */
            /*TODO  Clear bits in DTCStatusMask */

            if(( eventStatusBuffer[EventId-1].eventStatus & DEM_UDS_STATUS_TNCTOC ) )
            {
                //Dem_UdsStatusByteType EventUdsStatusByte_Old = eventStatusPtr->eventStatus;
                /*Reset the testfailed bit*/
                eventStatusBuffer[EventId-1].eventStatus &= ~(DEM_UDS_STATUS_TF);
                //Dem_UdsStatusByteType EventUdsStatusByte_New = eventStatusPtr->eventStatus;
                /*CallBack for the Status changed*/
                /*(DemCallbackEventDataChanged[DemEventParameter[EventId].DemCallbackEventUdsStatusChanged_startingIndex] \
                                             .DemCallbackEventDataChangedFnc(EventUdsStatusByte_Old , EventUdsStatusByte_New);*/
                /*
                (DemCallbackEventDataChanged[eventStatusPtr->EventParamterRef->DemCallbackEventUdsStatusChanged_startingIndex].DemCallbackEventDataChangedFnc)(EventId);
                */
            }
            else
            {
                returnCode = E_NOT_OK;
            }
            /* reset debouncing counters for event  */
            if( Dem_getDebounceAlgoNameType(EventId) == DEM_DEBOUNCE_COUNTER_BASED )
            {
                Dem_TriggerDebounceAlgorithmBehavior(EventId);
               // eventStatusPtr->faultDetectionCounter = 0 ;
            }
        }
        else
        {
            // DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_PARAM_DATA);
            returnCode = E_NOT_OK;
        }

    }
return returnCode ;
}
/**
 *  @brief <b>Dem_GetStatusOfDTC</b>
 *  Gets the status of a DTC.
 *  @param ClientId Identification of an event by assigned EventId
 *  module.
 *  @param DTCStatus This parameter receives the status information of
 *  the requested DTC.It follows the format as defined in ISO14229-1
 *  If the return value of the function call is other than
 *  DEM_FILTERED_OK this parameter does not contain valid data.
 *  @return Std_ReturnType which is OK or Not-Ok
 *  @details
 */
/*Table 7.2: Calculation of UDS status byte -------[SWS_Dem_00441]-------*/
Std_ReturnType Dem_GetStatusOfDTC(uint8 ClientId , uint8* DTCStatus)
{
    Std_ReturnType Return_code = E_NOT_OK ;
#if (DEMDEVERRORDETECT == STD_ON)
  if(Dem_ModuleState == MODULE_UN_INTAILIZED)
  {
    //DEM_REPORT_ERROR(DEM_SID_GetStatusOfDTC, DEM_E_UNINIT);
  }
  else if (DTCStatus == NULL)
  {
    //DEM_REPORT_ERROR(DEM_SID_GetStatusOfDTC, DEM_E_PARAM_POINTER);
  }
#endif
  else if (ClientId > DEMCLIENT_SIZE)
  {
    //DEM_REPORT_ERROR(DEM_SID_GetStatusOfDTC, DEM_E_WRONG_CONFIGURATION);
  }
  else
  {
      checkDtc(ClientId);
      if( Dem_DTCSelection[ClientId].SelectorStatus == DEM_DTC_SELECTOR_WRONG_DTC_ORIGIN)
      {
          Return_code = E_NOT_OK ;
      }
      else if( Dem_DTCSelection[ClientId].SelectorStatus == DEM_DTC_SELECTOR_WRONG_DTC)
      {
          Return_code = E_NOT_OK ;
      }
      else
      {
          uint16 i;
          Dem_EventIdType EvId ;
          /*Reset the Status pointer*/
          *DTCStatus = 0 ;
          /*Get the ID of requested DTC*/
          /*-------[SWS_Dem_00441]-------*/
          for( i = 0 ; i < MAXNUNBEROFEVENTS ; i++)
          {
              if( eventStatusBuffer[i].EventParamterRef->DemDTCRef_ptr->DemDtcValue == Dem_DTCSelection[ClientId].DTCInfo.DTC)
              {
                  *DTCStatus |= eventStatusBuffer[i].eventStatus ;
              }
          }
          Return_code = E_OK;
      }
  }
  return Return_code ;
}
/**
 *  @brief <b>Dem_GetEventUdsStatus</b>
 *  Gets the current UDS status byte assigned to the DTC for the event
 *  @param EventId Identification of an event by assigned EventId
 *  @param UDSStatusByte UDS DTC status byte of the requested event (refer
 *  to chapter "Status bit support").
 *  If the return value of the function call is E_NOT_OK,
 *  this parameter does not contain valid data.
 *  @return Std_ReturnType which is OK or Not-Ok
 *  @details 
 */
 Std_ReturnType Dem_GetEventUdsStatus( Dem_EventIdType EventId, Dem_UdsStatusByteType* UDSStatusByte )
 {
    Std_ReturnType Error_t = E_NOT_OK;
#if (DEMDEVERRORDETECT == STD_ON)
         if(Dem_ModuleState == MODULE_UN_INTAILIZED)
         {
           //DEM_REPORT_ERROR(DEM_SID_GetStatusOfDTC, DEM_E_UNINIT);
         }
         else if (UDSStatusByte == NULL)
         {
           //DEM_REPORT_ERROR(DEM_SID_GetStatusOfDTC, DEM_E_PARAM_POINTER);
             Error_t = E_NOT_OK;
         }
         else if ( EventId == DEMEVENTPARAMETER_ID_0)
         {
             //Report an error
             //DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_PARAM_DATA);
             Error_t = E_NOT_OK;
         }
         /*else if (EventId > MAXNUNBEROFEVENTS)
         {
            //DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_WRONG_CONFIGURATION);
             Error_t = E_NOT_OK;
         }*/
#endif
         else
        {
             //EventStatusRecType *eventStatusRec;
             //lookupEventStatusRec(EventId, &eventStatusRec);
             if( eventStatusBuffer[EventId-1].EventParamterRef->DemEventAvailable == FALSE)
             {
                 /* event is disabled so reporting shall be skipped */
             }
             else
             {
                 //EventStatusRecType EventStatus ;
                 //getEventStatusRec(EventId, &EventStatus);
                 *UDSStatusByte = eventStatusBuffer[EventId-1].eventStatus;
                 Error_t = E_OK ;
             }
        }
    return Error_t ;
 }
 /**
  *  @brief <b>Dem_GetDTCOfEvent</b>
  *  Gets the DTC of an event.
  *  @param EventId Identification of an event by assigned EventId
  *  @param DTCFormat Defines the output-format of the requested DTC
  *  value
  *  @return E_OK: get of DTC was successful
  *  @return E_NOT_OK: the call was not successful
  *  @return  DEM_E_NO_DTC_AVAILABLE: there is no DTC
  *  configured in the requested format
  *  @details
  */
 Std_ReturnType Dem_GetDTCOfEvent (Dem_EventIdType EventId, Dem_DTCFormatType DTCFormat, uint32* DTCOfEvent)
 {
     Std_ReturnType returnCode = DEM_E_NO_DTC_AVAILABLE;
#if (DEMDEVERRORDETECT == STD_ON)
         if(Dem_ModuleState == MODULE_UN_INTAILIZED)
         {
           //DEM_REPORT_ERROR(DEM_SID_GetStatusOfDTC, DEM_E_UNINIT);
         }
         else if (DTCOfEvent == NULL)
         {
           //DEM_REPORT_ERROR(DEM_SID_GetStatusOfDTC, DEM_E_PARAM_POINTER);
             returnCode = E_NOT_OK;
         }
         else if ( EventId == DEMEVENTPARAMETER_ID_0)
         {
             //Report an error
             //DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_PARAM_DATA);
             returnCode = E_NOT_OK;
         }
         /*else if (EventId > MAXNUNBEROFEVENTS)
         {
            //DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_WRONG_CONFIGURATION);
             returnCode = E_NOT_OK;
         }*/
         else if ( (DTCFormat != DEM_DTC_FORMAT_OBD) && (DTCFormat != DEM_DTC_FORMAT_UDS) \
                 &&(DTCFormat != DEM_DTC_FORMAT_J1939))
         {
             //DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_PARAM_DATA);
             //  Error_t = E_NOT_OK ;
         }
         else if (Dem_GetEventAvailable(EventId) == FALSE)
         {
             /* event is disabled so getting of DTC of event shall be skipped */
             /* E_NOT_OK return value remains */
         }
#endif
     DemEventParameter_s *eventIdParam;

     checkEventIdExist(EventId ,&eventIdParam );
     if (eventIdParam != NULL)
     {
         Dem_DTCType DTCValue; // uint32
             /* get the DTC mapped to event Id */
         if (DTCFormat == DEM_DTC_FORMAT_OBD)
         {
             /* OBD NOT SUPPORTED */
             DTCValue = DEM_NO_DTC;
         }
         else if (DTCFormat == DEM_DTC_FORMAT_J1939)
         {
             /* format is not supported in this version */
             DTCValue = DEM_NO_DTC;
         }
         else
         {
             DTCValue =  eventStatusBuffer[EventId-1].EventParamterRef->DemDTCRef_ptr->DemDtcValue;
         }

         if (DTCValue == DEM_NO_DTC)
         {
             returnCode = DEM_E_NO_DTC_AVAILABLE;
         }
         else
         {
             /* update out parameter with computed value */
             *DTCOfEvent = DTCValue;
             returnCode= E_OK;
         }
     }
     else
     {
         returnCode = E_NOT_OK;
     }
     return returnCode;
 }
 /**
  *  @brief <b>Dem_SetEnableCondition</b>
  *  Sets an enable condition
  *  @param EnableConditionID This parameter identifies the enable condition.
  *  @param ConditionFulfilled This parameter specifies whether the enable condition
  *  assigned to the EnableConditionID is fulfilled(TRUE) or not fulfilled (FALSE).
  *  In case the enable condition could be set successfully
  *  @return <b>E_OK</b>: In case the enable condition could be set successfully
  *  the API call returns E_OK
  *  @return <b>E_NOT_OK</b>: If the setting of the enable condition failed
  *  the return value of the function is E_NOT_OK.
 *  @details
  */
Std_ReturnType Dem_SetEnableCondition( uint8 EnableConditionID, boolean ConditionFulfilled )
{

    Std_ReturnType returnCode = E_NOT_OK;
#if (DEMDEVERRORDETECT == STD_ON)
        if(Dem_ModuleState == MODULE_UN_INTAILIZED)
        {
          //DEM_REPORT_ERROR(DEM_SID_GetStatusOfDTC, DEM_E_UNINIT);
        }
        else if ( (ConditionFulfilled != FALSE) && (ConditionFulfilled != TRUE))
        {
            //DEM_REPORT_ERROR(DEM_SID_SetEnableCondition, DEM_E_PARAM_DATA);
        }
        else if (EnableConditionID >= DEMENABLECONDITION_SIZE) // from LCfg
        {
          // DEM_REPORT_ERROR(DEM_SID_SetEnableCondition, DEM_E_WRONG_CONFIGURATION);
        }
        else
#endif
        {
            uint8 i ;
            for (i = 0; i < DEMENABLECONDITIONGROUP_SIZE ; i++)
            {
                uint8 j = DemEnableConditionGroup[i].DemEnableConditionRef_ptr->DemEnableConditionId;
                if (j == EnableConditionID )
                {
                    DemEnableConditionGroup[i].DemEnableConditionRef_ptr->DemEnableConditionStatus = ConditionFulfilled;
                    returnCode = E_OK;
                    break;
                }
                else
                {
                    // NOT VALID ENABLECONDITIONID
                    returnCode = E_NOT_OK ;
                }

            }
            // it should be in another function that checks
            // Not fully correct
            for ( i = 0; i < MAXNUNBEROFEVENTS; i++)
            {
               boolean status = eventStatusBuffer[i].EventParamterRef->DemEnableConditionGroupRef_ptr-> \
                       DemEnableConditionRef_ptr->DemEnableConditionStatus;
               if (status == FALSE)
               {
                   Dem_TriggerDebounceAlgorithmBehavior(eventStatusBuffer[i].eventId);
               }
               else
               {
                   // ALL ENABLE_CONDITIONS ARE TRUE
                   (DemCallbackInitMForE[eventStatusBuffer[i].EventParamterRef->DemCallbackInitMForE_startingIndex]. \
                           DemCallbackInitMForEFnc )( DEM_INIT_MONITOR_REENABLED ) ;

               }
               
            }
            
            
        }

      return returnCode ;
}
/********************************************************************************************/
/**
 *  @brief <b>Dem_GetDTCSuppression</b>
 *  Returns the suppression status of a specific DTC. API Availability:
 *  @param ClientId Unique client id, assigned to the instance of the calling
 *  module
 *  @param SuppressionStatus Defines whether the respective DTC is suppressed
 *  (TRUE) or enabled (FALSE).
 *  @return <b>E_OK</b>: Operation was successful.
 *  @return <b>E_NOT_OK</b>: Dem_SelectDTC was not called.
 *  @return <b>DEM_WRONG_DTC</b>: No valid DTC or DTC group selected.
 *  @return <b>DEM_WRONG_DTCORIGIN</b>: Wrong DTC origin selected.
 *  @return <b>DEM_PENDING</b>: The requested value is calculated asynchronously
 *  and currently not available. The caller can retry later.
 *  @details
 */
/********************************************************************************************/
#if (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION)
// demselectdtc >> needed??
Std_ReturnType Dem_GetDTCSuppression( uint8 ClientId, boolean* SuppressionStatus )
{
    Std_ReturnType returnCode = E_NOT_OK;
    DemEventParameter_s eventParam ;
    *SuppressionStatus = FALSE ;
#if (DEMDEVERRORDETECT == STD_ON)
        if(Dem_ModuleState == MODULE_UN_INTAILIZED)
        {
          //DEM_REPORT_ERROR(DEM_SID_GetStatusOfDTC, DEM_E_UNINIT);
        }
        else if (ClientId > DEMCLIENT_SIZE)// from LCfg
        {
            // error
            returnCode = E_NOT_OK;
        }
        else if (SuppressionStatus == NULL)
        {
          // DEM_REPORT_ERROR(DEM_SID_SetEnableCondition, DEM_E_WRONG_CONFIGURATION);
        }
        /*
        else if(checkDtcGroup(ClientId , &eventParam) == FALSE)
        {
            returnCode = DEM_WRONG_DTCORIGIN ;
        }
        */
        else 
#endif
        {
            //Dem_EventIdType EventId ;
            uint16 i ;
            boolean Result = FALSE;
            Dem_DTCType DTC ;
            //DemEventParameter_s *EventIdParam ;
            //EventId = Dem_DTCSelection[ClientId].DTCInfo.EventId ;
            DTC= Dem_DTCSelection[ClientId].DTCInfo.DTC ;
            if(Dem_DTCSelection[ClientId].SelectionStatus == DEM_SELECTED_NONE)
            {
                Result = E_NOT_OK;
            }
            else
            {
                //CHECK if all the DTC'S Events is available
                for ( i = 0 ; (i < MAXNUNBEROFEVENTS); i++)
                {
                    if (eventStatusBuffer[i].EventParamterRef->DemDTCRef_ptr->DemDtcValue == DTC )
                    {
                        if(Dem_GetEventAvailable(eventStatusBuffer[i].eventId) == TRUE)
                        {
                            Result = TRUE ;
                        }
                        else
                        {

                        }
                    }
                    else
                    {
                        // Have NO DTC
                        // returnCode = DEM_WRONG_DTC ;
                    }
                }
                if(Result == TRUE)
                {
                    *SuppressionStatus = FALSE;
                }
                else
                {
                    *SuppressionStatus = TRUE;
                }
                returnCode = E_OK ;
            }

        }
      return returnCode ;
}
#endif
/********************************************************************************************/
/**
 *  @brief <b>Dem_GetFaultDetectionCounter</b>
 *  Returns the suppression status of a specific DTC. API Availability:
 *  @param EventId Identification of an event by assigned EventId.
 *  @param FaultDetectionCounter This parameter receives the Fault Detection
 *  Counter information of the requested EventId. If the return value of the
 *  function call is other than E_OK this parameter does not contain valid data.
 *  @return <b>E_OK</b>: request was successful
 *  @return <b>E_NOT_OK</b>: request failed
 *  @return <b>DEM_E_NO_FDC_AVAILABLE</b>: there is no fault detection counter
 *  available for the requested event
 *  @details
 */
/********************************************************************************************/
Std_ReturnType Dem_GetFaultDetectionCounter( Dem_EventIdType EventId, sint8* FaultDetectionCounter )
{
    Std_ReturnType returnCode = E_NOT_OK;
    const DemEventParameter_s *eventParam;
#if (DEMDEVERRORDETECT == STD_ON)
        if(Dem_ModuleState == MODULE_UN_INTAILIZED)
        {
          //DEM_REPORT_ERROR(DEM_SID_GetFaultDetectionCounter, DEM_E_UNINIT);
        }
        else if (EventId == DEM_EVENT_ID_INVALID) // alot forget it
        {
           // DEM_REPORT_ERROR(DEM_SID_GetFaultDetectionCounter, DEM_E_PARAM_DATA);
        }
       /* else if (EventId > MAXNUNBEROFEVENTS ) // DEM_MAX_EVENTID
        {
           // DEM_REPORT_ERROR(DEM_SID_GetFaultDetectionCounter, DEM_E_WRONG_CONFIGURATION);
        }*/
        else if (FaultDetectionCounter == NULL)
        {
            //DEM_REPORT_ERROR(DEM_SID_GetFaultDetectionCounter, DEM_E_PARAM_POINTER);
        }
        else 
#endif
        {
            if (Dem_GetEventAvailable(EventId) == FALSE)
            {
                /* event is disabled so the getting of fault detection counter
                * shall be skipped */
                /* E_NOT_OK return value remains */
            }
            else
            {
                Dem_DebounceAlgoNameType result ;
                result = Dem_getDebounceAlgoNameType(EventId);
                switch(result)
                {
                case DEM_DEBOUNCE_COUNTER_BASED:
                    if(eventStatusBuffer[EventId-1].eventId != DEMEVENTPARAMETER_ID_0)
                    {
                        //save the counter in the pointer
                        *FaultDetectionCounter = eventStatusBuffer[EventId-1].faultDetectionCounter  ;
                    }
                    break;
                case DEM_DEBOUNCE_TIME_BASED:
                    break;
                case DEM_DEBOUNCE_MONITORINTERNAL_BASED:
                    if(DemDebounceAlgorithmClass[eventStatusBuffer[EventId-1].EventParamterRef->DemDebounceAlgorithmClass_startingIndex]. \
                            DebounceAlgorithm.DemDebounceMonitorInternal->DemCallbackGetFDCFnc != NULL)
                    {
                        DemDebounceAlgorithmClass[eventStatusBuffer[EventId-1].EventParamterRef->DemDebounceAlgorithmClass_startingIndex]. \
                              DebounceAlgorithm.DemDebounceMonitorInternal->DemCallbackGetFDCFnc (FaultDetectionCounter) ;
                    }

                    break;
                default:
                    break;
                }
           }
        }

    return returnCode ;
} 
/********************************************************************************************/
/**
 *  @brief <b>Dem_ClearDTC</b>
 *   Returns the suppression status of a specific DTC. API Availability:
 *  @param ClientId Unique client id, assigned to the instance of the calling
 *   module
 *  @return <b>E_OK</b>: DTC successfully cleared
 *  @return <b>E_NOT_OK</b>:  No DTC selected
 *  @return <b>DEM_WRONG_DTC</b>: Selected DTC value in selected format does not
 *   exist or clearing is restricted by configuration to group of all DTCs only.
 *   available for the requested event
 *  @return <b>DEM_WRONG_DTCORIGIN</b>: Selected DTCOrigin does not exist
 *  @return <b>DEM_CLEAR_FAILED</b>: DTC clearing failed
 *  @return <b>DEM_CLEAR_BUSY</b>: Another client is currently clearing DTCs.
 *   The requested operation will not be started and the caller shall try again
 *   at a later momen
 *  @return <b>DEM_CLEAR_MEMORY_ERROR</b>: An error occurred during erasing a
 *   memory location (e.g. if DemClearDTCBehavior is set to DEM_CLRRESP_ NON-VOLATILE_FINISH
 *   and erasing of non-volatile-block failed).
 *  @return <b>DEM_PENDING</b>: Clearing the DTCs is currently in progress.
 *   The caller shall call this function again at a later moment.
 *  @return <b>DEM_BUSY</b>: A different Dem_SelectDTC dependent operation according
 *  to SWS_Dem_01253 of this client is currently in progress.
 *  @details
 */
/********************************************************************************************/
Std_ReturnType Dem_ClearDTC( uint8 ClientId )
{
    Std_ReturnType returnCode = E_NOT_OK ;
#if (DEMDEVERRORDETECT == STD_ON)
        if(Dem_ModuleState == MODULE_UN_INTAILIZED)
        {
          //DEM_REPORT_ERROR(DEM_SID_GetStatusOfDTC, DEM_E_UNINIT);
            //TODO /** @brief <b>Dem_ClSSSSearDTC</b> */
        }
        else if (ClientId > DEMCLIENT_SIZE)// from LCfg
        {
            // error
        }
#endif
        else
        {
            Dem_DTCSelectionType DTCSelection;
            Dem_GetDTCSelection(ClientId, &DTCSelection) ;

            /* check if Dem_SelectDTC() was called before calling this API */
            if (DTCSelection.SelectorStatus == DEM_DTC_SELECTOR_NO_REQUEST)
            {
              /* !LINKSTO Dem.ASR431.SWS_Dem_01299,1 */
              // DEM_REPORT_ERROR(DEM_SID_ClearDTC, DEM_E_WRONG_CONDITION);
                returnCode = DEM_E_WRONG_CONDITION ;
            }
            else if((DTCSelection.DTCInfo.DTCOrigin!= DEM_DTC_ORIGIN_PRIMARY_MEMORY) &&
                   (DTCSelection.DTCInfo.DTCOrigin != DEM_DTC_ORIGIN_MIRROR_MEMORY) &&
                   (DTCSelection.DTCInfo.DTCOrigin != DEM_DTC_ORIGIN_PERMANENT_MEMORY) &&
                   (DTCSelection.DTCInfo.DTCOrigin != DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY ))
            {
                returnCode = DEM_WRONG_DTCORIGIN;
            }
            else if ((DTCSelection.DTCInfo.DTCFormat != DEM_DTC_FORMAT_OBD) &&
                      (DTCSelection.DTCInfo.DTCFormat != DEM_DTC_FORMAT_UDS))
            {
                returnCode = DEM_WRONG_DTC;
            }
            else
            {
               if(Dem_ClearDtcStatus.RunState == DEM_CLEARDTC_STATE_PROCESSING_RAM)
               {
                   /* report Result BUSY or pending depending on ClientId which*/
                   if (Dem_ClearDtcStatus.ClientId != ClientId)
                   {
                     /* report Result BUSY */
                       returnCode = DEM_CLEAR_BUSY;
                   }
                   else
                   {
                       if (Dem_ClearDtcStatus.OperationResult != DEM_PENDING)
                       {
                           /* set the RunState back to IDLE */
                           Dem_ClearDtcStatus.RunState = DEM_CLEARDTC_STATE_IDLE;
                           /* reset the ClientId */
                           Dem_ClearDtcStatus.ClientId = DEMEVENTPARAMETER_ID_0;
                       }
                   }
               }
               else
               {
                   if(Dem_ClearDtcStatus.ClientId ==  ClientId)
                   {
                       Dem_ClearDtcStatus.RunState = DEM_CLEARDTC_STATE_PROCESSING_RAM;
                       Dem_ClearDtcStatus.ClientId =  ClientId ;
                       returnCode = DEM_PENDING ;

                       Dem_EventIdType eventId;
                       const DemEventParameter_s *eventParam;
                       uint32 DTC = Dem_DTCSelection[ClientId].DTCInfo.DTC;
                       uint16 i;
                       for(i = 0 ; i< MAXNUNBEROFEVENTS ; i++)
                       {
                           eventId = eventStatusBuffer[i].eventId ;
                           if( eventId != DEMEVENTPARAMETER_ID_0 )
                           {
                               eventParam = eventStatusBuffer[i].EventParamterRef;
                               if(eventParam != NULL)
                               {
                                   //TODO monitor status to cleared dtc [SWS_Dem_01284]
#if(DEMCLEARDTCLIMITATION == DEM_ONLY_CLEAR_ALL_DTCS)
                                   //checl if the DTC is DEM_DTC_GROUP_ALL_DTCS or this event is in the desired dtc
                                   if(checkDtcGroup( DTC, eventParam) == TRUE)
                                   {
                                       //Clear the desired freeze frame
                                       Dem_ClearPrestoredFreezeFrame(eventId);
                                       //check the storage of the Dtc
                                       switch(Dem_DTCSelection[ClientId].DTCInfo.DTCOrigin)
                                       {
                                       case DEM_DTC_ORIGIN_PRIMARY_MEMORY:
                                           //TODO clear DTC's Events
                                           //clear the Event from the primary memory
                                           deleteEventPriMem(eventParam);
                                           //Clear the extended data from the memory
                                           deleteExtendedDataPriMem(eventParam);
                                           //Reset the status of the event from the event status buffer
                                           resetEventStatusRec(eventParam);
                                           //------[SWS_Dem_00573]-------//
#if(DEMTRIGGERMONITORINITBEFORECLEAROK == TRUE)
                                           (DemCallbackInitMForE[eventParam->DemCallbackInitMForE_startingIndex]\
                                                   .DemCallbackInitMForEFnc)( DEM_INIT_MONITOR_CLEAR ) ;
                                           returnCode = E_OK;
                                           /* set the RunState back to IDLE */
                                           Dem_ClearDtcStatus.RunState = DEM_CLEARDTC_STATE_IDLE;
                                           /* reset the ClientId */
                                           Dem_ClearDtcStatus.ClientId = DEM_CLIENT_ID_INVALID;
#endif
                                           returnCode = E_OK;
                                           break;
                                       case DEM_DTC_ORIGIN_PERMANENT_MEMORY:
                                       case DEM_DTC_ORIGIN_MIRROR_MEMORY:
                                           break;
                                       default:
                                           break;

                                       }
                                   }
#endif
                               }
                           }
                       }
                   }
               }
            }
         }
    return returnCode ;
}
/********************************************************************************************/
/**
 *  @brief <b>Dem_DisableDTCS</b>
 *   Disables the DTC setting for all DTCs assigned to the DemEventMemorySet of
 *   the addressed client.
 *  @param ClientId Unique client id, assigned to the instance of the calling
 *  module
 *  @param SuppressionStatus Defines whether the respective DTC is suppressed
 *  (TRUE) or enabled (FALSE).
 *  @return <b>E_OK</b>: Returned next filtered element
 *  @return <b>DEM_PENDING</b>: The requested operation is currently in progress.
 *   The caller shall call this function again at a later moment.
 *  @details
 */
/********************************************************************************************/
Std_ReturnType Dem_DisableDTCSetting( uint8 ClientId ) 
{
        Std_ReturnType returnCode = E_NOT_OK;
    
#if (DEMDEVERRORDETECT == STD_ON)
        if(Dem_ModuleState == MODULE_UN_INTAILIZED)
        {
          //DEM_REPORT_ERROR(DEM_SID_DisableDTCSetting, DEM_E_UNINIT);
        }
        else if (ClientId > DEMCLIENT_SIZE)
        {
           // DEM_REPORT_ERROR(DEM_SID_DisableDTCSetting, DEM_E_WRONG_CONFIGURATION);
        }
        
        else 
#endif
        {

        }

    return returnCode;
}
/********************************************************************************************/
/**
 *  @brief <b>Dem_SetOperationCycleState</b>
 *  Sets an operation cycle state. This API can only be used through the
 *  RTE and therefore no declaration is exported via Dem.h.
 *  The interface has an asynchronous behavior to avoid exceeding of typical
 *  timing requirements on APIs if a large number of events has to be processed
 *  and during the re-initializations of the related monitors. The asynchronous
 *  acknowledgements are the related InitMonitorForEvent callbacks.

 *  @param operationCycleId Identification of operation cycle, like power cycle,driving cycle
 *  @param cycleState New operation cycle state: (re-)start or end
 *  @return Std_ReturnType which is OK or Not-Ok
 *  @return <b>E_OK</b>: get of DTC status mask was successful //TODO
 *  @return <b>E_NOT_OK</b>: get of DTC status mask failed
 *  @see
 *  @details
 */
/********************************************************************************************/
Std_ReturnType Dem_SetOperationCycleState(uint8 operationCycleId, Dem_OperationCycleStateType cycleState)
{
    Std_ReturnType returnCode = E_OK;
#if (DEMDEVERRORDETECT == STD_ON)
    if(Dem_ModuleState == MODULE_UN_INTAILIZED)
    {
      //DEM_REPORT_ERROR(DEM_SID_DisableDTCSetting, DEM_E_UNINIT);
        returnCode = E_NOT_OK;
    }
    else if (operationCycleId > DEMOPERATIONCYCLE_SIZE)
    {
       // DEM_REPORT_ERROR(DEM_SID_DisableDTCSetting, DEM_E_WRONG_CONFIGURATION);
        returnCode = E_NOT_OK;
    }
    else if(cycleState != DEM_CYCLE_STATE_START && cycleState != DEM_CYCLE_STATE_END)
    {
        //DEM_REPORT_ERROR(Dem_SID_SetOperationCycleState, DEM_E_WRONG_CONFIGURATION);
        returnCode = E_NOT_OK;
    }
#endif
    else
    {
        returnCode = setOperationCycleState(operationCycleId, cycleState);
        handleAging(operationCycleId, cycleState);
    }
    return returnCode;
}
/********************************************************************************************/
/**
 *  @brief <b>Dem_shutdown</b>
 *   Shuts down this module..
 *  @details
 */
/********************************************************************************************/
void Dem_Shutdown(void)
{
    setOperationCycleState(DEM_ACTIVE, DEM_CYCLE_STATE_END);
    /* handleAging() should be called behind setOperationCycleState() */
    handleAging(DEM_ACTIVE, DEM_CYCLE_STATE_END);

    Dem_ModuleState = MODULE_UN_INTAILIZED;
}
/********************************************************************************************/
/**
 *  @brief <b>Dem_SetEventAvailable</b>
 *   Set the available status of a specific Event.
 *  @param EventId Identification of an event by assigned EventId.
 *  @param AvailableStatus This parameter specifies whether the respective
 *   Event shall be available (TRUE) or not (FALSE).
 *  @return <b>E_OK</b>: Request to set the availability status was successful.
 *  @return <b>E_NOT_OK</b>: Request to set the availability status not accepted.
 *  @details
 */
/********************************************************************************************/
/* SWS_Dem_01107 */
/*Note: Dem_SetEventAvailable is available before Dem_Init to �pre-configure� the
Dem in advance of the application start. */
#if(DEMAVAILABILITYSUPPORT == DEM_EVENT_AVAILABILITY )
Std_ReturnType  Dem_SetEventAvailable(Dem_EventIdType EventId, boolean AvailableStatus )
{
    Std_ReturnType returnCode = E_NOT_OK;
    Dem_UdsStatusByteType  EventUdsStatusByte_Old ;
    Dem_GetEventUdsStatus(EventId , &EventUdsStatusByte_Old);
#if (DEMDEVERRORDETECT == STD_ON)
        if(Dem_ModuleState == MODULE_UN_INTAILIZED)
        {
          //DEM_REPORT_ERROR(DEM_SID_GetFaultDetectionCounter, DEM_E_UNINIT);
        }
        else if (EventId == DEMEVENTPARAMETER_ID_0) // alot forget it
        {
           // DEM_REPORT_ERROR(DEM_SID_GetFaultDetectionCounter, DEM_E_PARAM_DATA);
        }
        /*else if (EventId > MAXNUNBEROFEVENTS ) // DEM_MAX_EVENTID
        {
           // DEM_REPORT_ERROR(DEM_SID_GetFaultDetectionCounter, DEM_E_WRONG_CONFIGURATION);
        }*/
        else if ( (AvailableStatus != FALSE) &&(AvailableStatus != TRUE) )
        {
          //DEM_REPORT_ERROR(DEM_SID_SetEventAvailable, DEM_E_PARAM_DATA);
        }
#endif
        else if ( Dem_GetEventAvailable(EventId) == AvailableStatus)
        {
            returnCode = E_NOT_OK ;
        }
        else
        {
            if(AvailableStatus == FALSE)
            {
                if( (EventUdsStatusByte_Old & (DEM_UDS_STATUS_TF | DEM_UDS_STATUS_PDTC | DEM_UDS_STATUS_CDTC | DEM_UDS_STATUS_WIR) ) != 0 )
                {
                    returnCode = E_NOT_OK ;
                }
                else
                {
                    //EventStatusRecType *eventStatusRecPtr;
                    //lookupEventStatusRec(EventId, &eventStatusRecPtr);
                    //If Dem_SetEventAvailable is called with AvailableStatus == �false�,
                    //the Dem shall set the UDS status shall be set to 0x00 for this ev
                    eventStatusBuffer[EventId-1].eventStatus = 0x00;
                    /* set the event availability status to FALSE */
                    eventStatusBuffer[EventId-1].EventParamterRef->DemEventAvailable = FALSE ;
                    //CALLBACK
                    /*(DemCallbackEventDataChanged[DemEventParameter[EventId].DemCallbackEventUdsStatusChanged_startingIndex]. \
                            DemCallbackEventUdsStatusChangedFnc) (EventUdsStatusByte_Old , 0x00);*/
                   /* (DemCallbackEventDataChanged[eventStatusRecPtr->EventParamterRef->DemCallbackEventUdsStatusChanged_startingIndex]\
                            .DemCallbackEventDataChangedFnc)(EventId);
                    */

                    returnCode = E_OK;
                }
            }
            else
            {
                //EventStatusRecType *eventStatusRecPtr;
                //lookupEventStatusRec(EventId, &eventStatusRecPtr);
                //If Dem_SetEventAvailable is called with AvailableStatus == �true�,
                //If Dem_SetEventAvailable is called with AvailableStatus == �true�, the Dem s
                eventStatusBuffer[EventId-1].eventStatus = 0x50;
                /* set the event availability status to FALSE */
                eventStatusBuffer[EventId-1].EventParamterRef->DemEventAvailable = TRUE ;
                /* reset debouncing counters for the event */
                eventStatusBuffer[EventId-1].faultDetectionCounter = 0 ;
                /*(DemCallbackEventDataChanged[eventStatusRecPtr->EventParamterRef->DemCallbackEventUdsStatusChanged_startingIndex]\
                        .DemCallbackEventDataChangedFnc)(EventUdsStatusByte_Old , 0x50);*/


               /* (DemCallbackEventDataChanged[eventStatusRecPtr->EventParamterRef->DemCallbackEventUdsStatusChanged_startingIndex]\
                        .DemCallbackEventDataChangedFnc)(EventId);*/

                //If the function Dem_SetEventAvailable is called to
                //set an event to �available�, the Dem shall trigger the event initialization using
                //DEM_INIT_MONITOR_REENABLED as InitMonitorReason.'

                /*(DemCallbackInitMForE[DemEventParameter[EventId].DemCallbackInitMForE_startingIndex] \
                                      .DemCallbackInitMForEFnc )( DEM_INIT_MONITOR_REENABLED ) ;*/

                returnCode = E_OK;
            }
        }
    return returnCode ;
}
#endif
/********************************************************************************************/
/**
 *  @brief <b>Dem_GetDTCStatusAvailabilityMask</b>
 *    Gets the DTC Status availability mask
 *  @param ClientId Unique client id, assigned to the instance of the calling
 *   module.
 *  @param DTCStatusMaskDTCStatusMask The value DTCStatusMask indicates the supported
 *   DTC status bits from the Dem. All supported information is
 *   indicated by setting the corresponding status bit to 1. See ISO14229-1.
 *  @return <b>E_OK</b>: get of DTC status mask was successful
 *  @return <b>E_NOT_OK</b>: get of DTC status mask failed
 *  @details
 */
/********************************************************************************************/
/* Gets the DTC Status availability mask */
 Std_ReturnType Dem_GetDTCStatusAvailabilityMask( uint8 ClientId, Dem_UdsStatusByteType* DTCStatusMask )
 {
    Std_ReturnType returnCode = E_NOT_OK ;
#if (DEMDEVERRORDETECT == STD_ON)
        if(Dem_ModuleState == MODULE_INTAILIZED)
        {
          //DEM_REPORT_ERROR(DEM_SID_GetFaultDetectionCounter, DEM_E_UNINIT);
        }
        else if (ClientId < DEMCLIENT_SIZE ) // DEM_MAX_EVENTID
        {
           // DEM_REPORT_ERROR(DEM_SID_GetFaultDetectionCounter, DEM_E_WRONG_CONFIGURATION);
        }
        else if(DTCStatusMask == NULL)
        {
            // DEM_REPORT_ERROR(DEM_SID_GetFaultDetectionCounter, DEM_E_WRONG_CONFIGURATION);
        }
#endif
        else
        {
            uint16 i ;
            boolean IsFound = FALSE ;
            for( i=0 ; i < DEMCLIENT_SIZE && (IsFound == FALSE); i++)
            {
                if( DemClient[i].DemClientId == ClientId)
                {
                    *DTCStatusMask = DemClient[i].DemEventMemorySetRef_ptr->DemDtcStatusAvailabilityMask;
                    *DTCStatusMask &=   DEM_UDS_STATUS_TF   \
                                | DEM_UDS_STATUS_TFTOC      \
                                | DEM_UDS_STATUS_PDTC       \
                                | DEM_UDS_STATUS_CDTC       \
                                | DEM_UDS_STATUS_TNCSLC     \
                                | DEM_UDS_STATUS_TFSLC      \
                                | DEM_UDS_STATUS_TNCTOC     \
                                | DEM_UDS_STATUS_WIR        ;
                    IsFound = TRUE ;
                }
            }
            returnCode = E_OK ;
        }
     return returnCode ;
 }
 /********************************************************************************************/
 /**
  *  @brief <b>Dem_SelectDTC</b>
  *    Selects a DTC or DTC group as target for further operations.
  *  @param ClientId Unique client id, assigned to the instance of the calling
  *   module.
  *  @param DTC Defines the DTC in respective format that is selected.
  *   If the DTC fits to a DTC group number, the DTC group is selected.
  *  @param DTCFormat Defines the input-format of the provided DTC value.
  *  @param DTCOrigin The event memory of the requested DTC or group of DTC.
  *  @return <b>E_OK</b>: get of DTC status mask was successful
  *  @return <b>E_NOT_OK</b>: get of DTC status mask failed
  *  @details SWS_Dem_91016
  */
 /********************************************************************************************/
 Std_ReturnType Dem_SelectDTC(uint8 ClientId,uint32 DTC,Dem_DTCFormatType DTCFormat,Dem_DTCOriginType DTCOrigin)
 {
     Std_ReturnType returnCode = E_NOT_OK;
 #if (DEMDEVERRORDETECT == STD_ON)
         if(Dem_ModuleState != MODULE_INTAILIZED)
         {
           //DEM_REPORT_ERROR(DEM_SID_GetStatusOfDTC, DEM_E_INIT);
         }
         else if (ClientId > DEMCLIENT_SIZE)
         {
           //DEM_REPORT_ERROR(DEM_SID_SelectDTC, DEM_E_WRONG_CONFIGURATION);
         }
         else if( (DTCFormat != DEM_DTC_FORMAT_OBD) && (DTCFormat != DEM_DTC_FORMAT_UDS)
                 && (DTCFormat != DEM_DTC_FORMAT_J1939) )
         {
           //DEM_REPORT_ERROR(DEM_SID_SelectDTC, DEM_E_PARAM_DATA);
         }
         else if ( (DTCOrigin != DEM_DTC_ORIGIN_PRIMARY_MEMORY) && (DTCOrigin != DEM_DTC_ORIGIN_MIRROR_MEMORY)
                 && (DTCOrigin != DEM_DTC_ORIGIN_PERMANENT_MEMORY) && (DTCOrigin != DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY))
         {
            //DEM_REPORT_ERROR(DEM_SID_SelectDTC, DEM_E_PARAM_DATA);
         }
 #endif
         else
         {
             if( (Dem_DTCSelection[ClientId].DTCInfo.DTC  == DTC) || (Dem_DTCSelection[ClientId].SelectionStatus != DEM_SELECTED_NONE) ||
                     (Dem_DTCSelection[ClientId].DTCInfo.DTCFormat == DTCFormat) || (Dem_DTCSelection[ClientId].DTCInfo.DTCOrigin == DTCOrigin))
             {
                 returnCode = DEM_BUSY ;
             }
             else
             {
                 /* store DTC related information of the client to internal data structure
                  * and invalidate previously cached event Id, if any */
                 Dem_DTCSelection[ClientId].DTCInfo.DTC       = DTC;
                 Dem_DTCSelection[ClientId].DTCInfo.EventId   = DEMEVENTPARAMETER_ID_0;
                 Dem_DTCSelection[ClientId].DTCInfo.DTCOrigin = DTCOrigin;
                 Dem_DTCSelection[ClientId].DTCInfo.DTCFormat = DTCFormat;

                 /* update selector status to indicate a new DTC selection request */
                 Dem_DTCSelection[ClientId].SelectorStatus  = DEM_DTC_SELECTOR_NOT_PROCESSED;
                 Dem_DTCSelection[ClientId].SelectionStatus = DEM_SELECTED_DTC;
                 returnCode = E_OK ;
             }

         }
         return returnCode ;
 }
/********************************************************************************************/
/**
*  @brief <b>Dem_Init</b>
*   Initializes or reinitializes this module.
*  @param ConfigPtr Pointer to the configuration set in VARIANT-POSTBUILD.
*  @details <b>DETAILS IN </b>SWS_Dem_00181 | SWS_Dem_00180 |  SWS_Dem_01326 |   SWS_Dem_00675 |   SWS_Dem_00551 | 
*           SWS_Dem_01324 |   SWS_Dem_ |  
*/
/********************************************************************************************/
void Dem_Init(Dem_ConfigType* ConfigPtr)
{
#if (DEMDEVERRORDETECT == STD_ON)
    if(Dem_ModuleState == MODULE_INTAILIZED)
    {
      //DEM_REPORT_ERROR(DEM_SID_DisableDTCSetting, DEM_E_INIT);
    }
#endif
    else
    {
         DemEventParameter_s *eventParamter ;
         DemEventParameter_s *eventParam;
        /*For all operation cycles with DemOperationCycleAutostart
        set to true Dem_Init shall start the operation cycle
        (identical to Dem_SetOperationCycleState is called with parameter
        DEM_CYCLE_STATE_START) with the exception of executing all callbacks resulting
        from UDS status byte changes.*/
        // Insert all supported events into event status buffer

        //TODO get the freezframe from the NVM and store it in priMemFreezeFrameBuffer
         uint16 FFindex ;
         for(FFindex  = 0 ; FFindex < DEMEVENTPARAMETER_SIZE ; FFindex++ )
         {
             priMemFreezeFrameBuffer[FFindex].eventId = FFindex+1 ;
         }

        //TODO recover Aging from NVRam to RAM

        uint16 index = 0;
        eventParamter = ConfigPtr->EventParameter;
        EventStatusRecType * eventStatusRecPtr;
        while( index < MAXNUNBEROFEVENTS )
        {
            // Find next free position in event status buffer
            lookupEventStatusRec(DEMEVENTPARAMETER_ID_0, &eventStatusRecPtr);
            if(eventStatusRecPtr != NULL)
            {
                eventStatusRecPtr->eventId = eventParamter[index].DemEventId;
                eventStatusRecPtr->EventParamterRef = &eventParamter[index];
            }
            else
            {
                // event status buffer is full
                // DET_REPORTERROR(MODULE_ID_DEM, 0, DEM_PREINIT_ID, DEM_E_EVENT_STATUS_BUFF_FULL);
            }
            index++;
        }
        //For all operation cycles with DemOperationCycleAutostart set to true Dem_Init shall start the operation cycle
        //(identical to Dem_SetOperationCycleState is called with parameter
        //DEM_CYCLE_STATE_START)
        uint16 i ;
        for(i=0 ; i<MAXNUNBEROFEVENTS ; i++)
        {
            if( DemDebounceCounterBasedClass[ConfigPtr->EventParameter[i].DemDebounceAlgorithmClass_startingIndex].DemDebounceCounterStorage == TRUE)
            {
                if(operationCycleStateList[ConfigPtr->EventParameter->DemEventId] == DEM_CYCLE_STATE_START)
                {
                    //Get the counter from the NVM and stor it in the eventStatusRec buffer for that event
                    //TODO added nvm read function in the stub file
                }
            }
        }

        /* Transfer updated event data to event memory */
        for (i = 0; i < MAXNUNBEROFEVENTS; i++)
        {
            if (eventStatusBuffer[i].eventId != DEMEVENTPARAMETER_ID_0)
            {
                checkEventIdExist(eventStatusBuffer[i].eventId, &eventParam);
                storeEventEvtMem(eventParam, &eventStatusBuffer[i]);
            }
        }
        /* Transfer freeze frames to event memory */
        for (i = 0; i < DEMMAXNUMBERPRESTOREDFF; i++)
        {
            if (preInitFreezeFrameBuffer[i].eventId != DEMEVENTPARAMETER_ID_0)
            {
                checkEventIdExist(preInitFreezeFrameBuffer[i].eventId, &eventParam);
                if(eventParam != NULL)
                {
                    storeFreezeFrameDataEvtMem(eventParam, &preInitFreezeFrameBuffer[i]);
                }
            }
        }

        Dem_ModuleState = MODULE_INTAILIZED;
        for (i = 0; i < MAXNUNBEROFEVENTS; i++)
        {
                if(Dem_ErrorQueue[i].EventId != DEMEVENTPARAMETER_ID_0)
                {
                    //check if the eventStatusBuffer index is empty
                    if(eventStatusBuffer[i].eventId == Dem_ErrorQueue[i].EventId)
                    {
                        Dem_SetEventStatus(eventStatusBuffer[i].eventId,  Dem_ErrorQueue[i].Status);
                    }
                }
        }
        // Initializion of operation cycle states..
        for (i = 0; i < DEMOPERATIONCYCLE_SIZE; i++)
        {
            if(operationCycleStateList[i] != DEM_CYCLE_STATE_START)
            {
                operationCycleStateList[i] = DEM_CYCLE_STATE_END;
            }

        }
    }
 }


/********************************************************************************************/
/**
*  @brief <b>Dem_PreInit</b>
*  @details Initializes the internal states necessary to process events reported by BSW-modules.  
*  @details <b>DETAILS IN </b>SWS_Dem_00179 | SWS_Dem_00180 | SWS_Dem_01318 | SWS_Dem_00438 | SWS_Dem_01242 |
*           SWS_Dem_01212 | SWS_Dem_01213 |  SWS_Dem_01289 | 
*/                                                                             
/********************************************************************************************/
void Dem_PreInit(void)
{
        /*The function Dem_PreInit shall initialize the internal states
          of the Dem module necessary to process events and reset debounce counters
          reported by SW-C or BSW modules by using Dem_SetEventStatus and
          Dem_ResetEventDebounceStatus.*/
#if (DEMDEVERRORDETECT == STD_ON)
        if(Dem_ModuleState == MODULE_INTAILIZED)
        {
          //DEM_REPORT_ERROR(DEM_SID_GetStatusOfDTC, DEM_E_INIT);
        }
#endif
        else
        {
            uint16 i, j , queueIdx;
            /* initialize (relative) error-queue pointers */

            /* initialize error-queue ring buffer indexes */
            for (queueIdx = 0 ; queueIdx < DEM_BSW_ERROR_BUFFER_SIZE; ++queueIdx)
            {
              Dem_ErrorQueue[queueIdx].EventId = DEMEVENTPARAMETER_ID_0;
            }
            //const DemEventParameter_s *eventIdParamList;

            // Initialize the event status buffer
            /*The Dem-internal debouncing (counters and timers) shall be
            initialized by calling Dem_PreInit.*/
            for (i = 0; i < MAXNUNBEROFEVENTS; i++)
            {
                eventStatusBuffer[i].eventId = DEMEVENTPARAMETER_ID_0;
                eventStatusBuffer[i].EventParamterRef = NULL;
                eventStatusBuffer[i].faultDetectionCounter = 0;
                eventStatusBuffer[i].maxFaultDetectionCounter = 0;
                eventStatusBuffer[i].occurrence = 0;
                //eventStatusBuffer[i].eventStatus = DEM_UDS_STATUS_TNCTOC | DEM_UDS_STATUS_TNCSLC;
                eventStatusBuffer[i].eventStatus = 0;
                eventStatusBuffer[i].errorStatusChanged = FALSE;
                eventStatusBuffer[i].confirmationCounter = 0;
                priMemEventBuffer[i].eventId = DEMEVENTPARAMETER_ID_0;

            }

            for (i = 0; i < DEMMAXNUMBERPRESTOREDFF; i++)
            {
                preInitFreezeFrameBuffer[i].checksum = 0;
                preInitFreezeFrameBuffer[i].eventId = DEMEVENTPARAMETER_ID_0;
                preInitFreezeFrameBuffer[i].occurrence = 0;
                preInitFreezeFrameBuffer[i].dataSize = 0;

               for (j = 0; j < DEMMAXNUMBERPRESTOREDFF;j++) //TODO FREEZE FRAME DATA SIZE
                {
                    preInitFreezeFrameBuffer[i].data[j] = 0;
                }
            }



                //TODO extended data
        }

        Dem_ModuleState = MODULE_PREINTAILIZED;
}

/********************************************************************************************/
/*                                                                                          */
/********************************************************************************************/
Std_ReturnType Dem_SetDTCFilter(
    uint8 ClientId,
    uint8 DTCStatusMask,Dem_DTCFormatType DTCFormat,
    Dem_DTCOriginType DTCOrigin, boolean FilterWithSeverity,
    Dem_DTCSeverityType DTCSeverityMask, boolean FilterForFaultDetectionCounter )
 {
    Std_ReturnType returnCode = E_NOT_OK;
    uint8 dtcStatusAvailabilityMask;
 #if (DEMDEVERRORDETECT == STD_ON)
  /* check of Dem_InitializationState would be not necessary, but if this API
   * is called before full initialization, the system design is dubious
   * (and Dem_GetNextFilteredDTC[AndFDC]() is then not usable anyway) */
  if (Dem_ModuleState != MODULE_INTAILIZED)
  {
    //DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_UNINIT);
  }
  else if (ClientId > DEMCLIENT_SIZE)
  {
    //DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_WRONG_CONFIGURATION);
  }
  /* Dcm is responsible, that no status masks with unavailable bits are
   * requested (but this would not influence correctness of the filter) */
  /* no check with DEM_IS_UNMASKED_BIT_SET(DTCStatusMask, AVAILABILITY_MASK)
   * done, because all bits are supported */
  else if ( (DTCFormat != DEM_DTC_FORMAT_OBD) &&
            (DTCFormat != DEM_DTC_FORMAT_UDS)
          )
  {
    /* !LINKSTO Dem.ASR431.SetDTCFilter.InvalidDTCFormat,1 */
    //DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_PARAM_DATA);
  }
  else if ( (DTCOrigin > (Dem_DTCOriginType)0x01FFU) ||
               ( (DTCOrigin < (Dem_DTCOriginType)0x0100U) &&
              (DTCOrigin != DEM_DTC_ORIGIN_PRIMARY_MEMORY) &&
              (DTCOrigin != DEM_DTC_ORIGIN_MIRROR_MEMORY) &&
              (DTCOrigin != DEM_DTC_ORIGIN_PERMANENT_MEMORY) &&
              (DTCOrigin != DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY)
            )
          )
  {
    /* !LINKSTO Dem.ASR431.SWS_Dem_01264,1 */
    //DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_PARAM_DATA);
  }
  else if ( (FilterWithSeverity != TRUE) &&
            (FilterWithSeverity != FALSE)
          )
  {
    //DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_PARAM_DATA);
  }
  /*else if ( (DTCSeverityMask != DEM_SEVERITY_NO_SEVERITY) &&
            (DEM_IS_UNMASKED_BIT_SET(DTCSeverityMask,
               DEM_SEVERITY_MAINTENANCE_ONLY |
               DEM_SEVERITY_CHECK_AT_NEXT_HALT |
               DEM_SEVERITY_CHECK_IMMEDIATELY) )
          )
  {
    //DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_PARAM_DATA);
  }*/
  else if ( (FilterForFaultDetectionCounter != TRUE) &&
            (FilterForFaultDetectionCounter != FALSE)
          )
  {
    //DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_PARAM_DATA);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
     {
        Dem_GetDTCStatusAvailabilityMask(ClientId , &dtcStatusAvailabilityMask);
        // Yes all parameters correct, set the new filters.  /** @req DEM057 */
        dtcFilter.dtcStatusMask = DTCStatusMask & dtcStatusAvailabilityMask;
        dtcFilter.dtcKind = DEM_DTC_KIND_ALL_DTCS;
        dtcFilter.dtcOrigin = DTCOrigin;
        dtcFilter.DTCFormat    = DTCFormat;
        dtcFilter.filterWithSeverity = FilterWithSeverity;
        dtcFilter.dtcSeverityMask = DTCSeverityMask;
        dtcFilter.filterForFaultDetectionCounter = FilterForFaultDetectionCounter;
        dtcFilter.faultIndex = DEMEVENTPARAMETER_SIZE;
    }
    return returnCode;
 }

/*****************************************************************************************************/
/* Procedure:   Dem_GetNumberOfFilteredDtc                                                           */
/* Reentrant:   No                                                                                   */
/*****************************************************************************************************/
Std_ReturnType Dem_GetNumberOfFilteredDtc(uint8 ClientId,uint16 *numberOfFilteredDTC)
{
    uint16 i;
    uint16 numberOfFaults = 0;
    Std_ReturnType returnCode = E_NOT_OK;

    if (Dem_ModuleState == MODULE_INTAILIZED)
    {
        //Dem_DisableEventStatusUpdate();

        for (i = 0; i < DEMEVENTPARAMETER_SIZE; i++)
        {
            if (eventStatusBuffer[i].eventId != DEMEVENTPARAMETER_ID_0)
            {
                if (matchEventWithDtcFilter(&eventStatusBuffer[i], ClientId))
                {
                        numberOfFaults++;
                        returnCode = E_OK;
                }
            }
        }

        //Dem_EnableEventStatusUpdate();

        *numberOfFilteredDTC = numberOfFaults; /** @req DEM061 */
    } else {
       // DET_REPORTERROR(MODULE_ID_DEM, 0, DEM_GETNUMBEROFFILTEREDDTC_ID, DEM_E_UNINIT);
        returnCode = E_NOT_OK;
    }
    return returnCode;
}


/********************************************************************************************/
/* Procedure:   Dem_GetNextFilteredDTC                                                      */
/* Reentrant:   No                                                                          */
/********************************************************************************************/
Std_ReturnType Dem_GetNextFilteredDTC(uint8 ClientId, uint32 *dtc, uint8 *dtcStatus)
{
    Std_ReturnType returnCode = E_NOT_OK;
    boolean dtcFound = FALSE;

    if (Dem_ModuleState == MODULE_INTAILIZED)
    {
        // TODO: This job should be done in an more advanced way according to Dem217
        while ((!dtcFound) && (dtcFilter.faultIndex != 0))
        {
            dtcFilter.faultIndex--;
            if (eventStatusBuffer[dtcFilter.faultIndex].eventId != DEMEVENTPARAMETER_ID_0)
            {
                if (matchEventWithDtcFilter(&eventStatusBuffer[dtcFilter.faultIndex] , ClientId))
                {
                    if (eventStatusBuffer[dtcFilter.faultIndex].EventParamterRef->DemDTCRef_ptr != NULL)
                    {
                        *dtc = eventStatusBuffer[dtcFilter.faultIndex].EventParamterRef->DemDTCRef_ptr; /** @req DEM216 */
                        *dtcStatus = eventStatusBuffer[dtcFilter.faultIndex].eventStatus;
                         dtcFound = TRUE;
                        returnCode = E_OK;
                    }
                }
            }
        }

        if (!dtcFound)
        {
            dtcFilter.faultIndex = DEMEVENTPARAMETER_SIZE;
            returnCode = E_NOT_OK;
        }
    } else
    {
        //DET_REPORTERROR(MODULE_ID_DEM, 0, DEM_GETNEXTFILTEREDDTC_ID, DEM_E_UNINIT);
        returnCode = E_NOT_OK;
    }

    return returnCode;
}

/********************************************************************************************/
/* Service name:                                                                            */
/* Parameters (in):                                                                         */
/* Parameters (inout):                                                                      */
/* Parameters (out):                                                                        */
/* Description:                                                                             */
/********************************************************************************************/
Std_ReturnType Dem_GetSeverityOfDTC(uint8 ClientId,Dem_DTCSeverityType* DTCSeverity)
{
    Std_ReturnType Return_code = E_NOT_OK ;
#if (DEMDEVERRORDETECT == STD_ON)
 /* check of Dem_InitializationState would be not necessary, but if this API
  * is called before full initialization, the system design is dubious
  * (and Dem_GetNextFilteredDTC[AndFDC]() is then not usable anyway) */
  if (Dem_ModuleState != MODULE_INTAILIZED)
  {
   //DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_UNINIT);
  }
  else if (ClientId > DEMCLIENT_SIZE)
  {
   //DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_WRONG_CONFIGURATION);
  }
  else if (DTCSeverity == NULL)
  {
      //DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_WRONG_CONFIGURATION);
  }
  else
#endif
  {
      uint16 Evntid ;
      checkDtc(ClientId) ;
      uint16 i =  0  ;
      const uint32 Dtc = Dem_DTCSelection[ClientId].DTCInfo.DTC ;

      if(   Dem_DTCSelection[ClientId].SelectorStatus != DEM_DTC_SELECTOR_WRONG_DTC
         && Dem_DTCSelection[ClientId].SelectorStatus != DEM_DTC_SELECTOR_WRONG_DTC_ORIGIN)
      {
          if(Dem_DTCSelection[ClientId].DTCInfo.EventId != DEMEVENTPARAMETER_ID_0 )
          {
              Evntid = Dem_DTCSelection[ClientId].DTCInfo.EventId  ;

          }
          else
          {

              for (i = 0; i < DEMEVENTPARAMETER_SIZE; i++)
              {
                  if (Dtc == eventStatusBuffer[i].EventParamterRef->DemDTCRef_ptr->DemDtcValue )
                  {
                      Dem_DTCSelection[ClientId].DTCInfo.EventId = eventStatusBuffer[i].eventId  ;
                      break ;
                  }
              }
          }
          * DTCSeverity = eventStatusBuffer[i].EventParamterRef->DemDTCRef_ptr->DemDTCSeverity ;
          Return_code = E_OK ;
      }
  }

    return Return_code ;
}

/********************************************************************************************/
/* Service name:                                                                            */
/* Parameters (in):                                                                         */
/* Parameters (inout):                                                                      */
/* Parameters (out):                                                                        */
/* Description:                                                                             */
/********************************************************************************************/
Std_ReturnType Dem_GetFunctionalUnitOfDTC(uint8 ClientId,uint8* DTCFunctionalUnit)
{
    Std_ReturnType Return_code = E_NOT_OK ;
    #if (DEMDEVERRORDETECT == STD_ON)
     /* check of Dem_InitializationState would be not necessary, but if this API
      * is called before full initialization, the system design is dubious
      * (and Dem_GetNextFilteredDTC[AndFDC]() is then not usable anyway) */
      if (Dem_ModuleState != MODULE_INTAILIZED)
      {
       //DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_UNINIT);
      }
      else if (ClientId > DEMCLIENT_SIZE)
      {
       //DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_WRONG_CONFIGURATION);
      }
      else if (DTCFunctionalUnit == NULL)
      {
          //DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_WRONG_CONFIGURATION);
      }
      else
    #endif
      {
          uint16 Evntid ;
          checkDtc(ClientId) ;
          uint16 i  ;
          const uint32 dtc = Dem_DTCSelection[ClientId].DTCInfo.DTC ;

          if(   Dem_DTCSelection[ClientId].SelectorStatus != DEM_DTC_SELECTOR_WRONG_DTC
             && Dem_DTCSelection[ClientId].SelectorStatus != DEM_DTC_SELECTOR_WRONG_DTC_ORIGIN)
          {
              if(Dem_DTCSelection[ClientId].DTCInfo.EventId != DEMEVENTPARAMETER_ID_0 )
              {
                  Evntid = Dem_DTCSelection[ClientId].DTCInfo.EventId  ;

              }
              else
              {
                  for (i = 0; i < DEMEVENTPARAMETER_SIZE; i++)
                  {
                      if (dtc == eventStatusBuffer[i].EventParamterRef->DemDTCRef_ptr->DemDtcValue )
                      {
                          Dem_DTCSelection[ClientId].DTCInfo.EventId = eventStatusBuffer[i].eventId  ;
                          break ;
                      }
                  }
              }
              * DTCFunctionalUnit = eventStatusBuffer[i].EventParamterRef->DemDTCRef_ptr->DemDTCFunctionalUnit ;
              Return_code = E_OK ;
          }
      }
     return Return_code ;
}

/********************************************************************************************/
/* Service name:                                                                            */
/* Parameters (in):                                                                         */
/* Parameters (inout):                                                                      */
/* Parameters (out):                                                                        */
/* Description:                                                                             */
/********************************************************************************************/
Std_ReturnType Dem_PrestoreFreezeFrame(Dem_EventIdType EventId)
{
    Std_ReturnType Result = E_NOT_OK;

#if (DEMDEVERRORDETECT == STD_ON)
 /* check of Dem_InitializationState would be not necessary, but if this API
  * is called before full initialization, the system design is dubious
  * (and Dem_GetNextFilteredDTC[AndFDC]() is then not usable anyway) */
  if (Dem_ModuleState != MODULE_INTAILIZED)
  {
     //DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_UNINIT);
  }
  else if (EventId > DEMEVENTPARAMETER_SIZE)
  {
      // DEM_REPORT_ERROR(DEM_SID_PrestoreFreezeFrame, DEM_E_WRONG_CONFIGURATION);
  }
  else if(eventStatusBuffer[EventId].EventParamterRef->DemFFPrestorageSupported == FALSE)
  {
      //DEM_REPORT_ERROR(DEM_SID_PrestoreFreezeFrame, DEM_E_WRONG_CONFIGURATION);
  }
  else if (Dem_GetEventAvailable(EventId) == FALSE)
  {
      uint16 EvId ;
      uint16 Index = 0 ;
      /* check if there are PFFs in front of the target PFF */
      for (EvId = 0U; EvId < EventId; ++EvId)
      {
        if (eventStatusBuffer[EvId].EventParamterRef->DemFFPrestorageSupported == TRUE)
        {
          ++Index;

        }
      }
  }
  else
#endif
  {
#if (DEMMAXNUMBERPRESTOREDFF > 0 )
      uint8 storIndex = 0 ;
      //store the ID from the configuration
      priMemFreezeFrameBuffer[EventId].data[storIndex] = (eventStatusBuffer[EventId].EventParamterRef->DemDTCRef_ptr->DemDTCAttributesRef_ptr->DemFreezeFrameClassRef_ptr->
              DemDidClassRef_ptr->DemDidIdentifier >>8)& 0xFF ;
      storIndex++;
      priMemFreezeFrameBuffer[EventId].data[storIndex] = (eventStatusBuffer[EventId].EventParamterRef->DemDTCRef_ptr->DemDTCAttributesRef_ptr->DemFreezeFrameClassRef_ptr->
              DemDidClassRef_ptr->DemDidIdentifier )& 0xFF ;
      storIndex++;
      //get the data of the freezframe from the SWC
      eventStatusBuffer[EventId].EventParamterRef->DemDTCRef_ptr->DemDTCAttributesRef_ptr->DemFreezeFrameClassRef_ptr->
      DemDidClassRef_ptr->DemDidDataElementClassRef_ptr->DemExternalSRDataElementClass(&(priMemFreezeFrameBuffer[EventId].data[storIndex]));

#endif
  }

return Result ;
}
/********************************************************************************************/
/* Service name:                                                                            */
/* Parameters (in):                                                                         */
/* Parameters (inout):                                                                      */
/* Parameters (out):                                                                        */
/* Description:                                                                             */
/********************************************************************************************/

Std_ReturnType Dem_GetNextFilteredDTCAndSeverity(uint8 ClientId,uint32* DTC,uint8* DTCStatus,Dem_DTCSeverityType* DTCSeverity,uint8* DTCFunctionalUnit)
{
    Std_ReturnType Return_code = E_NOT_OK ;
#if (DEMDEVERRORDETECT == STD_ON)
 /* check of Dem_InitializationState would be not necessary, but if this API
  * is called before full initialization, the system design is dubious
  * (and Dem_GetNextFilteredDTC[AndFDC]() is then not usable anyway) */
  if (Dem_ModuleState != MODULE_INTAILIZED)
  {
   //DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_UNINIT);
  }
  else if (ClientId > DEMCLIENT_SIZE)
  {
   //DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_WRONG_CONFIGURATION);
  }
  else if (DTCSeverity == NULL)
  {
      //DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_WRONG_CONFIGURATION);
  }
  else if (DTC == NULL)
  {
      //DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_WRONG_CONFIGURATION);
  }
  else if (DTCStatus == NULL)
  {
      //DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_WRONG_CONFIGURATION);
  }
  else if (DTCFunctionalUnit == NULL)
  {
      //DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_WRONG_CONFIGURATION);
  }
  else
#endif
  {

  }
  return Return_code ;
}


/********************************************************************************************/
/* Service name:                                                                            */
/* Parameters (in):                                                                         */
/* Parameters (inout):                                                                      */
/* Parameters (out):                                                                        */
/* Description:                                                                             */
/********************************************************************************************/
DemTypeOfDTCSupported_Emun Dem_GetTranslationType(uint8 ClientId)
{
#if (DEMDEVERRORDETECT == STD_ON)
 /* check of Dem_InitializationState would be not necessary, but if this API
  * is called before full initialization, the system design is dubious
  * (and Dem_GetNextFilteredDTC[AndFDC]() is then not usable anyway) */
  if (Dem_ModuleState != MODULE_INTAILIZED)
  {
   //DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_UNINIT);
  }
  else if (ClientId > DEMCLIENT_SIZE)
  {
   //DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_WRONG_CONFIGURATION);
  }
#endif
  DemTypeOfDTCSupported_Emun TranslationType  = DemClient[ClientId].DemEventMemorySetRef_ptr->DemTypeOfDTCSupported ;
  return TranslationType ;
}
/********************************************************************************************/
/* Service name:                                                                            */
/* Parameters (in):                                                                         */
/* Parameters (inout):                                                                      */
/* Parameters (out):                                                                        */
/* Description:                                                                             */
/********************************************************************************************/
 void Dem_MainFunction(void)
 {
     if(AgingIsModified)
     {
         storeAgingRecPerMem(BlockId);
     }
 }

 /*void Get_EventsData(EventInfo *des_buffer)
 {
     uint8 i ;
     for( i = 0 ; i<MAXNUNBEROFEVENTS ; i++)
     {
         if(priMemEventBuffer[i].eventId != DEMEVENTPARAMETER_ID_0 )
         {
             des_buffer[i].DemEventId         = priMemEventBuffer[i].eventId ;
             if(eventStatusBuffer[priMemEventBuffer[i].eventId -1].EventParamterRef->DemDTCRef_ptr == NULL)
             {
                 des_buffer[i].DemDtcValue        = 0;
             }
             else
             {
                 des_buffer[i].DemDtcValue        = eventStatusBuffer[priMemEventBuffer[i].eventId -1].EventParamterRef->DemDTCRef_ptr->DemDtcValue;
             }
             des_buffer[i].DemEventAvailable  = eventStatusBuffer[priMemEventBuffer[i].eventId -1].EventParamterRef->DemEventAvailable ;
             des_buffer[i].errorStatusChanged = eventStatusBuffer[priMemEventBuffer[i].eventId -1].errorStatusChanged ;
             des_buffer[i].occurrence         = eventStatusBuffer[priMemEventBuffer[i].eventId -1].occurrence ;
             des_buffer[i].eventStatus        = eventStatusBuffer[priMemEventBuffer[i].eventId -1].eventStatus;
         }
     }

 }


 Std_ReturnType Get_DtcEvents(EventInfo *des_buffer , uint32 Dtc)
 {
     Std_ReturnType Result = E_NOT_OK ;
     uint8 i ;
     for( i = 0 ; i<MAXNUNBEROFEVENTS ; i++)
     {
         if(priMemEventBuffer[i].eventId != DEMEVENTPARAMETER_ID_0 )
         {
             if( eventStatusBuffer[priMemEventBuffer[i].eventId -1].EventParamterRef->DemDTCRef_ptr->DemDtcValue ==  Dtc && \
                     Dtc != NULL)
             {
                 des_buffer[i].DemEventId         = priMemEventBuffer[i].eventId ;
                 des_buffer[i].DemDtcValue        = eventStatusBuffer[priMemEventBuffer[i].eventId -1].EventParamterRef->DemDTCRef_ptr->DemDtcValue;
                 des_buffer[i].DemEventAvailable  = eventStatusBuffer[priMemEventBuffer[i].eventId -1].EventParamterRef->DemEventAvailable ;
                 des_buffer[i].errorStatusChanged = eventStatusBuffer[priMemEventBuffer[i].eventId -1].errorStatusChanged ;
                 des_buffer[i].occurrence         = eventStatusBuffer[priMemEventBuffer[i].eventId -1].occurrence ;
                 des_buffer[i].eventStatus        = eventStatusBuffer[priMemEventBuffer[i].eventId -1].eventStatus;
                 Result = E_OK ;

             }
         }
     }

   return Result ;
}
*/
