

#ifndef DEM_LCFG_H
#define DEM_LCFG_H



/******************************************************************************************
****************************************Dem Module****************************************
*********************************Link-Time Configurations*********************************
******************************************************************************************/




/******************************************************************************************
***************************************Dem Module's***************************************
****************************************Structures****************************************
******************************************************************************************/


/*
* DemClient Container
*  Macro Configurations
*/
#define DEMCLIENT_SIZE                                               (3U)
#define DEMCLIENT_ID_0                                               (0U)
#define DEMCALLBACKDTCSTATUSCHANGED_0_STARTING_INDEX                 (0U)
#define DEMCALLBACKDTCSTATUSCHANGED_0_NUMBER_INSTANCES               (1U)

#define DEMCLIENT_ID_1                                               (1U)

#define DEMCLIENT_ID_2                                               (2U)


/*
* DemCallbackDTCStatusChanged Container
*  Macro Configurations
*/
#define DEMCALLBACKDTCSTATUSCHANGED_SIZE                             (1U)
#define DEMCALLBACKDTCSTATUSCHANGED_ID_0                             (0U)

/*
* DemExternalSRDataElementClass Container
*  Macro Configurations
*/
#define DEME1TERNALSRDATAELEMENTCLASS_SIZE                           (1U)
#define DEMEXTERNALSRDATAELEMENTCLASS_ID_0                           (0U)
#define DEMALTERNATIVEDATAINTERFACE_0_STARTING_INDEX                 (0U)
#define DEMALTERNATIVEDATAINTERFACE_0_NUMBER_INSTANCES               (1U)
#define DEMDATAELEMENTINSTANCE_0_STARTING_INDEX                      (0U)
#define DEMDATAELEMENTINSTANCE_0_NUMBER_INSTANCES                    (1U)


/*
* DemInternalDataElementClass Container
*  Macro Configurations
*/
#define DEMINTERNALDATAELEMENTCLASS_SIZE                             (1U)
#define DEMINTERNALDATAELEMENTCLASS_ID_0                             (0U)

/*
* DemExternalCSDataElementClass Container
*  Macro Configurations
*/
#define DEME1TERNALCSDATAELEMENTCLASS_SIZE                           (1U)
#define DEMEXTERNALCSDATAELEMENTCLASS_ID_0                           (0U)

/*
* DemDidClass Container
*  Macro Configurations
*/
#define DEMDIDCLASS_SIZE                                             (0U)

/*
* DemGeneralOBD Container
*  Macro Configurations
*/
#define DEMGENERALOBD_SIZE                                           (1U)
#define DEMGENERALOBD_ID_0                                           (0U)
#define DEMCALLBACKOBDDTCSTATUSCHANGED_0_STARTING_INDEX              (0U)
#define DEMCALLBACKOBDDTCSTATUSCHANGED_0_NUMBER_INSTANCES            (1U)


/*
* DemCallbackOBDDTCStatusChanged Container
*  Macro Configurations
*/
#define DEMCALLBACKOBDDTCSTATUSCHANGED_SIZE                          (1U)
#define DEMCALLBACKOBDDTCSTATUSCHANGED_ID_0                          (0U)

/*
* DemEnableCondition Container
*  Macro Configurations
*/
#define DEMENABLECONDITION_SIZE                                      (3U)
#define DEMENABLECONDITION_ID_0                                      (0U)
#define DEMENABLECONDITION_ID_1                                      (1U)
#define DEMENABLECONDITION_ID_2                                      (2U)

/*
* DemEnableConditionGroup Container
*  Macro Configurations
*/
#define DEMENABLECONDITIONGROUP_SIZE                                 (3U)
#define DEMENABLECONDITIONGROUP_ID_0                                 (0U)
#define DEMENABLECONDITIONGROUP_ID_1                                 (1U)
#define DEMENABLECONDITIONGROUP_ID_2                                 (2U)

