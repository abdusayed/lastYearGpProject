
#ifndef DEM_TYPES_H_
#define DEM_TYPES_H_



#include "Rte_Dem_Type.h"
typedef uint8  boolean ;

typedef uint8 Std_ReturnType;
#define E_OK                    (Std_ReturnType)0
#define E_NOT_OK                (Std_ReturnType)1
#define DEM_PENDING             (Std_ReturnType)4
#define DEM_CLEAR_BUSY          (Std_ReturnType)5
#define DEM_CLEAR_MEMORY_ERROR  (Std_ReturnType)6
#define DEM_CLEAR_FAILED        (Std_ReturnType)7
#define DEM_WRONG_DTC           (Std_ReturnType)8
#define DEM_WRONG_DTCORIGIN     (Std_ReturnType)9
#define DEM_E_NO_DTC_AVAILABLE  (Std_ReturnType)10
#define DEM_BUSY                (Std_ReturnType)22
/*
#define E_NO_DTC_AVAILABLE      (Std_ReturnType)2
#define E_SESSION_NOT_ALLOWED   (Std_ReturnType)4
#define E_PROTOCOL_NOT_ALLOWED  (Std_ReturnType)5
#define E_REQUEST_NOT_ACCEPTED  (Std_ReturnType)8 */


typedef uint32 Dem_DTCType;


/***************************call backs********************************/
typedef Std_ReturnType (*Dem_CallbackDemTriggerOnMonitorStatus_cb)(void) ;
typedef Std_ReturnType (*DemCallbackDTCStatusChangedFnc_cb)(Dem_UdsStatusByteType DTCStatusOld , Dem_UdsStatusByteType DTCStatusNew);
typedef Std_ReturnType (*Dem_ClearDtcNotification_cb) (uint32 DTC, Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin) ;
//typedef Std_ReturnType (*DemCallbackDTCStatusChangedFnc_cb) (uint32 DTC, Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin) ;
typedef Std_ReturnType (*Dem_CallbackClearEventAllowed_cb) (boolean* Allowed);
typedef Std_ReturnType (*DemCallbackEventDataChangedFnc_cb) (Dem_EventIdType EventId) ;
typedef Std_ReturnType (*DemCallbackEventUdsStatusChangedFnc_cb) \
        (Dem_UdsStatusByteType EventStatusByteOld , Dem_UdsStatusByteType EventStatusByteNew);
typedef Std_ReturnType (*DemCallbackInitMForEFnc_cb)(Dem_InitMonitorReasonType InitMonitorReason);
typedef Std_ReturnType (*DemCallbackMonitorStatusChangedFnc_cb)(void);
typedef Std_ReturnType (*DemCallbackGetFDCFnc_cb)(sint8*FaultDetectionCounter);
typedef Std_ReturnType (*DemComponentFailedCallbackFnc_cb )(boolean ComponentFailedStatus);  /////319
typedef Std_ReturnType (*DemDataElementReadFnc_cb)(Dem_MonitorDataType monitorData0 ,uint8* Buffer);



/***************************************************************************/
/* Defines the clearing process of diagnostic information for volatile and */
/* non-volatile memory and the positive response handling for the Dcm      */
/* module.                                                                 */
/***************************************************************************/
typedef uint8 DemClearDTCBehavior_Enum;
/***************************************************************************/
/* Defines the supported Dem_<...>ClearDTC API scope                       */
/***************************************************************************/
typedef uint8 DemClearDTCLimitation_Enum ;
/***************************************************************************/
/* Defines the default endianness of the data belonging to a data element  */
/* which is applicable if the DemExternalSRDataElementClass does not       */
/* define a endianness.                                                    */
/***************************************************************************/
typedef uint8 DemDataElementDefaultEndianness_Enum ;
/***************************************************************************/
/* This parameter defines the type of event combination supported by the   */
/* Dem.                                                                    */
/***************************************************************************/
typedef uint8 DemEventCombinationSupport_Enum ;
/***************************************************************************/
/*This configuration switch defines OBD support and kind of OBD ECU.       */
/***************************************************************************/
typedef uint8 DemOBDSupport_Enum;
/***************************************************************************/
/* This configuration switch defines, whether the aging and displacement   */
/* mechanism shall be applied to the "TestFailedSinceLastClear" status     */
/* bits.                                                                   */
/***************************************************************************/
typedef uint8 DemStatusBitHandlingTestFailedSinceLastClear_Emun;
/***************************************************************************/
/* This configuration switch defines, whether support for suppression is   */
/* enabled or not                                                          */
/***************************************************************************/
typedef uint8 DemSuppressionSupport_Enum ;
/***************************************************************************/
/* Functionality provided by Dem for the DemClient.                        */
/***************************************************************************/
typedef uint8 DemClientFunctionality_Enum;
/* The Dem provides only the client related functionality EvMemOverflowIndication for this
 * client Id. Other functionality like DTCFilter or Clear is not allowed to be used by this
 * client.*/
#define CLIENT_ONLY_USES_EVENTOVERFLOW_INTERFACE (DemClientFunctionality_Enum)0
/*The Dem provides all client related functionality for the selected client
 *  (e.g.clear APIs and overflow indications).*/
#define CLIENT_USES_FULL_FUNCTIONALITY           (DemClientFunctionality_Enum)1

/***************************************************************************/
/* This parameter defines the format returned by                           */
/* Dem_GetTranslationType and does not relate to/influence the             */
/* supported Dem functionality                                             */
/***************************************************************************/
typedef uint8 DemTypeOfDTCSupported_Emun;
/***************************************************************************/
/* Configure, whether the callback shall be called on start of a clear or  */
/* after finishing a clear DTC operation (refer to                         */
/* <Module>_ClearDtcNotification)                                          */
/***************************************************************************/
typedef uint8 DemClearDtcNotificationTime_Enum ;
/***************************************************************************/
/* This configuration switch defines, whether support for event            */
/* displacement is enabled or not, and which displacement strategy is      */
/* followed.                                                               */
/***************************************************************************/
typedef uint8 DemEventDisplacementStrategy_Enum;
/***************************************************************************/
/* DemEnvironmentDataCapture defines the point in time, when the data      */
/* actually is captured.                                                   */
/***************************************************************************/
typedef uint8 DemEnvironmentDataCapture_Enum;
/***************************************************************************/
/* Configures the primary trigger to allocate an event memory entry.       */
/***************************************************************************/
typedef uint8 DemEventMemoryEntryStorageTrigger_Enum;
/***************************************************************************/
/* This configuration switch defines the consideration of the fault        */
/* confirmation process for the occurrence counter. For OBD and mixed      */
/* systems (OBD/non OBD, refer to DemOBDSupport) configuration             */
/* switch shall always set to DEM_PROCESS_OCCCTR_TF.                       */
/***************************************************************************/
typedef uint8 DemOccurrenceCounterProcessing_Enum;
/***************************************************************************/
/* This parameter defines the type of assigning freeze frame record        */
/* numbers for event-specific freeze frame records.                        */
/***************************************************************************/
typedef uint8 DemTypeOfFreezeFrameRecordNumeration_Enum;
/***************************************************************************/
/* Defines the trigger to store the ExtendedDataRecord.                    */
/***************************************************************************/
typedef uint8 DemExtendedDataRecordTrigger_Enum;
/***************************************************************************/
/* This extended data record is captured if the configured trigger         */
/* condition in "DemExtendedDataRecordTrigger" is fulfilled.               */
/***************************************************************************/
typedef uint8 DemExtendedDataRecordUpdate_Enum;
/***************************************************************************/
/* Defines the trigger to store the FreezeFrameRecord.                     */
/***************************************************************************/
typedef uint8 DemFreezeFrameRecordTrigger_Enum;
/***************************************************************************/
/* This parameter defines the case, when the freeze frame record is        */
/*   stored/updated                                                        */
/***************************************************************************/
typedef uint8 DemFreezeFrameRecordUpdate_Enum;
/***************************************************************************/
/* Switch to provide either Gasoline or Diesel parameters.                 */
/***************************************************************************/
typedef uint8 DemOBDEngineType_Enum;
/***************************************************************************/
/*This parameter specifies the assigned denominator type which is          */
/*applied in addition to the                                               */
/*DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR conditions                      */
/***************************************************************************/
typedef uint8 DemIUMPRDenGroup_Enum;
/***************************************************************************/
/* This parameter specifies the assigned IUMPR group of the ratio Id.      */
/***************************************************************************/
typedef uint8 DemIUMPRGroup_Enum;
/***************************************************************************/
/*  This parameter defines whether the ratio will be calculated API or     */
/*  observer based                                                         */
/***************************************************************************/
typedef uint8 DemRatioKind_Enum;
/***************************************************************************/
/*  DTC severity according to ISO 14229-1. This parameter depends on       */
/*  the automotive manufacturer                                            */
/***************************************************************************/
typedef uint8 DemDTCSeverity_Enum;
/***************************************************************************/
/* This parameter defines when a specific event memory entry is allowed    */
/*  to be stored in the NVRAM.                                             */
/***************************************************************************/
typedef uint8 DemNvStorageStrategy_Enum;
/***************************************************************************/
/* DTC Class according to ISO 14229-1 [2013 version]. This parameter         */
/* depends on the automotive manufacturer. If it is not configured, the      */
/* value is marked as �unclassified�. If this parameter is configured for no */
/* DTC, the Dem provides no DTC WWHOBD class information.                    */
/***************************************************************************/
typedef uint8 DemWWHOBDDTCClass_Enum ;
/***************************************************************************/
/* Significance of the event, which indicates additional information
    concerning fault classification and resolution                         */