/*
* DemEventMemorySet Container
*  Macro Configurations
*/
#define DEMEVENTMEMORYSET_SIZE                                       (3U)
#define DEMEVENTMEMORYSET_ID_0                                       (0U)
#define DEMCLEARDTCNOTIFICATION_0_STARTING_INDEX                     (0U)
#define DEMCLEARDTCNOTIFICATION_0_NUMBER_INSTANCES                   (1U)
#define DEMINDICATOR_0_STARTING_INDEX                                (0U)
#define DEMINDICATOR_0_NUMBER_INSTANCES                              (1U)
#define DEMMIRRORMEMORY_0_STARTING_INDEX                             (0U)
#define DEMMIRRORMEMORY_0_NUMBER_INSTANCES                           (1U)
#define DEMPRIMARYMEMORY_0_STARTING_INDEX                            (0U)
#define DEMPRIMARYMEMORY_0_NUMBER_INSTANCES                          (1U)
#define DEMUSERDEFINEDMEMORY_0_STARTING_INDEX                        (0U)
#define DEMUSERDEFINEDMEMORY_0_NUMBER_INSTANCES                      (1U)

#define DEMEVENTMEMORYSET_ID_1                                       (1U)
#define DEMPRIMARYMEMORY_1_STARTING_INDEX                            (1U)
#define DEMPRIMARYMEMORY_1_NUMBER_INSTANCES                          (1U)

#define DEMEVENTMEMORYSET_ID_2                                       (2U)
#define DEMPRIMARYMEMORY_2_STARTING_INDEX                            (2U)
#define DEMPRIMARYMEMORY_2_NUMBER_INSTANCES                          (1U)


/*
* DemClearDTCNotification Container
*  Macro Configurations
*/
#define DEMCLEARDTCNOTIFICATION_SIZE                                 (1U)
#define DEMCLEARDTCNOTIFICATION_ID_0                                 (0U)

/*
* DemIndicator Container
*  Macro Configurations
*/
#define DEMINDICATOR_SIZE                                            (1U)
#define DEMINDICATOR_ID_0                                            (0U)

/*
* DemMirrorMemory Container
*  Macro Configurations
*/
#define DEMMIRRORMEMORY_SIZE                                         (1U)
#define DEMMIRRORMEMORY_ID_0                                         (0U)

/*
* DemPrimaryMemory Container
*  Macro Configurations
*/
#define DEMPRIMARYMEMORY_SIZE                                        (3U)
#define DEMPRIMARYMEMORY_ID_0                                        (0U)
#define DEMPRIMARYMEMORY_ID_1                                        (1U)
#define DEMPRIMARYMEMORY_ID_2                                        (2U)

/*
* DemUserDefinedMemory Container
*  Macro Configurations
*/
#define DEMUSERDEFINEDMEMORY_SIZE                                    (1U)
#define DEMUSERDEFINEDMEMORY_ID_0                                    (0U)

/*
* DemExtendedDataClass Container
*  Macro Configurations
*/
#define DEME3TENDEDDATACLASS_SIZE                                    (3U)
#define DEMEXTENDEDDATACLASS_ID_0                                    (0U)
#define DEMEXTENDEDDATACLASS_ID_1                                    (1U)
#define DEMEXTENDEDDATACLASS_ID_2                                    (2U)

/*
* DemExtendedDataRecordClass Container
*  Macro Configurations
*/
#define DEME0TENDEDDATARECORDCLASS_SIZE                              (0U)

/*
* DemExtendedDataRecordClass Container
*  Macro Configurations
*/
#define DEME0TENDEDDATARECORDCLASS_SIZE                              (0U)

/*
* DemFreezeFrameClass Container
*  Macro Configurations
*/
#define DEMFREEZEFRAMECLASS_SIZE                                     (3U)
#define DEMFREEZEFRAMECLASS_ID_0                                     (0U)
#define DEMFREEZEFRAMECLASS_ID_1                                     (1U)
#define DEMFREEZEFRAMECLASS_ID_2                                     (2U)

/*
* DemFreezeFrameRecNumClass Container
*  Macro Configurations
*/
#define DEMFREEZEFRAMERECNUMCLASS_SIZE                               (3U)
#define DEMFREEZEFRAMERECNUMCLASS_ID_0                               (0U)
#define DEMFREEZEFRAMERECNUMCLASS_ID_1                               (1U)
#define DEMFREEZEFRAMERECNUMCLASS_ID_2                               (2U)

/*
* DemFreezeFrameRecordClass Container
*  Macro Configurations
*/
#define DEMFREEZEFRAMERECORDCLASS_SIZE                               (3U)
#define DEMFREEZEFRAMERECORDCLASS_ID_0                               (0U)
#define DEMFREEZEFRAMERECORDCLASS_ID_1                               (1U)
#define DEMFREEZEFRAMERECORDCLASS_ID_2                               (2U)

/*
* DemFreezeFrameRecordClass Container
*  Macro Configurations
*/
#define DEMFREEZEFRAMERECORDCLASS_SIZE                               (3U)
#define DEMFREEZEFRAMERECORDCLASS_ID_0                               (0U)
#define DEMFREEZEFRAMERECORDCLASS_ID_1                               (1U)
#define DEMFREEZEFRAMERECORDCLASS_ID_2                               (2U)

/*
* DemGroupOfDTC Container
*  Macro Configurations
*/
#define DEMGROUPOFDTC_SIZE                                           (3U)
#define DEMGROUPOFDTC_ID_0                                           (0U)
#define DEMGROUPOFDTC_ID_1                                           (1U)
#define DEMGROUPOFDTC_ID_2                                           (2U)

/*
* DemNvRamBlockId Container
*  Macro Configurations
*/
#define DEMNVRAMBLOCKID_SIZE                                         (3U)
#define DEMNVRAMBLOCKID_ID_0                                         (0U)
#define DEMNVRAMBLOCKID_ID_1                                         (1U)
#define DEMNVRAMBLOCKID_ID_2                                         (2U)

/*
* DemOperationCycle Container
*  Macro Configurations
*/
#define DEMOPERATIONCYCLE_SIZE                                       (3U)
#define DEMOPERATIONCYCLE_ID_0                                       (0U)
#define DEMOPERATIONCYCLE_ID_1                                       (1U)
#define DEMOPERATIONCYCLE_ID_2                                       (2U)

/*
* DemRatio Container
*  Macro Configurations
*/
#define DEMRATIO_SIZE                                                (3U)
#define DEMRATIO_ID_0                                                (0U)
#define DEMRATIO_ID_1                                                (1U)
#define DEMRATIO_ID_2                                                (2U)

/*
* DemStorageCondition Container
*  Macro Configurations
*/
#define DEMSTORAGECONDITION_SIZE                                     (3U)
#define DEMSTORAGECONDITION_ID_0                                     (0U)
#define DEMSTORAGECONDITION_ID_1                                     (1U)
#define DEMSTORAGECONDITION_ID_2                                     (2U)

/*
* DemStorageConditionGroup Container
*  Macro Configurations
*/
#define DEMSTORAGECONDITIONGROUP_SIZE                                (3U)
#define DEMSTORAGECONDITIONGROUP_ID_0                                (0U)
#define DEMSTORAGECONDITIONGROUP_ID_1                                (1U)
#define DEMSTORAGECONDITIONGROUP_ID_2                                (2U)

/*
* DemComponent Container
*  Macro Configurations
*/
#define DEMCOMPONENT_SIZE                                            (3U)
#define DEMCOMPONENT_ID_0                                            (0U)
#define DEMCOMPONENT_ID_1                                            (1U)
#define DEMCOMPONENT_ID_2                                            (2U)