/***************************************************************************/
typedef uint8 DemDTCSignificance_Enum ;
/******************************************************************************/
/*This parameter defines how the event debounce algorithm will behave,        */
/*if a related enable condition is not fulfilled or ControlDTCSetting of the  */
/*related event is disabled.                                                  */
/******************************************************************************/
typedef uint8 DemDebounceBehavior_Enum;
/******************************************************************************/
/*Update conditions applied by the Dem to reports of DTR values. Only         */
/*supported if a related Event is configured                                  */
/*DEM_DTR_UPDATE_ALWAYS :Any DTR result reported by the monitor               */
/*is used by the Dem.                                                         */
/*DEM_DTR_UPDATE_STEADY :The Dem accepts reported DTRs only                   */
/*when the configured debouncingmechanism is stable at the FAIL or            */
/*PASS limit                                                                  */
/******************************************************************************/
typedef uint8 DemDtrUpdateKind_Enum;
/***************************************************************************/
/*  This parameter is used to distinguish between SW-C and BSW events.     */
/***************************************************************************/
typedef uint8 DemEventKind_Enum;
/***************************************************************************/
/*  Indicates the reporting behavior of the BSW Module (DemEventKind
        == DEM_EVENT_KIND_BSW) in order to determine the size of the
        reporting queue.                                                   */
/***************************************************************************/
typedef uint8 DemReportBehavior_Enum;
/***************************************************************************/
/*  Defines the resulting UDS status byte for the related event, which must
    not be cleared according to the ClearEventAllowed callback              */
/***************************************************************************/
typedef uint8 DemClearEventAllowedBehavior_Enum;
/***************************************************************************/
/*Provide the implementation data type of this C/S data element.           */
/***************************************************************************/
typedef uint8 DemDataElementDataType_Enum;
/***************************************************************************/
/* Defines the endianness of the data belonging to an external data.       */
/* If no DemDataElementEndianness is defined the value of                  */
/* DemDataElementDefaultEndianness is applicable.                          */
/***************************************************************************/
typedef uint8 DemDataElementEndianness_Enum;
/***************************************************************************/
/*This parameter defines the Dem-internal data value, which is mapped      */
/*to the data element.                                                     */
/***************************************************************************/
typedef uint8 DemInternalDataElement_Enum;
/***************************************************************************/
/* monitor status values.                                                  */
/***************************************************************************/
typedef uint8 Dem_MonitorStatusType;
#define DEM_MONITOR_STATUS_TF     (Dem_MonitorStatusType)0
#define DEM_MONITOR_STATUS_TNCTOC (Dem_MonitorStatusType)1

/***************************************************************************/
/*                                                                         */
/***************************************************************************/
typedef uint8 DemEventOBDReadinessGroup_enum;
/***************************************************************************/
/* This type contains operation cycle state values, which can be           */
/* reported via Dem_SetOperationCycleState()                               */
/* Dem_GetOperationCycleState().                                           */
/***************************************************************************/
typedef uint8 Dem_OperationCycleStateType;
#define DEM_CYCLE_STATE_START   (Dem_OperationCycleStateType)1
#define DEM_CYCLE_STATE_END     (Dem_OperationCycleStateType)2

/***************************************************************************/
/*                           Dem_DTCGroupType                              */
/***************************************************************************/
typedef uint32 Dem_DTCGroupType;
#define DEM_DTC_GROUP_ALL_DTCS          (Dem_DTCGroupType)0xffffff

/***************************************************************************/
/*                           Dem status type                               */
/***************************************************************************/
#define DEM_DTC_STATUS_MASK_ALL         (uint8)0x00

/***************************************************************************/
/*           This type is used to filter DTCs for their kind.              */
/***************************************************************************/
typedef uint8 Dem_DTCKindType;
#define DEM_DTC_KIND_ALL_DTCS           (Dem_DTCKindType)0x01
#define DEM_DTC_KIND_EMISSION_REL_DTCS  (Dem_DTCKindType)0x02

typedef uint8 Dem_FreezeFrameKindType;
#define DEM_J1939DCM_FREEZEFRAME                  (Dem_FreezeFrameKindType)0U
#define DEM_J1939DCM_SPNS_IN_EXPANDED_FREEZEFRAME (Dem_FreezeFrameKindType)2U


/*----------------[Dem_DTCSeverityType]-------------------------------------*/

/** \brief Defines the type of a DTCSeverityMask according to ISO14229-1. */
typedef uint8 Dem_DTCSeverityType;

#if (defined DEM_SEVERITY_NO_SEVERITY)
#error DEM_SEVERITY_NO_SEVERITY already defined
#endif
/** \brief No severity information available */
#define DEM_SEVERITY_NO_SEVERITY                  0x00U

#if (defined DEM_SEVERITY_WWHOBD_CLASS_NO_CLASS)
#error DEM_SEVERITY_WWHOBD_CLASS_NO_CLASS already defined
#endif
/** \brief No class information */
#define DEM_SEVERITY_WWHOBD_CLASS_NO_CLASS        0x01U

#if (defined DEM_SEVERITY_WWHOBD_CLASS_A)
#error DEM_SEVERITY_WWHOBD_CLASS_A already defined
#endif
/** \brief WWH-OBD Class A */
#define DEM_SEVERITY_WWHOBD_CLASS_A               0x02U

#if (defined DEM_SEVERITY_WWHOBD_CLASS_B1)
#error DEM_SEVERITY_WWHOBD_CLASS_B1 already defined
#endif
/** \brief WWH-OBD Class B1 */
#define DEM_SEVERITY_WWHOBD_CLASS_B1              0x04U

#if (defined DEM_SEVERITY_WWHOBD_CLASS_B2)
#error DEM_SEVERITY_WWHOBD_CLASS_B2 already defined
#endif
/** \brief WWH-OBD Class B2 */
#define DEM_SEVERITY_WWHOBD_CLASS_B2              0x08U

#if (defined DEM_SEVERITY_WWHOBD_CLASS_C)
#error DEM_SEVERITY_WWHOBD_CLASS_C already defined
#endif
/** \brief WWH-OBD Class C */
#define DEM_SEVERITY_WWHOBD_CLASS_C               0x10U

#if (defined DEM_SEVERITY_MAINTENANCE_ONLY)
#error DEM_SEVERITY_MAINTENANCE_ONLY already defined
#endif
/** \brief Maintenance required */
#define DEM_SEVERITY_MAINTENANCE_ONLY             0x20U

#if (defined DEM_SEVERITY_CHECK_AT_NEXT_HALT)
#error DEM_SEVERITY_CHECK_AT_NEXT_HALT already defined
#endif
/** \brief Check at next halt */
#define DEM_SEVERITY_CHECK_AT_NEXT_HALT           0x40U

#if (defined DEM_SEVERITY_CHECK_IMMEDIATELY)
#error DEM_SEVERITY_CHECK_IMMEDIATELY already defined
#endif
/** \brief Check immediately */
#define DEM_SEVERITY_CHECK_IMMEDIATELY            0x80U

/*------------------[Dem_FaultDetectionCounterType]-------------------------*/

/** \brief Used to report Fault Detection Counter via API
 ** Dem_GetFaultDetectionCounter()
 **
 ** value: -128dec...127dec: PASSED ... FAILED according to ISO 14229-1
 **
 ** \note This type has been replaced with compatible base type (sint8) in
 ** AR3.1 Dem SWS, however it has been retained here for compatibility. */
typedef sint8 Dem_FaultDetectionCounterType;

/*----------------[Dem_FilterForFDCType]------------------------------------*/

/** \brief Used to specify the usage of Fault Detection Counter information */
typedef uint8 Dem_FilterForFDCType;

#if (defined DEM_FILTER_FOR_FDC_YES)
#error DEM_FILTER_FOR_FDC_YES already defined
#endif
/** \brief Fault Detection Counter information used */
#define DEM_FILTER_FOR_FDC_YES  0x00U

#if (defined DEM_FILTER_FOR_FDC_NO)
#error DEM_FILTER_FOR_FDC_NO already defined
#endif
/** \brief Fault Detection Counter information not used */
#define DEM_FILTER_FOR_FDC_NO   0x01U

/*----------------[Dem_FilterWithSeverityType]------------------------------*/

/** \brief Used to specify the usage of severity information */
typedef uint8 Dem_FilterWithSeverityType;

#if (defined DEM_FILTER_WITH_SEVERITY_YES)
#error DEM_FILTER_WITH_SEVERITY_YES already defined
#endif
/** \brief Severity information used */
#define DEM_FILTER_WITH_SEVERITY_YES  0x00U

#if (defined DEM_FILTER_WITH_SEVERITY_NO)
#error DEM_FILTER_WITH_SEVERITY_NO already defined
#endif
/** \brief Severity information not used */
#define DEM_FILTER_WITH_SEVERITY_NO   0x01U

#if ( (DEM_INCLUDE_RTE == STD_OFF) || \
      (DEM_DEFAULT_ASR_SERVICE_API == DEM_SERVICE_API_ASR40) )



      
/* This container contains the configuration (parameters) for DTC groups*/
typedef struct
{
    /* DTC values of the selected group of DTC */
    uint32 DemGroupDTCs ;
}DemGroupOfDTC_s;

/*This container contains the primary event memory specific parameters
 *of the Dem module.*/
typedef struct
{
    /*Maximum number of events which can be stored in the primary
     *memory*/
    uint8 DemMaxNumberEventEntryPrimary;

}DemPrimaryMemory_s;

/*This container contains the user defined event memory specific
 *parameters of the Dem module*/
typedef struct
{

    /*Maximum number of events which can be stored in the user defined
     *memory.*/
    uint8 DemMaxNumberEventEntryUserDefined;
    /*Identifier used by external tester to identify the User defined event
     *memory.*/
    uint8 DemUserDefinedMemoryIdentifier;

}DemUserDefinedMemory_s;

typedef struct
{

    /*Maximum number of events which can be stored in the user defined
     *memory.*/
    uint8 DemMaxNumberEventEntryMirror;

}DemMirrorMemory_s;

///////////////////////////
typedef union
{

    DemPrimaryMemory_s     *DemPrimaryMemory;
    DemUserDefinedMemory_s *DemUserDefinedMemory;
}Dem_Primary_UserDefined_Memory_s;


/*This container contains the configuration (parameters) for Indicators.*/
typedef struct
{
  /*Unique identifier of an indicator */
  uint8 DemIndicatorID ;
}DemIndicator_s;

/*Contains callback function definition which are called during clear DTC
 *operations.*/
typedef struct
{
    /*Notification callback function name which is called on a clear DTC
     *operation (refer to <Module>_ClearDtcNotification).*/
    Dem_ClearDtcNotification_cb DemClearDtcNotificationFnc;

    /*Configure, whether the callback shall be called on start of a clear or
    after finishing a clear DTC operation */
    DemClearDtcNotificationTime_Enum DemClearDtcNotificationTime;
}DemClearDTCNotification_s;


/* This container holds all parameters that are relevant to configure an operation cycle */
typedef struct DemOperationCycle_Str
{
    /*The autostart property defines if the operation cycles is automatically
     *(re-)started during Dem_PreInit.*/
    boolean DemOperationCycleAutostart ;

    /*This parameter’s value is used, together with the aggregating
     *container, to define a symbolic name of the operation cycle*/
    uint8 DemOperationCycleId ;

    /*  Defines the operation cycle, which is relevant for processing this
        operation cycle. */
    uint8 DemLeadingCycleRef_type ;
    struct DemOperationCycle_Str *DemLeadingCycleRef_ptr ; /////////////////
    uint8 DemLeadingCycleRef_numberOfElements ;
}DemOperationCycle_s;

typedef struct
{
    /*If the data element is an array data element, it defines the number of
     *elements in the array. Note that this is not the size in bytes.*/
    //uint32 DemDataElementArraySize;
    uint8 DemDataElementDataSize ;
    /*Provide the implementation data type of this C/S data element*/
    //DemDataElementDataType_Enum DemDataElementDataType ;
    /*If the parameter is set to True, the generated function call to retrieve
     *the data element has the monitorData0 as additional first parameter*/
    //boolean DemDataElementProvideMonitorData;
    /*In case of DemDataElementUsePort is false, this parameter defines
     *the prototype of the C function "ReadDataElement" used to get the
     *according value.*/
    DemDataElementReadFnc_cb DemDataElementReadFnc;
    /*If the parameter is set to True, a R-Port is generated, to obtain the data
     *element (interface DataServices_{Data}). If the parameter is set to
     *False, the information is obtained by C function-call on another BSW
     *module specified by the parameter DemDataElementReadFnc.*/
    boolean DemDataElementUsePort;
}DemExternalCSDataElementClass_s;