/*
* DemDTC Container
*  Macro Configurations
*/
#define DEMDTC_SIZE                                                  (3U)
#define DEMDTC_ID_0                                                  (0U)
#define DEMDTC_ID_1                                                  (1U)
#define DEMDTC_ID_2                                                  (2U)

/*
* DemDTCAttributes Container
*  Macro Configurations
*/
#define DEMDTCATTRIBUTES_SIZE                                        (3U)
#define DEMDTCATTRIBUTES_ID_0                                        (0U)
#define DEMDTCATTRIBUTES_ID_1                                        (1U)
#define DEMDTCATTRIBUTES_ID_2                                        (2U)

/*
* DemEventParameter Container
*  Macro Configurations
*/

#define DEMEVENTPARAMETER_SIZE                                       (2U)
#define DEMEVENTPARAMETER_ID_0                                       (0U)
#define DEMCALLBACKCLEAREVENTALLOWED_0_STARTING_INDEX                (0U)
#define DEMCALLBACKCLEAREVENTALLOWED_0_NUMBER_INSTANCES              (1U)
#define DEMCALLBACKEVENTDATACHANGED_0_STARTING_INDEX                 (0U)
#define DEMCALLBACKEVENTDATACHANGED_0_NUMBER_INSTANCES               (1U)
#define DEMCALLBACKEVENTUDSSTATUSCHANGED_0_STARTING_INDEX            (0U)
#define DEMCALLBACKEVENTUDSSTATUSCHANGED_0_NUMBER_INSTANCES          (1U)
#define DEMCALLBACKINITMFORE_0_STARTING_INDEX                        (0U)
#define DEMCALLBACKINITMFORE_0_NUMBER_INSTANCES                      (1U)
#define DEMCALLBACKMONITORSTATUSCHANGED_0_STARTING_INDEX             (0U)
#define DEMCALLBACKMONITORSTATUSCHANGED_0_NUMBER_INSTANCES           (1U)
#define DEMDEBOUNCECOUNTERBASED_0_STARTING_INDEX                     (0U)
#define DEMDEBOUNCECOUNTERBASED_0_NUMBER_INSTANCES                   (1U)
#define DEMINDICATORATTRIBUTE_0_STARTING_INDEX                       (0U)
#define DEMINDICATORATTRIBUTE_0_NUMBER_INSTANCES                     (1U)



/*
* DemMultiEventTriggering Container
*  Macro Configurations
*/
#define DEMMULTIEVENTTRIGGERING_SIZE                                 (3U)
#define DEMMULTIEVENTTRIGGERING_ID_0                                 (0U)
#define DEMMULTIEVENTTRIGGERING_ID_1                                 (1U)
#define DEMMULTIEVENTTRIGGERING_ID_2                                 (2U)

/*
* DemObdDTC Container
*  Macro Configurations
*/
#define DEMOBDDTC_SIZE                                               (1U)
#define DEMOBDDTC_ID_0                                               (0U)

/*
* DemPidClass Container
*  Macro Configurations
*/
#define DEMPIDCLASS_SIZE                                             (1U)
#define DEMPIDCLASS_ID_0                                             (0U)
#define DEMPIDDATAELEMENT_0_STARTING_INDEX                           (0U)
#define DEMPIDDATAELEMENT_0_NUMBER_INSTANCES                         (1U)


/*
* DemDtr Container
*  Macro Configurations
*/
#define DEMDTR_SIZE                                                  (1U)
#define DEMDTR_ID_0                                                  (0U)



/******************************************************************************************
***************************************Dem Module's***************************************
**************************************Reference Types**************************************
******************************************************************************************/