typedef struct
{
    /*If the data element is an array data element, it defines the number of
     *elements in the array. Note that this is not the size in bytes.*/
    //uint32 DemDataElementArraySize;
    uint8 DemDataElementDataSize ;
    /*Provide the implementation data type of this C/S data element*/
    DemDataElementDataType_Enum DemDataElementDataType;
    /*Defines the endianness of the data belonging to an external data*/
    DemDataElementEndianness_Enum DemDataElementEndianness;
    /*Reference to DemDiagnosisScaling Sub container*/
    uint8 DemDiagnosisScaling_type;
    uint8 DemDiagnosisScaling_startingIndex ;
    uint8 DemDiagnosisScaling_numberOfInstances;
    /*Reference to DemSRDataElementClass Sub container*/
    uint8 DemSRDataElementClass_type;
    uint8 DemSRDataElementClass_startingIndex;
    uint8 DemSRDataElementClass_numberOfInstances;

}DemExternalSRDataElementClass_s;

typedef struct
{
    /*Defines the size of the data element in bytes*/
    uint8 DemDataElementDataSize;
    /*This parameter defines the Dem-internal data value, which is mapped
    to the data element.*/
    DemInternalDataElement_Enum DemInternalDataElement ;

}DemInternalDataElementClass_s;
typedef union
{
    DemExternalCSDataElementClass_s DemExternalCSDataElementClass_Ref;
    DemExternalSRDataElementClass_s DemExternalSRDataElementClass_Ref;
}DemExternal_CS_SR_DataElementClass_s;
typedef struct
{
    DemExternalCSDataElementClass_s DemExternalCSDataElementClass_Ref;
    DemExternalSRDataElementClass_s DemExternalSRDataElementClass_Ref;
    DemInternalDataElementClass_s   DemInternalDataElementClass_Ref;
}DemExternal_CS_SR_Interal_DataElementClass_s;

/*This container contains the configuration (parameters) for a data Id
 *class. It is assembled out of one or several data elements*/
typedef struct
{
   /* DemExternalCSDataElementClass*/
    DemExternalCSDataElementClass_s *DemExternalCSDataElementClass;
    DemExternalSRDataElementClass_s *DemExternalSRDataElementClass;
    DemInternalDataElementClass_s   *DemInternalDataElementClass;
}DemDataElementClass_s;

typedef struct
{
    /* dentifier of the Data ID.*/
    uint16 DemDidIdentifier ;

    /* This reference contains the link to a data element class. */
    //TODO DemDataElementClass* DemDidDataElementClassRef;
}DemDidClass_s;

/*This container contains the configuration (parameters) for a non-volatile
 *memory block, which is used from the Dem. If no permanent storage of
 *event memory entries is required, no block needs to be configured.*/
typedef struct NvMBlockDescriptor_s
{
    /*This reference contains the link to a non-volatile memory block. For
     *post build time configurations worst case scenario shall be used*/
    uint8 DemNvRamBlockIdRef_type ;
    struct NvMBlockDescriptor_s *DemNvRamBlockIdRef_ptr; /////////////**** pg 428***/

    uint8 DemNvRamBlockIdRef_numberOfElements ;
}DemNvRamBlockId_s;

typedef struct
{
    DemCallbackDTCStatusChangedFnc_cb DemCallbackDTCStatusChangedFnc ;
}DemCallbackOBDDTCStatusChanged_s;

/*This container contains the general OBD-specific configuration
 *(parameters) of the Dem module*/
typedef struct
{
    /*Defines the operationCycle which denotes the OBD driving cycle */
    uint8                 DemOBDDrivingCycleRef_type ;
    DemOperationCycle_s * DemOBDDrivingCycleRef_ptr ;
    uint8                 DemOBDDrivingCycleRef_numberOfElements;
    /*Input variable for the accelerator padal information, which is assigned
     *to a specific data element used as interface for the Dem-internal PID calculations.*/
    uint8       DemOBDInputAcceleratorPedalInformation_type ;
    DemExternal_CS_SR_DataElementClass_s* DemOBDInputAcceleratorPedalInformation_ptr;
    uint8       DemOBDInputAcceleratorPedalInformation_numberOfElements ;
    /*Input variable for the ambient pressure, which is assigned to a specific
     *data element used as interface for the Dem-internal PID calculations.*/
    uint8       DemOBDInputAmbientPressure_type ;
    DemExternal_CS_SR_DataElementClass_s* DemOBDInputAmbientPressure_ptr;
    uint8       DemOBDInputAmbientPressure_numberOfElements ;
    /*Input variable for the ambient temperature, which is assigned to a
     *specific data element used as interface for the Dem-internal PID
     *calculations*/
    uint8 DemOBDInputAmbientTemperature_type;
    DemExternal_CS_SR_DataElementClass_s* DemOBDInputAmbientTemperature_ptr;
    uint8 DemOBDInputAmbientTemperature_numberOfElements ;
    /*Input variable for the distance information, which is assigned to a
     *specific data element used as interface for the Dem-internal PID
     *calculations.*/
    uint8 DemOBDInputDistanceInformation_type;
    DemExternal_CS_SR_DataElementClass_s* DemOBDInputDistanceInformation_ptr;
    uint8 DemOBDInputDistanceInformation_numberOfElements;
    /*Input variable for the engine speed, which is assigned to a specific data
     *element used as interface for the Dem-internal PID calculations*/
    uint8 DemOBDInputEngineSpeed_type ;
    DemExternal_CS_SR_DataElementClass_s* DemOBDInputEngineSpeed_ptr;
    uint8 DemOBDInputEngineSpeed_numberOfElements;
    /*Input variable for the engine temperature, which is assigned to a
     *specific data element used as interface for the Dem-internal PID
     *calculations.*/
    uint8 DemOBDInputEngineTemperature_type ;
    DemExternal_CS_SR_DataElementClass_s* DemOBDInputEngineTemperature_ptr;
    uint8 DemOBDInputEngineTemperature_numberOfElements;
    /*Input variable for the programming event, which is assigned to a
     *specific data element used as interface for the Dem-internal PID
     *calculations.*/
    uint8 DemOBDInputProgrammingEvent_type ;
    DemExternal_CS_SR_DataElementClass_s* DemOBDInputProgrammingEvent_ptr;
    uint8 DemOBDInputProgrammingEvent_numberOfElements ;
    /*Input variable for the vehicle speed, which is assigned to a specific
     *data element used as interface for the Dem-internal PID calculations*/
    uint8 DemOBDInputVehicleSpeed_type ;
    DemExternal_CS_SR_DataElementClass_s *DemOBDInputVehicleSpeed_ptr;
    uint8 DemOBDInputVehicleSpeed_numberOfElements ;
    /*Defines the operationCycle, which is relevant for processing the OBDPFCCycle.*/
    uint8 DemOBDPFCCycleRef_type;
    DemOperationCycle_s * DemOBDPFCCycleRe_ptr;
    uint8 DemOBDPFCCycleRef_numberOfElements;
    /*Input variable for the Time Since Engine Start information, which is
     *assigned to a specific data element*/
    uint8 DemOBDTimeSinceEngineStart_type ;
    DemExternal_CS_SR_Interal_DataElementClass_s DemOBDTimeSinceEngineStart_ptr;
    uint8 DemOBDTimeSinceEngineStart_numberOfElements ;
    /*Defines the operationCycle which denotes the OBD warm-up cycle */
    uint8 DemOBDWarmUpCycleRef_type;
    DemOperationCycle_s * DemOBDWarmUpCycleRef_ptr ;
    uint8 DemOBDWarmUpCycleRef_numberOfElements;
    /*Function name of prototype "DTCStatusChanged".*/
    uint8 DemCallbackOBDDTCStatusChanged_startingIndex ;
    uint8 DemCallbackOBDDTCStatusChanged_numberOfInstances;

}DemGeneralOBD_s;

/*This container contains a list of dedicated, different freeze frame record numbers.*/
typedef struct
{
    /*This parameter defines a record number for a freeze frame record.
     *This record number is unique per freeze frame record number class*/
    uint8 DemFreezeFrameRecordNumber ;
    /*Defines the trigger to store the FreezeFrameRecord. */
    DemFreezeFrameRecordTrigger_Enum DemFreezeFrameRecordTrigger;
    /*This parameter defines the case, when the freeze frame record is
     *stored/updated*/
    DemFreezeFrameRecordUpdate_Enum DemFreezeFrameRecordUpdate;
}DemFreezeFrameRecordClass_s;

/*This container contains a list of dedicated, different freeze frame record
 *numbers assigned to an event. The order of record numbers in this list
 *is assigned to the chronological order of the according freeze frame
 *records*/
typedef struct
{
    /* Reference to the DID elements which shall be contained in the freeze frame.*/
    uint8 DemFreezeFrameRecordClassRef_type ;
    DemFreezeFrameRecordClass_s * DemFreezeFrameRecordClassRef_ptr;
    uint8 DemFreezeFrameRecordClassRef_numberOfElements ;
}DemFreezeFrameRecNumClass_s;

/*This container contains the combinations of DIDs for a non OBD2 and
  *WWH-OBD relevant freeze frame class.*/
typedef struct
{
    /* Reference to the DID elements which shall be contained in the freeze frame.*/
    uint8 DemDidClassRef_type ;
    DemDidClass_s * DemDidClassRef_ptr ;
    uint8 DemDidClassRef_numberOfElements ;
}DemFreezeFrameClass_s;
/*This container contains the configuration (parameters) for an extended
 *data record class.*/
typedef struct
{
    /*This configuration parameter specifies an unique identifier for an
     *extended data record.
     *One or more extended data records can be assigned to one diagnostic
     *event/DTC.*/
    uint8 DemExtendedDataRecordNumber ;
    /* Defines the trigger to store the ExtendedDataRecord */
    DemExtendedDataRecordTrigger_Enum DemExtendedDataRecordTrigger;
    /*This extended data record is captured if the configured trigger
     *condition in "DemExtendedDataRecordTrigger" is fulfilled.*/
    DemExtendedDataRecordUpdate_Enum DemExtendedDataRecordUpdate ;
    /* This reference contains the link to a data element class */
    DemDataElementClass_s * DemDataElementClassRef ;

}DemExtendedDataRecordClass_s;

/*This class contains the combinations of extended data records for an
  *extended data class.*/
typedef struct
{
    /* This reference contains the link to an extended data class record. */
    uint8 DemExtendedDataRecordClassRef_type;
    DemExtendedDataRecordClass_s * DemExtendedDataRecordClassRef_ptr ;
    uint8 DemExtendedDataRecordClassRef_numberOfElements;
}DemExtendedDataClass_s;

/*This container is a collection of referenced event memories and related
 * information for a Dem client.
 */
typedef struct DemEventMemorySet_Str
{
  /*Mask for the supported DTC status bits by the Dem. This mask is used
   *by UDS service 0x19.*/
  uint8 DemDtcStatusAvailabilityMask;
  /* Maximum number of events which can be stored in the permanent
   * memory.
   * The assignment of an event to this memory type is dynamic and used
   * for emission-related events only.*/
  uint8 DemMaxNumberEventEntryPermanent;
  /* This parameter defines the format returned by
   * Dem_GetTranslationType and does not relate to/influence the
   * supported Dem functionality.*/
  DemTypeOfDTCSupported_Emun DemTypeOfDTCSupported;
  /*This parameter defines the indicator representing the MIL.
   *This parameter is mandatory for ECUs supporting OBD (refer to
   *DemOBDSupport).*/
  uint8 DemMILIndicatorRef_type ;
  struct DemEventMemorySet_Str *DemMILIndicatorRef_ptr; // 0..1
  uint8 DemMILIndicatorRef_numberOfElements;

  /*This parameter defines the indicator representing the
   *AmberWarningLamp . This parameter may be used for ECUs
   *supporting J1939.*/
  uint8 DemAmberWarningLampIndicatorRef_type;
  DemIndicator_s *DemAmberWarningLampIndicatorRef_ptr ; // 0..1

  uint8 DemAmberWarningLampIndicatorRef_numberOfElements;
  /*This parameter defines the indicator representing the ProtectLamp.
   *This parameter may be used for ECUs supporting J1939. */
  uint8 DemProtectLampIndicatorRef_type;
  DemIndicator_s *DemProtectLampIndicatorRef_ptr ;  // 0..1
  uint8 DemProtectLampIndicatorRef_numberOfElements;
  /*This parameter defines the indicator representing the RedStopLamp.
   *This parameter may be used for ECUs supporting J1939. */
  uint8 DemRedStopLampIndicatorRef_type;
  DemIndicator_s *DemRedStopLampIndicatorRef_ptr ; // 0..1
  uint8 DemRedStopLampIndicatorRef_numberOfElements ;
  /* included containers*/
  uint8 DemClearDTCNotification_startingIndex ;
  uint8 DemClearDTCNotification_numberOfInstances;

  uint8 DemIndicator_startingIndex;
  uint8 DemIndicator_numberOfInstances;
  uint8 DemMirrorMemory_startingIndex ;
  uint8 DemMirrorMemory_numberOfInstances;


  uint8 DemPrimaryMemory_startingIndex ;
  uint8 DemPrimaryMemory_numberOfInstances ;

  uint8 DemUserDefinedMemory_startingIndex ;
  uint8 DemUserDefinedMemory_numberOfInstances ;
}DemEventMemorySet_s;

typedef struct
{
     DemCallbackDTCStatusChangedFnc_cb DemCallbackDTCStatusChangedFnc;
}DemCallbackDTCStatusChanged_s;

//This container contains possible clients that are using the Dem APIs.
typedef struct
{
    /*Defines a unique identifier for a Dem client. This number is used by this
     *client in the ClientID parameter in all API with this parameter.*/
    uint8 DemClientId;
    /*Functionality provided by Dem for the DemClient.*/
    DemClientFunctionality_Enum DemClientFunctionality ;
    /*If set to true, this client shall only use the DEM via RTE (Dem will
     *provide the C/S interfaces: CddIf, EvMemOverflowIndication). The
     *client must not do any C_API calls to the DEM. Default Value false */
    boolean DemClientUsesRte ;
    /*References to the client assigned event memory container that
     *contains client specific settings and event memories*/
    /*Function name of prototype "DTCStatusChanged" */
    uint8 DemEventMemorySetRef_type ;
    DemEventMemorySet_s *DemEventMemorySetRef_ptr ;
    uint8 DemEventMemorySetRef_numberOfElements ;
    /*The presence of this container indicates, that the Dem has access to a
     "DTCStatusChanged" callback, which the Dem will call to notify other
     *components about the change in the status of a DTC
     */
    uint8 DemCallbackDTCStatusChanged_startingIndex ;
    uint8 DemCallbackDTCStatusChanged_numberOfInstances ;
}DemClient_s;