#define DEMCOMPONENT_REFERENCE_TYPE                           (1U)
#define DEMDTCATTRIBUTES_REFERENCE_TYPE                       (2U)
#define DEMOBDDTC_REFERENCE_TYPE                              (3U)
#define DEMOPERATIONCYCLE_REFERENCE_TYPE                      (4U)
#define DEMEXTENDEDDATACLASS_REFERENCE_TYPE                   (5U)
#define DEMFREEZEFRAMECLASS_REFERENCE_TYPE                    (6U)
#define DEMFREEZEFRAMERECNUMCLASS_REFERENCE_TYPE              (7U)
#define DEMJ1939FREEZEFRAMECLASS_REFERENCE_TYPE               (8U)
#define DEMMIRRORMEMORY_REFERENCE_TYPE                        (9U)
#define DEMPRIMARYMEMORY_REFERENCE_TYPE                       (10U)
#define DEMUSERDEFINEDMEMORY_REFERENCE_TYPE                   (11U)
#define DEMEVENTPARAMETER_REFERENCE_TYPE                      (12U)
#define DEMDEBOUNCECOUNTERBASEDCLASS_REFERENCE_TYPE           (13U)
#define DEMDEBOUNCETIMEBASECLASS_REFERENCE_TYPE               (14U)
#define DEMINDICATOR_REFERENCE_TYPE                           (15U)
#define DEMDTC_REFERENCE_TYPE                                 (16U)
#define DEMENABLECONDITIONGROUP_REFERENCE_TYPE                (17U)
#define DEMSTORAGECONDITIONGROUP_REFERENCE_TYPE               (18U)
#define DEMDATAELEMENTCLASS_REFERENCE_TYPE                    (19U)
#define DEMEVENTMEMORYSET_REFERENCE_TYPE                      (20U)
#define DEMENABLECONDITION_REFERENCE_TYPE                     (21U)
#define DEMEXTENDEDDATARECORDCLASS_REFERENCE_TYPE             (22U)
#define DEMDIDCLASS_REFERENCE_TYPE                            (23U)
#define DEMFREEZEFRAMERECORDCLASS_REFERENCE_TYPE              (24U)
#define DEMSPNCLASS_REFERENCE_TYPE                            (25U)
#define DEMEXTERNALCSDATAELEMENTCLASS_REFERENCE_TYPE          (26U)
#define DEMEXTERNALSRDATAELEMENTCLASS_REFERENCE_TYPE          (27U)
#define DEMINTERNALDATAELEMENTCLASS_REFERENCE_TYPE            (28U)
#define NVMBLOCKDESCRIPTOR_REFERENCE_TYPE                     (29U)
#define FIMFID_REFERENCE_TYPE                                 (30U)
#define DEMSTORAGECONDITION_REFERENCE_TYPE                    (31U)




/******************************************************************************************
***************************************Dem Module's***************************************
**********************************Choice Container Types**********************************
******************************************************************************************/

#define DEMDEBOUNCECOUNTERBASED_CONTAINER_TYPE                         (1U)
#define DEMDEBOUNCEMONITORINTERNAL_CONTAINER_TYPE                      (2U)
#define DEMDEBOUNCETIMEBASE_CONTAINER_TYPE                             (3U)
#define DEMEXTERNALCSDATAELEMENTCLASS_CONTAINER_TYPE                   (4U)
#define DEMEXTERNALSRDATAELEMENTCLASS_CONTAINER_TYPE                   (5U)
#define DEMALTERNATIVEDATAINTERFACE_CONTAINER_TYPE                     (6U)
#define DEMALTERNATIVEDATATYPE_CONTAINER_TYPE                          (7U)
#define DEMALTERNATIVEDIAGNOSTICDATAELEMENT_CONTAINER_TYPE             (8U)
#define DEMDATAELEMENTINSTANCE_CONTAINER_TYPE                          (9U)
#define DEMSUBELEMENTINDATAELEMENTINSTANCE_CONTAINER_TYPE              (10U)
#define DEMSUBELEMENTINIMPLDATAELEMENTINSTANCE_CONTAINER_TYPE          (11U)
#define DEMINTERNALDATAELEMENTCLASS_CONTAINER_TYPE                     (12U)