/*This container contains the configuration (parameters) for enable
  conditions.                                                       */

typedef struct
{
    /* Defines a unique enable condition Id.*/
    /* This parameter should not be changeable by user, because the Id
       should be generated by Dem itself to prevent gaps and multiple use of
       an Id. The enable conditions should be sequentially ordered beginning
       with 0 and no gaps in between.
     */
    uint8 DemEnableConditionId ;

   /*Defines the initial status for enable or disable of acceptance of event
     reports of a diagnostic event.
     The value is the initialization after power up (before this condition is
     reported the first time). true: acceptance of a diagnostic event enabled
     false: acceptance of a diagnostic event disabled
    */
    boolean DemEnableConditionStatus ;


}DemEnableCondition_s;/* tool */

/*This container contains the configuration (parameters) for enable
  conditions groups .
  */
typedef struct
{
    /* References an enable condition.*/
    uint8 DemEnableConditionRef_type;
    DemEnableCondition_s * DemEnableConditionRef_ptr ;
    uint8 DemEnableConditionRef_numberOfElements;
}DemEnableConditionGroup_s;

/*This container configures the monitored components and system
 *dependencies */
typedef struct DemComponent_str
{
    /*Specifies the function to be called on component failed status changes */
    DemComponentFailedCallbackFnc_cb DemComponentFailedCallbackFnc ;
    /*Specifies whether CBStatusComp_{ComponentName} for component change notifications shall be provided */
    /*DemComponentFailedCallbackUsePort [ */
    /*Unique identifier of a DemComponent */
    uint16 DemComponentId ;
    /*This configuration switch defines, whether the priority of events at this
     *component shall be ignored.*/
    boolean DemComponentIgnoresPriority;
    /* Reference to all immediate children of the current component */
    uint8 DemImmediateChildComponentRef_type;
    struct DemComponent_str* DemImmediateChildComponentRef_ptr;
    uint8 DemImmediateChildComponentRef_numberOfElements;
}DemComponent_s;



/*The presence of this container indicates that the Dem
has access to a "ClearEventAllowed" callback   */
typedef struct
{
   /*  Function name of prototype "ClearEventAllowed". */
    Dem_CallbackClearEventAllowed_cb Dem_CallbackClearEventAllowed;
    /*  Defines the resulting UDS status byte for the related event, which must
        not be cleared according to the ClearEventAllowed callback              */
    DemClearEventAllowedBehavior_Enum DemClearEventAllowedBehavior ;
}DemCallbackClearEventAllowed_s;

/*This container contains the configuration of Debounce Time Based
Class.*/
typedef struct
{
    DemDebounceBehavior_Enum DemDebounceBehavior;
    /*Defines the time out duration for "Event Failed" qualification.*/
    float32 DemDebounceTimeFailedThreshold;
    /*Defines the time out duration for "Event Passed" qualification.*/
    float32 DemDebounceTimePassedThreshold;
    /*Threshold to allocate an event memory entry and to capture the Freeze
     *Frame.*/
    float32 DemTimeBasedFdcThresholdStorageValue;

}DemDebounceTimeBaseClass_s;



/*This container contains the configuration of Debounce Counter Based Class */
typedef struct
{
    /* Threshold to allocate an event memory entry and to capture the Freeze Frame.*/
    uint16 DemCounterBasedFdcThresholdStorageValue ; ///////////////////////
    /*  This parameter defines how the event debounce algorithm will behave,
        if a related enable condition is not fulfilled or ControlDTCSetting of the
        related event is disabled                                                   */
     DemDebounceBehavior_Enum DemDebounceBehavior;
    /* Defines the step size for decrementation of the internal debounce counter (PREPASSED).*/
    uint16 DemDebounceCounterDecrementStepSize ;
    /*  Defines the value of the internal debounce counter, which indicates the failed status */
    uint16 DemDebounceCounterFailedThreshold ;
    /*  Defines the step size for incrementation of the internal debounce counter (PREFAILED) */
    uint16 DemDebounceCounterIncrementStepSize ;
    /*  Switch for the activation of Jump-Down. */
    boolean DemDebounceCounterJumpDown;
    /*  Jump-Down value of the internal debounce counter which is taken as
        initialization value for the counter when the respective step-down
        occurs.                                                            */
    sint16 DemDebounceCounterJumpDownValue ;
    /*  Switch for the activation of Jump-Up. */
    boolean DemDebounceCounterJumpUp ;
    /*  Jump-Up value of the internal debounce counter which is taken as
        initialization value for the counter when the respective step-up occurs */
    sint16 DemDebounceCounterJumpUpValue ;
    /* Defines the value of the internal debounce counter, which indicates the passed status */
    sint16 DemDebounceCounterPassedThreshold ;
    /*  Switch to store the debounce counter value non-volatile or not  */
    boolean DemDebounceCounterStorage ;
}DemDebounceCounterBasedClass_s;

typedef struct
{
    DemCallbackGetFDCFnc_cb                   DemCallbackGetFDCFnc;

}DemDebounceMonitorInternal_s;

/*Debounce algorithm class: counter based, time based, or monitor
internal.*/
typedef struct
{
    union
    {

        /*This reference selects the DemDebounceCounterBasedClass applied
         *for the debouncing of the DemEventParameter.*/
        DemDebounceCounterBasedClass_s            *DemDebounceCounterBasedClassRef_ptr;
        /*This parameter defines the name of the function that the Dem will call
         *to retrieve the fault-detection counter value from a complex driver.*/
        DemDebounceMonitorInternal_s              *DemDebounceMonitorInternal;
        /*This reference selects the DemDebounceTimeBaseClass applied for
         *the debouncing of the DemEventParameter*/
        DemDebounceTimeBaseClass_s                *DemDebounceTimeBaseRef_ptr;
    }DebounceAlgorithm;

}DemDebounceAlgorithmClass_s;


/* This container contains the configuration (parameters) for DemObdDTC.*/
typedef struct
{
    /*  This parameter is TRUE, when the event is affected by the Dem PTO handling.*/
    boolean DemConsiderPtoStatus ;
    /*  Unique Diagnostic Trouble Code value for OBD */
    uint16 DemDtcValue ;
    DemEventOBDReadinessGroup_enum DemEventOBDReadinessGroup;
    /* Unique Diagnostic Trouble Code value for J1939 */
    uint32 DemJ1939DTCValue ;
    /* unit32 DemJ1939DTCValue ;*/
}DemObdDTC_s;

/*This container contains the different data elements contained in the specific PID */
typedef struct
{
    /* This reference contains the link to a data element class */
    DemDataElementClass_s * DemPidDataElementClassRef ;

}DemPidDataElement_s;

/*This container contains the different PIDs for the single global OBD
relevant freeze frame class. It is assembled out of one or several data
elements.*/
typedef struct
{
    /* identifier of the PID */
    uint8 DemPidIdentifier ;
////////////////////////////
    uint8 DemPidDataElement_startingIndex ;
    uint8 DemPidDataElement_numberOfInstances;
}DemPidClass_s;

/* This container contains the configuration (parameters) for
DemDTCAttributes */
typedef struct
{
    /* Defines if a DTC can be aged */
    boolean DemAgingAllowed ;
    /* Number of aging cycles needed to unlearn/delete the event */
    uint8 DemAgingCycleCounterThreshold ;
    /* Number of aging cycles needed to reset the testFailedSinceLastClear Bit. */
    uint8 DemAgingCycleCounterThresholdForTFSLC ;
    /* Priority of the event/dtc, in view of full event memory. A lower value
        means higher priority                                               */
    uint8 DemDTCPriority ;
    /* Significance of the event, which indicates additional information
        concerning fault classification and resolution */
    DemDTCSignificance_Enum DemDTCSignificance;
    /* This parameter defines the number of according freeze frame records,
    which can maximal be stored for this event. Therefore all these freeze
    frame records have the same freeze frame class.*/
    uint8 DemMaxNumberFreezeFrameRecords;
    /* Reference to the cycle which is triggering the aging of the event. */
    uint8 DemAgingCycleRef_type;
    DemOperationCycle_s * DemAgingCycleRef_ptr ;
    uint8 DemAgingCycleRef_numberOfElements;
    /* This reference defines the link to an extended data class sampler */
    uint8 DemExtendedDataClassRef_type ;
    DemExtendedDataClass_s * DemExtendedDataClassRef_ptr ;
    uint8 DemExtendedDataClassRef_numberOfElements ;
    /* These references define the links to a freeze frame class sampler. */
    uint8 DemFreezeFrameClassRef_type ;
    DemFreezeFrameClass_s * DemFreezeFrameClassRef_ptr ;
    uint8 DemFreezeFrameClassRef_numberOfElements;
    /* This parameter defines the list of dedicated freeze frame record
        numbers associated with the diagnostic event. These record numbers
        are assigned to the freeze frame records (instead of calculated record
        numbers).*/
    uint8 DemFreezeFrameRecNumClassRef_type;
    DemFreezeFrameRecNumClass_s * DemFreezeFrameRecNumClassRef_ptr ;
    uint8 DemFreezeFrameRecNumClassRef_numberOfElements;
    /* This reference defines the link to a WWH-OBD freeze frame class sampler. */
    uint8 DemWWHOBDFreezeFrameClassRef_type ;

    DemFreezeFrameClass_s * DemWWHOBDFreezeFrameClassRef_ptr ;
    uint8 DemWWHOBDFreezeFrameClassRef_numberOfElements ;
    /*The memory destination assigns DTCs to one or two memory
     *destinations. If more than one memory destination is assigned to a
     *specific DTC, the DTC can be present in the corresponding event
     *memories. In this case one of the references has to be
     *DemMirrorMemory*/

    /*.DemJ1939ExpandedFreezeFrameClassRef_type
    .DemJ1939ExpandedFreezeFrameClassRef_ptr
    .DemJ1939ExpandedFreezeFrameClassRef_numberOfElements
    .DemJ1939FreezeFrameClassRef_type
    .DemJ1939FreezeFrameClassRef_ptr
    .DemJ1939FreezeFrameClassRef_numberOfElements */
    uint8 DemMemoryDestinationRef_type;
    Dem_Primary_UserDefined_Memory_s *DemMemoryDestinationRef_ptr;
    uint8 DemMemoryDestinationRef_numberOfElements;
    uint8 DemJ1939ExpandedFreezeFrameClassRef_type;
    uint8 *DemJ1939ExpandedFreezeFrameClassRef_ptr;
    uint8 DemJ1939ExpandedFreezeFrameClassRef_numberOfElements;

    uint8 DemJ1939FreezeFrameClassRef_type;
    uint8 *DemJ1939FreezeFrameClassRef_ptr;
    uint8 DemJ1939FreezeFrameClassRef_numberOfElements;

}DemDTCAttributes_s;
/* This container contains the configuration (parameters) for DemUdsDTC. */
typedef struct
{
    /*DTCFuncitonalUnit is a 1-byte value which identifies the corresponding
     *basic vehicle / system function which reports the DTC. This parameter
     *is necessary for the report of severity information*/
    uint8 DemDTCFunctionalUnit ;
    /*DTC severity according to ISO 14229-1. This parameter depends on
     *the automotive manufacturer*/
    DemDTCSeverity_Enum DemDTCSeverity;
    /*Unique Diagnostic Trouble Code value for UDS */
    uint32 DemDtcValue;
    /*This parameter defines when a specific event memory entry is allowed
     *to be stored in the NVRAM.*/
    DemNvStorageStrategy_Enum DemNvStorageStrategy ;
    /*This parameter defines the DTC Attributes associated with the DemDTC. */
    uint8 DemDTCAttributesRef_type;
    DemDTCAttributes_s *DemDTCAttributesRef_ptr;
    uint8 DemDTCAttributesRef_numberOfElements;
    /*DTC Class according to ISO 14229-1 [2013 version]. This parameter
     *depends on the automotive manufacturer. If it is not configured, the
     *value is marked as �unclassified�. If this parameter is configured for no
     *DTC, the Dem provides no DTC WWHOBD class information.*/
     DemWWHOBDDTCClass_Enum DemWWHOBDDTCClass;
    /* This parameter defines the OBD DTC configuration associated with the DemDTC. */
    uint8 DemObdDTCRef_type ;

    DemObdDTC_s* DemObdDTCRef_ptr ;
    uint8 DemObdDTCRef_numberOfElements ;


}DemDTC_s;

/*  This container contains the configuration (parameters) for storage
    conditions.                                                        */
typedef struct
{
    /*Defines a unique storage condition Id. */
    uint8 DemStorageConditionId ;
    /*Defines the initial status for enable or disable of storage of a diagnostic
     *event*/
    boolean DemStorageConditionStatus ;
    /*Specifies the reference to an event which is stored to event memory
     *and supports failure analysis*/
    uint8 DemStorageConditionReplacementEventRef_type ;
    //DemEventParameter_s * DemStorageConditionReplacementEventRef_ptr ;
    uint8 * DemStorageConditionReplacementEventRef_ptr ;

    uint8 DemStorageConditionReplacementEventRef_numberOfElements;
}DemStorageCondition_s;


typedef struct
{
    DemCallbackInitMForEFnc_cb DemCallbackInitMForEFnc ;
} DemCallbackInitMForEFnc_s;

typedef struct
{
    DemCallbackEventDataChangedFnc_cb DemCallbackEventDataChangedFnc ;
}DemCallbackEventDataChanged_s ;
typedef struct
{
    uint8 DemStorageConditionRef_type;
    uint8 DemStorageConditionRef_numberOfElements;
    DemStorageCondition_s *DemStorageConditionRef_ptr;

}DemStorageConditionGroup_s;