/******************************************************************************************
***************************************Dem Module's***************************************
***************************************Enumerations***************************************
******************************************************************************************/

#define DEM_SEVERITY_CHECK_AT_NEXT_HALT                        (0U)
#define DEM_SEVERITY_CHECK_IMMEDIATELY                         (1U)
#define DEM_SEVERITY_MAINTENANCE_ONLY                          (2U)
#define DEM_SEVERITY_NO_SEVERITY                               (3U)
#define DURING_SHUTDOWN                                        (0U)
#define IMMEDIATE_AT_FIRST_OCCURRENCE                          (1U)
#define DEM_DTC_WWHOBD_CLASS_A                                 (0U)
#define DEM_DTC_WWHOBD_CLASS_B1                                (1U)
#define DEM_DTC_WWHOBD_CLASS_B2                                (2U)
#define DEM_DTC_WWHOBD_CLASS_C                                 (3U)
#define DEM_DTC_WWHOBD_CLASS_NOCLASS                           (4U)
#define DEM_EVENT_SIGNIFICANCE_FAULT                           (0U)
#define DEM_EVENT_SIGNIFICANCE_OCCURRENCE                      (1U)
#define DEM_DEBOUNCE_FREEZE                                    (0U)
#define DEM_DEBOUNCE_RESET                                     (1U)
#define DEM_DTR_UPDATE_ALWAYS                                  (0U)
#define DEM_DTR_UPDATE_STEADY                                  (1U)
#define DEM_NO_STATUS_BYTE_CHANGE                              (0U)
#define DEM_ONLY_THIS_CYCLE_AND_READINESS                      (1U)
#define DEM_INDICATOR_BLINKING                                 (0U)
#define DEM_INDICATOR_BLINK_CONT                               (1U)
#define DEM_INDICATOR_CONTINUOUS                               (2U)
#define DEM_INDICATOR_FAST_FLASH                               (3U)
#define DEM_INDICATOR_SLOW_FLASH                               (4U)
#define DEM_EVENT_KIND_BSW                                     (0U)
#define DEM_EVENT_KIND_SWC                                     (1U)
#define REPORT_AFTER_INIT                                      (0U)
#define REPORT_BEFORE_INIT                                     (1U)
#define DEM_OBD_RDY_AC                                         (0U)
#define DEM_OBD_RDY_BOOSTPR                                    (1U)
#define DEM_OBD_RDY_CAT                                        (2U)
#define DEM_OBD_RDY_CMPRCMPT                                   (3U)
#define DEM_OBD_RDY_EGR                                        (4U)
#define DEM_OBD_RDY_EGSENS                                     (5U)
#define DEM_OBD_RDY_EVAP                                       (6U)
#define DEM_OBD_RDY_FLSYS                                      (7U)
#define DEM_OBD_RDY_FLSYS_NONCONT                              (8U)
#define DEM_OBD_RDY_HCCAT                                      (9U)
#define DEM_OBD_RDY_HTCAT                                      (10U)
#define DEM_OBD_RDY_MISF                                       (11U)
#define DEM_OBD_RDY_NONE                                       (12U)
#define DEM_OBD_RDY_NOXCAT                                     (13U)
#define DEM_OBD_RDY_O2SENS                                     (14U)
#define DEM_OBD_RDY_O2SENSHT                                   (15U)
#define DEM_OBD_RDY_PMFLT                                      (16U)
#define DEM_OBD_RDY_SECAIR                                     (17U)
#define DEM_CLIENT_ONLY_USES_EVENTOVERFLOW_INTERFACE           (0U)
#define DEM_CLIENT_USES_FULL_FUNCTIONALITY                     (1U)
#define BOOLEAN                                                (0U)
#define SINT16                                                 (1U)
#define SINT32                                                 (2U)
#define SINT8                                                  (3U)
#define UINT16                                                 (4U)
#define UINT32                                                 (5U)
#define UINT8                                                  (6U)
#define BIG_ENDIAN                                             (0U)
#define LITTLE_ENDIAN                                          (1U)
#define OPAQUE                                                 (2U)
#define DEM_AGINGCTR_DOWNCNT                                   (0U)
#define DEM_AGINGCTR_UPCNT                                     (1U)
#define DEM_AGINGCTR_UPCNT_FIRST_ACTIVE                        (2U)
#define DEM_CLR_DIST                                           (3U)
#define DEM_CLR_TIME                                           (4U)
#define DEM_CURRENT_FDC                                        (5U)
#define DEM_CYCLES_SINCE_FIRST_FAILED                          (6U)
#define DEM_CYCLES_SINCE_LAST_FAILED                           (7U)
#define DEM_FAILED_CYCLES                                      (8U)
#define DEM_MAX_FDC_DURING_CURRENT_CYCLE                       (9U)
#define DEM_MAX_FDC_SINCE_LAST_CLEAR                           (10U)
#define DEM_MIL_DIST                                           (11U)
#define DEM_MIL_TIME                                           (12U)
#define DEM_OCCCTR                                             (13U)
#define DEM_OVFLIND                                            (14U)
#define DEM_SIGNIFICANCE                                       (15U)
#define DEM_WARM_UPS                                           (16U)
#define FINISH                                                 (0U)
#define START                                                  (1U)
#define DEM_DTC_TRANSLATION_ISO11992_4                         (0U)
#define DEM_DTC_TRANSLATION_ISO14229_1                         (1U)
#define DEM_DTC_TRANSLATION_ISO15031_6                         (2U)
#define DEM_DTC_TRANSLATION_SAEJ1939_73                        (3U)
#define DEM_DTC_TRANSLATION_SAE_J2012_DA_DTCFORMAT_04          (4U)
#define DEM_TRIGGER_ON_CONFIRMED                               (0U)
#define DEM_TRIGGER_ON_FDC_THRESHOLD                           (1U)
#define DEM_TRIGGER_ON_MIRROR                                  (2U)
#define DEM_TRIGGER_ON_PASSED                                  (3U)
#define DEM_TRIGGER_ON_PENDING                                 (2U)
#define DEM_TRIGGER_ON_TEST_FAILED                             (2U)
#define DEM_UPDATE_RECORD_NO                                   (0U)
#define DEM_UPDATE_RECORD_YES                                  (1U)
#define DEM_IGNITION_COMPRESSION                               (0U)
#define DEM_IGNITION_SPARK                                     (1U)
#define DEM_IUMPR_DEN_500MILL                                  (0U)
#define DEM_IUMPR_DEN_COLDSTART                                (1U)
#define DEM_IUMPR_DEN_EVAP                                     (2U)
#define DEM_IUMPR_DEN_NONE                                     (3U)
#define DEM_IUMPR_DEN_PHYS_API                                 (4U)
#define DEM_IUMPR_AFRI1                                        (0U)
#define DEM_IUMPR_AFRI2                                        (1U)
#define DEM_IUMPR_BOOSTPRS                                     (2U)
#define DEM_IUMPR_CAT1                                         (3U)
#define DEM_IUMPR_CAT2                                         (4U)
#define DEM_IUMPR_EGR                                          (5U)
#define DEM_IUMPR_EGSENSOR                                     (6U)
#define DEM_IUMPR_EVAP                                         (7U)
#define DEM_IUMPR_FLSYS                                        (8U)
#define DEM_IUMPR_NMHCCAT                                      (9U)
#define DEM_IUMPR_NOXADSORB                                    (10U)
#define DEM_IUMPR_NOXCAT                                       (11U)
#define DEM_IUMPR_OXS1                                         (12U)
#define DEM_IUMPR_OXS2                                         (13U)
#define DEM_IUMPR_PF1                                          (14U)
#define DEM_IUMPR_PF2                                          (15U)
#define DEM_IUMPR_PMFILTER                                     (16U)
#define DEM_IUMPR_PRIVATE                                      (17U)
#define DEM_IUMPR_SAIR                                         (18U)
#define DEM_IUMPR_SECOXS1                                      (19U)
#define DEM_IUMPR_SECOXS2                                      (20U)
#define DEM_RATIO_API                                          (0U)
#define DEM_RATIO_OBSERVER                                     (1U)
#define DEM_EVENT_AVAILABILITY                                 (0U)
#define DEM_NO_AVAILABILITY                                    (1U)
#define DEM_CLRRESP_NONVOLATILE_FINISH                         (0U)
#define DEM_CLRRESP_NONVOLATILE_TRIGGER                        (1U)
#define DEM_CLRRESP_VOLATILE                                   (2U)
#define DEM_ALL_SUPPORTED_DTCS                                 (0U)
#define DEM_ONLY_CLEAR_ALL_DTCS                                (1U)
#define DEM_CAPTURE_ASYNCHRONOUS_TO_REPORTING                  (0U)
#define DEM_CAPTURE_SYNCHRONOUS_TO_REPORTING                   (1U)
#define DEM_EVCOMB_DISABLED                                    (0U)
#define DEM_EVCOMB_ONRETRIEVAL                                 (1U)
#define DEM_EVCOMB_ONSTORAGE                                   (2U)
#define DEM_DISPLACEMENT_FULL                                  (0U)
#define DEM_DISPLACEMENT_NONE                                  (1U)
#define DEM_DISPLACEMENT_PRIO_OCC                              (2U)
#define DEM_OBD_DEP_SEC_ECU                                    (0U)
#define DEM_OBD_MASTER_ECU                                     (1U)
#define DEM_OBD_NO_OBD_SUPPORT                                 (2U)
#define DEM_OBD_PRIMARY_ECU                                    (3U)
#define DEM_PROCESS_OCCCTR_CDTC                                (0U)
#define DEM_PROCESS_OCCCTR_TF                                  (1U)
#define DEM_STATUS_BIT_AGING_AND_DISPLACEMENT                  (0U)
#define DEM_STATUS_BIT_NORMAL                                  (1U)
#define DEM_DTC_SUPPRESSION                                    (0U)
#define DEM_NO_SUPPRESSION                                     (1U)
#define DEM_FF_RECNUM_CALCULATED                               (0U)
#define DEM_FF_RECNUM_CONFIGURED                               (1U)