/* This container contains the configuration (parameters) for events. */
typedef struct DemEventParameter_Str
{
   /* Time to wait until the event is considered as causal. The parameter is specified in seconds */
    float32 DemCausalityDelayTime ; /////////////////
    /*  Specifies the priority within the component. A lower value means higher priority. */
    uint8 DemComponentPriority ;
    /*  This parameter configures an Event as unavailable. It is treated by
        Dem as if it does not exist. true = Event is available false = Event is not available */
    boolean DemEventAvailable ;
    /*  Defines the operation cycle threshold of the DTC confirmation status
        according "Confirmation Threshold" of ISO 14229-1.                      */
    uint8 DemEventConfirmationThreshold ;
    /*  Indicates whether the events confirmation Cycle threshold can be
        adapted by Dem_SetEventFailureCycleCounterThreshold.                */
    boolean DemEventFailureCycleCounterThresholdAdaptable ;
    /*  Unique identifier of a diagnostic event */
    uint16 DemEventId ;
    /*  This parameter is used to distinguish between SW-C and BSW events.*/
    DemEventKind_Enum  DemEventKind ;

    /*  if parameter is configured to FALSE, reporting of PASSED will be
        ignored if the event is already "testfailed this operation cycle" */
    boolean DemEventRecoverableInSameOperationCycle ;
    /*  If the event uses a pre-stored freeze-frame this attribute indicates if the
        event requires the pre-stored data to be stored in non-volatile memory.
        TRUE = store the pre-stored data in non-volatile memory, FALSE =
        pre-stored data is not stored in non-volatile memory.                   */
    boolean DemFFPrestorageInNvm ;
    /*  If this parameter is set to true, then the Prestorage of FreezeFrames is
        supported by the assigned event. This parameter is useful to calculate
        the buffer size.                                                        */
    boolean DemFFPrestorageSupported ;
    /*  Indicates the reporting behavior of the BSW Module (DemEventKind
        == DEM_EVENT_KIND_BSW) in order to determine the size of the
        reporting queue.                                                    */
    DemReportBehavior_Enum DemReportBehavior;

    /* Reference to the monitored component */
    uint8 DemComponentClassRef_type;
    DemComponent_s * DemComponentClassRef_ptr ;
    uint8 DemComponentClassRef_numberOfElements;
    /* This parameter defines the DTC configuration (typically Uds)
        associated with the diagnostic event.                       */
    uint8 DemDTCRef_type;
    DemDTC_s * DemDTCRef_ptr ;

    uint8 DemDTCRef_numberOfElements;
    /*  References an enable condition group. */
    uint8 DemEnableConditionGroupRef_type;
    DemEnableConditionGroup_s * DemEnableConditionGroupRef_ptr ;
    uint8 DemEnableConditionGroupRef_numberOfElements;
    /*  This parameter defines a reference which points to a representative
        event of one group of associate events. The "reverence event" must
        refer to it self. Note: One event is only allowed to be reverenced to only
        one group of associate events.                                              */
    uint8 DemOBDGroupingAssociativeEventsRef_type;

    struct DemEventParameter_Str * DemOBDGroupingAssociativeEventsRef_ptr ;
    uint8 DemOBDGroupingAssociativeEventsRef_numberOfElements;
    /*  Kind of operation cycle for the event (e.g. power cycle, driving cycle, ...) */
    uint8 DemOperationCycleRef_type ;
    DemOperationCycle_s * DemOperationCycleRef_ptr ;
    uint8 DemOperationCycleRef_numberOfElements ;
    /*  References a storage condition group */
    uint8 DemStorageConditionGroupRef_type;

    DemStorageConditionGroup_s * DemStorageConditionGroupRef_ptr ;
    uint8 DemStorageConditionGroupRef_numberOfElements;
    /*  ***********    */
    uint8 DemCallbackClearEventAllowed_startingIndex;
    uint8 DemCallbackClearEventAllowed_numberOfInstances;

    uint8 DemCallbackEventDataChanged_startingIndex;
    uint8 DemCallbackEventDataChanged_numberOfInstances;

    uint8 DemCallbackEventUdsStatusChanged_startingIndex;
    uint8 DemCallbackEventUdsStatusChanged_numberOfInstances;

    uint8 DemCallbackInitMForE_startingIndex ;
    uint8 DemCallbackInitMForE_numberOfInstances ;

    uint8 DemCallbackMonitorStatusChanged_startingIndex;
    uint8 DemCallbackMonitorStatusChanged_numberOfInstances;
    uint8 DemDebounceAlgorithmClass_type ;
    uint8 DemDebounceAlgorithmClass_startingIndex ;
    uint8 DemDebounceAlgorithmClass_numberOfInstances;
    uint8 DemIndicatorAttribute_startingIndex ;
    uint8 DemIndicatorAttribute_numberOfInstances;



}DemEventParameter_s;






/*This container contains the OBD-specific in-use-monitor performance
 *ratio configuration. It is related to a specific event, a FID, and an
 *IUMPR group.*/
typedef struct
{
        /*This parameter specifies the assigned denominator type which is
         *applied in addition to the
         *DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR conditions*/
        DemIUMPRDenGroup_Enum DemIUMPRDenGroup ;
        /* This parameter specifies the assigned IUMPR group of the ratio Id. */
        DemIUMPRGroup_Enum DemIUMPRGroup;
        /* Defines a unique ratio Id. */
        uint8 DemRatioId ;
        /*This parameter defines whether the ratio will be calculated API or
         *observer based*/
        DemRatioKind_Enum DemRatioKind;
        /* This reference contains the link to a diagnostic event   */
        uint8 DemDiagnosticEventRef_type;

        DemEventParameter_s *DemDiagnosticEventRef_ptr ;
        uint8 DemDiagnosticEventRef_numberOfElements;
        /*  This reference contains the link to a function identifier within the FiM
            which is used as a primary FID.                                          */
        uint8 DemFunctionIdRef_type;
        //TO DO
        uint8 *DemFunctionIdRef_ptr;
        uint8 DemFunctionIdRef_numberOfElements;
        /* FiMFID *DemFunctionIdRef */
        uint8 DemSecondaryFunctionIdRef_type;
        uint8 *DemSecondaryFunctionIdRef_ptr;
        uint8 DemSecondaryFunctionIdRef_numberOfElements;
}DemRatio_s ;

/*This container holds the configuration of one individual DTR.*/
typedef struct
{
   /*Part of the conversion between the binary representation and the
    *physical meaning analogous to the SW-C Template conversion
    *CompuRationalCoeffs with 2 numerator coefficients and 1 denominator
    *coefficient in the direction compuInternalToPhys. This is the only one
    *supported denominator value, a constant divisor.
    *The value 0 is not allowed.*/
    float32 DemDtrCompuDenominator0;
    float32 DemDtrCompuNumerator0;
    float32 DemDtrCompuNumerator1;
    /*The index identifier value assigned to this DTR. The value is generated
     *during the Dem configuration process.*/
    uint32  DemDtrId;
    /*The OBDMID of the DTR.*/
    uint8   DemDtrMid;
    /*The OBDTID of the DTR.*/
    uint8   DemDtrTid;
    /*The UaSId the DTR data shall be scaled to, and reported together with
    the rescaled DTR data.*/
    uint8 DemDtrUasid;
    /*Update conditions applied by the Dem to reports of DTR values. Only
     *supported if a related Event is configured*/
    DemDtrUpdateKind_Enum DemDtrUpdateKind;
    /*Reference to the DemEventParameter this DTR is related to. If the
    *related event is not configured, the Dem cannot ensure consistency
    *between the DTR and the event*/
    uint8 DemDtrEventRef_type ;
    DemEventParameter_s *DemDtrEventRef_ptr;
    uint8 DemDtrEventRef_numberOfElements ;
}DemDtr_s;

/*This container contains the configuration (parameters) for storage
 *condition groups.*/

/* Configures an event that will trigger other events whenever the event is reported. */
typedef struct
{
    /*  Reference to the event that will trigger other events upon reception of this event.*/
    uint8 DemMultiEventTriggeringMasterEventRef_type;
    DemEventParameter_s* DemMultiEventTriggeringMasterEventRef_ptr;
    uint8 DemMultiEventTriggeringMasterEventRef_numberOfElements;
    /* Reference to the event that is triggered upon triggering the master event.*/
    uint8 DemMultiEventTriggeringSlaveEventRef_type;
    DemEventParameter_s * DemMultiEventTriggeringSlaveEventRef_ptr;
    uint8 DemMultiEventTriggeringSlaveEventRef_numberOfElements;
}DemMultiEventTriggering_s;

#endif /* DEM_TYPES_H_ */