/******************************************************************************************
***************************************Dem Module's***************************************
**************************************Default Values**************************************
******************************************************************************************/

#define DEFAULT_PARAMETER_8BIT_VALUE            (255U)
#define DEFAULT_PARAMETER_16BIT_VALUE           (65535U)
#define DEFAULT_PARAMETER_32BIT_VALUE           (4294967295U)
#define DEFAULT_PARAMETER_64BIT_VALUE           (18446744073709551615U)
#define DEFAULT_PARAMETER_BOOLEAN_VALUE         (0U)
#define DEFAULT_PARAMETER_ENUM_VALUE            (21U)
#define DEFAULT_PARAMETER_STRING_VALUE          ("\0")
#define DEFAULT_REFERENCE_TYPE                  (0U)
#define DEFAULT_REFERENCE_NUMBER_INSTANCES      (0U)
#define DEFAULT_REFERENCE_VALUE                 ((void *)0)
#define DEFAULT_PARAMETER_FUNCTION_NAME_VALUE   ((void *)0)
#define DEFAULT_CONTAINER_TYPE                  (0U)
#define DEFAULT_CONTAINER_STARTING_VALUE        (0U)
#define DEFAULT_CONTAINER_NUMBER_INSTANCES      (0U)
#define FALSE                                   (0U)
#define TRUE                                    (1U)




#endif
