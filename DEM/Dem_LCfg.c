

/******************************************************************************************
****************************************Dem Module****************************************
*********************************Link-Time Configurations*********************************
******************************************************************************************/

#include "Dem_LCfg.h"
#include "Dem_Types.h"

#define DEMEXTERNALSRDATAELEMENTCLASS_SIZE 5
#define DEMEXTENDEDDATACLASS_SIZE 5
#define DEMEXTENDEDDATARECORDCLASS_SIZE 5
#define DEMEXTERNALCSDATAELEMENTCLASS_SIZE 5

/*
* DemClient Container
*  Configuration Structure
*/

DemClient_s DemClient[DEMCLIENT_SIZE] =
{
	{
		.DemClientFunctionality = DEM_CLIENT_USES_FULL_FUNCTIONALITY,
		.DemClientId = 0,
		.DemClientUsesRte = FALSE,
		.DemEventMemorySetRef_type = DEMEVENTMEMORYSET_REFERENCE_TYPE,
		//.DemEventMemorySetRef_ptr = &DemEventMemorySet[0],
		.DemEventMemorySetRef_numberOfElements = 1,
		.DemCallbackDTCStatusChanged_startingIndex = DEMCALLBACKDTCSTATUSCHANGED_0_STARTING_INDEX,
		.DemCallbackDTCStatusChanged_numberOfInstances = DEMCALLBACKDTCSTATUSCHANGED_0_NUMBER_INSTANCES
	},
	{
		.DemClientFunctionality = DEM_CLIENT_USES_FULL_FUNCTIONALITY,
		.DemClientId = 1,
		.DemClientUsesRte = FALSE,
		.DemEventMemorySetRef_type = DEMEVENTMEMORYSET_REFERENCE_TYPE,
		//.DemEventMemorySetRef_ptr = &DemEventMemorySet[1],
		.DemEventMemorySetRef_numberOfElements = 1,
		.DemCallbackDTCStatusChanged_startingIndex = DEFAULT_CONTAINER_STARTING_VALUE,
		.DemCallbackDTCStatusChanged_numberOfInstances = DEFAULT_CONTAINER_NUMBER_INSTANCES
	},
	{
		.DemClientFunctionality = DEM_CLIENT_USES_FULL_FUNCTIONALITY,
		.DemClientId = 3,
		.DemClientUsesRte = FALSE,
		.DemEventMemorySetRef_type = DEMEVENTMEMORYSET_REFERENCE_TYPE,
		//.DemEventMemorySetRef_ptr = &DemEventMemorySet[2],
		.DemEventMemorySetRef_numberOfElements = 1,
		.DemCallbackDTCStatusChanged_startingIndex = DEFAULT_CONTAINER_STARTING_VALUE,
		.DemCallbackDTCStatusChanged_numberOfInstances = DEFAULT_CONTAINER_NUMBER_INSTANCES
	}
};
//TODO
//uint8 DemEventMemorySet[10];
/*
* DemCallbackDTCStatusChanged Container
*  Configuration Structure
*/

DemCallbackDTCStatusChanged_s DemCallbackDTCStatusChanged[DEMCALLBACKDTCSTATUSCHANGED_SIZE] =
{
    {
        .DemCallbackDTCStatusChangedFnc = DEFAULT_PARAMETER_FUNCTION_NAME_VALUE
    }
};
/*
* DemExternalSRDataElementClass Container
*  Configuration Structure
*/
DemExternalSRDataElementClass_s DemExternalSRDataElementClass[DEMEXTERNALSRDATAELEMENTCLASS_SIZE] =
{
	{
		.DemDataElementDataSize = 0,
		.DemDataElementDataType = SINT16,
		.DemDataElementEndianness = BIG_ENDIAN,
		.DemDiagnosisScaling_type = DEMALTERNATIVEDATAINTERFACE_CONTAINER_TYPE,
		.DemDiagnosisScaling_startingIndex = DEMALTERNATIVEDATAINTERFACE_0_STARTING_INDEX,
		.DemDiagnosisScaling_numberOfInstances = DEMALTERNATIVEDATAINTERFACE_0_NUMBER_INSTANCES,
		.DemSRDataElementClass_type = DEMDATAELEMENTINSTANCE_CONTAINER_TYPE,
		.DemSRDataElementClass_startingIndex = DEMDATAELEMENTINSTANCE_0_STARTING_INDEX,
		.DemSRDataElementClass_numberOfInstances = DEMDATAELEMENTINSTANCE_0_NUMBER_INSTANCES
	}
};


/*
* DemInternalDataElementClass Container
*  Configuration Structure
*/
DemInternalDataElementClass_s DemInternalDataElementClass[DEMINTERNALDATAELEMENTCLASS_SIZE] =
{
	{
		.DemDataElementDataSize = 0,
		.DemInternalDataElement = DEM_AGINGCTR_DOWNCNT
	}
};

/*
* DemExternalCSDataElementClass Container
*  Configuration Structure
*/

DemExternalCSDataElementClass_s DemExternalCSDataElementClass[DEMEXTERNALCSDATAELEMENTCLASS_SIZE] =
{
	{
		.DemDataElementDataSize = 3,
		.DemDataElementReadFnc = DEFAULT_PARAMETER_FUNCTION_NAME_VALUE,
		.DemDataElementUsePort = TRUE
	}
};



/*
* DemDidClass Container
*  Configuration Structure
*/
DemDidClass_s DemDidClass[DEMDIDCLASS_SIZE] =
{

};

/*
* DemGeneralOBD Container
*  Configuration Structure
*/
DemGeneralOBD_s DemGeneralOBD[DEMGENERALOBD_SIZE] =
{
	{
		.DemOBDDrivingCycleRef_type = DEFAULT_REFERENCE_TYPE,
		.DemOBDDrivingCycleRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemOBDDrivingCycleRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemOBDInputAcceleratorPedalInformation_type = DEFAULT_REFERENCE_TYPE,
		.DemOBDInputAcceleratorPedalInformation_ptr = DEFAULT_REFERENCE_VALUE,
		.DemOBDInputAcceleratorPedalInformation_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemOBDInputAmbientPressure_type = DEFAULT_REFERENCE_TYPE,
		.DemOBDInputAmbientPressure_ptr = DEFAULT_REFERENCE_VALUE,
		.DemOBDInputAmbientPressure_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemOBDInputAmbientTemperature_type = DEFAULT_REFERENCE_TYPE,
		.DemOBDInputAmbientTemperature_ptr = DEFAULT_REFERENCE_VALUE,
		.DemOBDInputAmbientTemperature_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemOBDInputDistanceInformation_type = DEFAULT_REFERENCE_TYPE,
		.DemOBDInputDistanceInformation_ptr = DEFAULT_REFERENCE_VALUE,
		.DemOBDInputDistanceInformation_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemOBDInputEngineSpeed_type = DEFAULT_REFERENCE_TYPE,
		.DemOBDInputEngineSpeed_ptr = DEFAULT_REFERENCE_VALUE,
		.DemOBDInputEngineSpeed_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemOBDInputEngineTemperature_type = DEFAULT_REFERENCE_TYPE,
		.DemOBDInputEngineTemperature_ptr = DEFAULT_REFERENCE_VALUE,
		.DemOBDInputEngineTemperature_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemOBDInputProgrammingEvent_type = DEFAULT_REFERENCE_TYPE,
		.DemOBDInputProgrammingEvent_ptr = DEFAULT_REFERENCE_VALUE,
		.DemOBDInputProgrammingEvent_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemOBDInputVehicleSpeed_type = DEFAULT_REFERENCE_TYPE,
		.DemOBDInputVehicleSpeed_ptr = DEFAULT_REFERENCE_VALUE,
		.DemOBDInputVehicleSpeed_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemOBDPFCCycleRef_type = DEFAULT_REFERENCE_TYPE,
		//.DemOBDPFCCycleRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemOBDPFCCycleRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemOBDTimeSinceEngineStart_type = DEFAULT_REFERENCE_TYPE,
		.DemOBDTimeSinceEngineStart_ptr = DEFAULT_REFERENCE_VALUE,
		.DemOBDTimeSinceEngineStart_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemOBDWarmUpCycleRef_type = DEFAULT_REFERENCE_TYPE,
		.DemOBDWarmUpCycleRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemOBDWarmUpCycleRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemCallbackOBDDTCStatusChanged_startingIndex = DEMCALLBACKOBDDTCSTATUSCHANGED_0_STARTING_INDEX,
		.DemCallbackOBDDTCStatusChanged_numberOfInstances = DEMCALLBACKOBDDTCSTATUSCHANGED_0_NUMBER_INSTANCES
	}
};

/*
* DemCallbackOBDDTCStatusChanged Container
*  Configuration Structure
*/
DemCallbackOBDDTCStatusChanged_s DemCallbackOBDDTCStatusChanged[DEMCALLBACKOBDDTCSTATUSCHANGED_SIZE] =
{
	{
		.DemCallbackDTCStatusChangedFnc = DEFAULT_PARAMETER_FUNCTION_NAME_VALUE
	}
};

/*
* DemEnableCondition Container
*  Configuration Structure
*/
DemEnableCondition_s DemEnableCondition[DEMENABLECONDITION_SIZE] =
{
	{
		.DemEnableConditionId = 0,
		.DemEnableConditionStatus = TRUE
	},
	{
		.DemEnableConditionId = 1,
		.DemEnableConditionStatus = TRUE
	},
	{
		.DemEnableConditionId = 3,
		.DemEnableConditionStatus = TRUE
	}
};

/*
* DemEnableConditionGroup Container
*  Configuration Structure
*/
DemEnableConditionGroup_s DemEnableConditionGroup[DEMENABLECONDITIONGROUP_SIZE] =
{
	{
		.DemEnableConditionRef_type = DEMENABLECONDITION_REFERENCE_TYPE,
		.DemEnableConditionRef_ptr = &DemEnableCondition[0],
		.DemEnableConditionRef_numberOfElements = 1
	},
	{
		.DemEnableConditionRef_type = DEMENABLECONDITION_REFERENCE_TYPE,
		.DemEnableConditionRef_ptr = &DemEnableCondition[1],
		.DemEnableConditionRef_numberOfElements = 1
	},
	{
		.DemEnableConditionRef_type = DEMENABLECONDITION_REFERENCE_TYPE,
		.DemEnableConditionRef_ptr = &DemEnableCondition[2],
		.DemEnableConditionRef_numberOfElements = 1
	}
};

/*
* DemEventMemorySet Container
*  Configuration Structure
*/
DemEventMemorySet_s DemEventMemorySet[DEMEVENTMEMORYSET_SIZE] =
{
	{
		.DemDtcStatusAvailabilityMask = 2,
		.DemMaxNumberEventEntryPermanent = 2,
		.DemTypeOfDTCSupported = DEM_DTC_TRANSLATION_ISO11992_4,
		.DemAmberWarningLampIndicatorRef_type = DEFAULT_REFERENCE_TYPE,
		.DemAmberWarningLampIndicatorRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemAmberWarningLampIndicatorRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemMILIndicatorRef_type = DEFAULT_REFERENCE_TYPE,
		.DemMILIndicatorRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemMILIndicatorRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemProtectLampIndicatorRef_type = DEFAULT_REFERENCE_TYPE,
		.DemProtectLampIndicatorRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemProtectLampIndicatorRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemRedStopLampIndicatorRef_type = DEFAULT_REFERENCE_TYPE,
		.DemRedStopLampIndicatorRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemRedStopLampIndicatorRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemClearDTCNotification_startingIndex = DEMCLEARDTCNOTIFICATION_0_STARTING_INDEX,
		.DemClearDTCNotification_numberOfInstances = DEMCLEARDTCNOTIFICATION_0_NUMBER_INSTANCES,
		.DemIndicator_startingIndex = DEMINDICATOR_0_STARTING_INDEX,
		.DemIndicator_numberOfInstances = DEMINDICATOR_0_NUMBER_INSTANCES,
		.DemMirrorMemory_startingIndex = DEMMIRRORMEMORY_0_STARTING_INDEX,
		.DemMirrorMemory_numberOfInstances = DEMMIRRORMEMORY_0_NUMBER_INSTANCES,
		.DemPrimaryMemory_startingIndex = DEMPRIMARYMEMORY_0_STARTING_INDEX,
		.DemPrimaryMemory_numberOfInstances = DEMPRIMARYMEMORY_0_NUMBER_INSTANCES,
		.DemUserDefinedMemory_startingIndex = DEMUSERDEFINEDMEMORY_0_STARTING_INDEX,
		.DemUserDefinedMemory_numberOfInstances = DEMUSERDEFINEDMEMORY_0_NUMBER_INSTANCES
	},
	{
		.DemDtcStatusAvailabilityMask = 0,
		.DemMaxNumberEventEntryPermanent = 0,
		.DemTypeOfDTCSupported = DEM_DTC_TRANSLATION_ISO11992_4,
		.DemAmberWarningLampIndicatorRef_type = DEFAULT_REFERENCE_TYPE,
		.DemAmberWarningLampIndicatorRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemAmberWarningLampIndicatorRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemMILIndicatorRef_type = DEFAULT_REFERENCE_TYPE,
		.DemMILIndicatorRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemMILIndicatorRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemProtectLampIndicatorRef_type = DEFAULT_REFERENCE_TYPE,
		.DemProtectLampIndicatorRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemProtectLampIndicatorRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemRedStopLampIndicatorRef_type = DEFAULT_REFERENCE_TYPE,
		.DemRedStopLampIndicatorRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemRedStopLampIndicatorRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemClearDTCNotification_startingIndex = DEFAULT_CONTAINER_STARTING_VALUE,
		.DemClearDTCNotification_numberOfInstances = DEFAULT_CONTAINER_NUMBER_INSTANCES,
		.DemIndicator_startingIndex = DEFAULT_CONTAINER_STARTING_VALUE,
		.DemIndicator_numberOfInstances = DEFAULT_CONTAINER_NUMBER_INSTANCES,
		.DemMirrorMemory_startingIndex = DEFAULT_CONTAINER_STARTING_VALUE,
		.DemMirrorMemory_numberOfInstances = DEFAULT_CONTAINER_NUMBER_INSTANCES,
		.DemPrimaryMemory_startingIndex = DEMPRIMARYMEMORY_1_STARTING_INDEX,
		.DemPrimaryMemory_numberOfInstances = DEMPRIMARYMEMORY_1_NUMBER_INSTANCES,
		.DemUserDefinedMemory_startingIndex = DEFAULT_CONTAINER_STARTING_VALUE,
		.DemUserDefinedMemory_numberOfInstances = DEFAULT_CONTAINER_NUMBER_INSTANCES
	},
	{
		.DemDtcStatusAvailabilityMask = 0,
		.DemMaxNumberEventEntryPermanent = 0,
		.DemTypeOfDTCSupported = DEFAULT_PARAMETER_ENUM_VALUE,
		.DemAmberWarningLampIndicatorRef_type = DEFAULT_REFERENCE_TYPE,
		.DemAmberWarningLampIndicatorRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemAmberWarningLampIndicatorRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemMILIndicatorRef_type = DEFAULT_REFERENCE_TYPE,
		.DemMILIndicatorRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemMILIndicatorRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemProtectLampIndicatorRef_type = DEFAULT_REFERENCE_TYPE,
		.DemProtectLampIndicatorRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemProtectLampIndicatorRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemRedStopLampIndicatorRef_type = DEFAULT_REFERENCE_TYPE,
		.DemRedStopLampIndicatorRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemRedStopLampIndicatorRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemClearDTCNotification_startingIndex = DEFAULT_CONTAINER_STARTING_VALUE,
		.DemClearDTCNotification_numberOfInstances = DEFAULT_CONTAINER_NUMBER_INSTANCES,
		.DemIndicator_startingIndex = DEFAULT_CONTAINER_STARTING_VALUE,
		.DemIndicator_numberOfInstances = DEFAULT_CONTAINER_NUMBER_INSTANCES,
		.DemMirrorMemory_startingIndex = DEFAULT_CONTAINER_STARTING_VALUE,
		.DemMirrorMemory_numberOfInstances = DEFAULT_CONTAINER_NUMBER_INSTANCES,
		.DemPrimaryMemory_startingIndex = DEMPRIMARYMEMORY_2_STARTING_INDEX,
		.DemPrimaryMemory_numberOfInstances = DEMPRIMARYMEMORY_2_NUMBER_INSTANCES,
		.DemUserDefinedMemory_startingIndex = DEFAULT_CONTAINER_STARTING_VALUE,
		.DemUserDefinedMemory_numberOfInstances = DEFAULT_CONTAINER_NUMBER_INSTANCES
	}
};

/*
* DemClearDTCNotification Container
*  Configuration Structure
*/
DemClearDTCNotification_s DemClearDTCNotification[DEMCLEARDTCNOTIFICATION_SIZE] =
{
	{
		.DemClearDtcNotificationFnc = DEFAULT_PARAMETER_FUNCTION_NAME_VALUE,
		.DemClearDtcNotificationTime = DEFAULT_PARAMETER_ENUM_VALUE
	}
};

/*
* DemIndicator Container
*  Configuration Structure
*/
DemIndicator_s DemIndicator[DEMINDICATOR_SIZE] =
{
	{
		.DemIndicatorID = 0
	}
};

/*
* DemMirrorMemory Container
*  Configuration Structure
*/
DemMirrorMemory_s DemMirrorMemory[DEMMIRRORMEMORY_SIZE] =
{
	{
		.DemMaxNumberEventEntryMirror = 0
	}
};

/*
* DemPrimaryMemory Container
*  Configuration Structure
*/
DemPrimaryMemory_s DemPrimaryMemory[DEMPRIMARYMEMORY_SIZE] =
{
	{
		.DemMaxNumberEventEntryPrimary = 6
	},
	{
		.DemMaxNumberEventEntryPrimary = 3
	},
	{
		.DemMaxNumberEventEntryPrimary = 3
	}
};

/*
* DemUserDefinedMemory Container
*  Configuration Structure
*/
DemUserDefinedMemory_s DemUserDefinedMemory[DEMUSERDEFINEDMEMORY_SIZE] =
{
	{
		.DemMaxNumberEventEntryUserDefined = 2,
		.DemUserDefinedMemoryIdentifier = 3
	}
};

/*
* DemExtendedDataRecordClass Container
*  Configuration Structure
*/

DemExtendedDataRecordClass_s DemExtendedDataRecordClass[DEMEXTENDEDDATARECORDCLASS_SIZE] =
{

};

/*
* DemExtendedDataClass Container
*  Configuration Structure
*/
DemExtendedDataClass_s DemExtendedDataClass[DEMEXTENDEDDATACLASS_SIZE] =
{
	{
		.DemExtendedDataRecordClassRef_type = DEMEXTENDEDDATARECORDCLASS_REFERENCE_TYPE,
		.DemExtendedDataRecordClassRef_ptr = &DemExtendedDataRecordClass[0],
		.DemExtendedDataRecordClassRef_numberOfElements = 1
	},
	{
		.DemExtendedDataRecordClassRef_type = DEMEXTENDEDDATARECORDCLASS_REFERENCE_TYPE,
		.DemExtendedDataRecordClassRef_ptr = &DemExtendedDataRecordClass[1],
		.DemExtendedDataRecordClassRef_numberOfElements = 1
	},
	{
		.DemExtendedDataRecordClassRef_type = DEMEXTENDEDDATARECORDCLASS_REFERENCE_TYPE,
		.DemExtendedDataRecordClassRef_ptr = &DemExtendedDataRecordClass[2],
		.DemExtendedDataRecordClassRef_numberOfElements = 1
	}
};





/*
* DemClass Container
*  Configuration Structure
*/
DemFreezeFrameClass_s DemFreezeFrameClass[DEMFREEZEFRAMECLASS_SIZE] =
{
	{
		.DemDidClassRef_type = DEMDIDCLASS_REFERENCE_TYPE,
		.DemDidClassRef_ptr = &DemDidClass[0],
		.DemDidClassRef_numberOfElements = 1
	},
	{
		.DemDidClassRef_type = DEMDIDCLASS_REFERENCE_TYPE,
		.DemDidClassRef_ptr = &DemDidClass[1],
		.DemDidClassRef_numberOfElements = 1
	},
	{
		.DemDidClassRef_type = DEMDIDCLASS_REFERENCE_TYPE,
		.DemDidClassRef_ptr = &DemDidClass[2],
		.DemDidClassRef_numberOfElements = 1
	}
};
/*
* DemFreezeFrameRecordClass Container
*  Configuration Structure
*/
DemFreezeFrameRecordClass_s DemFreezeFrameRecordClass[DEMFREEZEFRAMERECORDCLASS_SIZE] =
{
    {
        .DemFreezeFrameRecordNumber = 0,
        .DemFreezeFrameRecordTrigger = DEFAULT_PARAMETER_ENUM_VALUE,
        .DemFreezeFrameRecordUpdate = DEFAULT_PARAMETER_ENUM_VALUE
    },
    {
        .DemFreezeFrameRecordNumber = 0,
        .DemFreezeFrameRecordTrigger = DEFAULT_PARAMETER_ENUM_VALUE,
        .DemFreezeFrameRecordUpdate = DEFAULT_PARAMETER_ENUM_VALUE
    },
    {
        .DemFreezeFrameRecordNumber = 0,
        .DemFreezeFrameRecordTrigger = DEFAULT_PARAMETER_ENUM_VALUE,
        .DemFreezeFrameRecordUpdate = DEFAULT_PARAMETER_ENUM_VALUE
    }
};


/*
* DemFreezeFrameRecNumClass Container
*  Configuration Structure
*/
DemFreezeFrameRecNumClass_s DemFreezeFrameRecNumClass[DEMFREEZEFRAMERECNUMCLASS_SIZE] =
{
	{
		.DemFreezeFrameRecordClassRef_type = DEMFREEZEFRAMERECORDCLASS_REFERENCE_TYPE,
		.DemFreezeFrameRecordClassRef_ptr = &DemFreezeFrameRecordClass[0],
		.DemFreezeFrameRecordClassRef_numberOfElements = 1
	},
	{
		.DemFreezeFrameRecordClassRef_type = DEMFREEZEFRAMERECORDCLASS_REFERENCE_TYPE,
		.DemFreezeFrameRecordClassRef_ptr = &DemFreezeFrameRecordClass[1],
		.DemFreezeFrameRecordClassRef_numberOfElements = 1
	},
	{
		.DemFreezeFrameRecordClassRef_type = DEMFREEZEFRAMERECORDCLASS_REFERENCE_TYPE,
		.DemFreezeFrameRecordClassRef_ptr = &DemFreezeFrameRecordClass[2],
		.DemFreezeFrameRecordClassRef_numberOfElements = 1
	}
};




/*
* DemGroupOfDTC Container
*  Configuration Structure
*/
DemGroupOfDTC_s DemGroupOfDTC[DEMGROUPOFDTC_SIZE] =
{
	{
		.DemGroupDTCs = 0
	},
	{
		.DemGroupDTCs = 0
	},
	{
		.DemGroupDTCs = 0
	}
};

/*
* DemNvRamBlockId Container
*  Configuration Structure
*/
DemNvRamBlockId_s DemNvRamBlockId[DEMNVRAMBLOCKID_SIZE] =
{
	{
		.DemNvRamBlockIdRef_type = DEFAULT_REFERENCE_TYPE,
		.DemNvRamBlockIdRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemNvRamBlockIdRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES
	},
	{
		.DemNvRamBlockIdRef_type = DEFAULT_REFERENCE_TYPE,
		.DemNvRamBlockIdRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemNvRamBlockIdRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES
	},
	{
		.DemNvRamBlockIdRef_type = DEFAULT_REFERENCE_TYPE,
		.DemNvRamBlockIdRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemNvRamBlockIdRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES
	}
};

/*
* DemOperationCycle Container
*  Configuration Structure
*/
DemOperationCycle_s DemOperationCycle[DEMOPERATIONCYCLE_SIZE] =
{
	{
		.DemOperationCycleAutostart = FALSE,
		.DemOperationCycleId = 1,
		.DemLeadingCycleRef_type = DEFAULT_REFERENCE_TYPE,
		.DemLeadingCycleRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemLeadingCycleRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES
	},
	{
		.DemOperationCycleAutostart = FALSE,
		.DemOperationCycleId = 0,
		.DemLeadingCycleRef_type = DEFAULT_REFERENCE_TYPE,
		.DemLeadingCycleRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemLeadingCycleRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES
	},
	{
		.DemOperationCycleAutostart = FALSE,
		.DemOperationCycleId = 0,
		.DemLeadingCycleRef_type = DEFAULT_REFERENCE_TYPE,
		.DemLeadingCycleRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemLeadingCycleRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES
	}
};

/*
* DemRatio Container
*  Configuration Structure
*/
DemRatio_s DemRatio[DEMRATIO_SIZE] =
{
	{
		.DemIUMPRDenGroup = DEFAULT_PARAMETER_ENUM_VALUE,
		.DemIUMPRGroup = DEFAULT_PARAMETER_ENUM_VALUE,
		.DemRatioId = 0,
		.DemRatioKind = DEFAULT_PARAMETER_ENUM_VALUE,
		.DemDiagnosticEventRef_type = DEFAULT_REFERENCE_TYPE,
		.DemDiagnosticEventRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemDiagnosticEventRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemFunctionIdRef_type = DEFAULT_REFERENCE_TYPE,
		.DemFunctionIdRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemFunctionIdRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemSecondaryFunctionIdRef_type = DEFAULT_REFERENCE_TYPE,
		.DemSecondaryFunctionIdRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemSecondaryFunctionIdRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES
	},
	{
		.DemIUMPRDenGroup = DEFAULT_PARAMETER_ENUM_VALUE,
		.DemIUMPRGroup = DEFAULT_PARAMETER_ENUM_VALUE,
		.DemRatioId = 0,
		.DemRatioKind = DEFAULT_PARAMETER_ENUM_VALUE,
		.DemDiagnosticEventRef_type = DEFAULT_REFERENCE_TYPE,
		.DemDiagnosticEventRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemDiagnosticEventRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemFunctionIdRef_type = DEFAULT_REFERENCE_TYPE,
		.DemFunctionIdRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemFunctionIdRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemSecondaryFunctionIdRef_type = DEFAULT_REFERENCE_TYPE,
		.DemSecondaryFunctionIdRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemSecondaryFunctionIdRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES
	},
	{
		.DemIUMPRDenGroup = DEFAULT_PARAMETER_ENUM_VALUE,
		.DemIUMPRGroup = DEFAULT_PARAMETER_ENUM_VALUE,
		.DemRatioId = 0,
		.DemRatioKind = DEFAULT_PARAMETER_ENUM_VALUE,
		.DemDiagnosticEventRef_type = DEFAULT_REFERENCE_TYPE,
		.DemDiagnosticEventRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemDiagnosticEventRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemFunctionIdRef_type = DEFAULT_REFERENCE_TYPE,
		.DemFunctionIdRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemFunctionIdRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
		.DemSecondaryFunctionIdRef_type = DEFAULT_REFERENCE_TYPE,
		.DemSecondaryFunctionIdRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemSecondaryFunctionIdRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES
	}
};
//TODO
/*DemDebounceAlgorithmClass_s DemDebounceAlgorithmClass[10] =
{
 {



 },
};*/
DemDebounceCounterBasedClass_s DemDebounceCounterBasedClass[5] =
{
 {
  .DemDebounceBehavior = DEM_DEBOUNCE_RESET   ,
  .DemDebounceCounterDecrementStepSize = 1    ,
  .DemDebounceCounterFailedThreshold   = 15   ,
  .DemDebounceCounterIncrementStepSize = 2    ,
  .DemDebounceCounterJumpDown          = FALSE ,
  .DemDebounceCounterJumpUp            = FALSE ,
  .DemDebounceCounterPassedThreshold   = -15   ,
  .DemDebounceCounterStorage           = TRUE  ,
 },
};
DemDebounceAlgorithmClass_s DemDebounceAlgorithmClass[5]  =
{
 {
  .DebounceAlgorithm.DemDebounceCounterBasedClassRef_ptr = &DemDebounceCounterBasedClass ,
 },

};

/*
* DemStorageCondition Container
*  Configuration Structure
*/
DemStorageCondition_s DemStorageCondition[DEMSTORAGECONDITION_SIZE] =
{
	{

		.DemStorageConditionId = 0,
		.DemStorageConditionStatus = FALSE,
		.DemStorageConditionReplacementEventRef_type = DEFAULT_REFERENCE_TYPE,
		.DemStorageConditionReplacementEventRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemStorageConditionReplacementEventRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES
	},
	{
		.DemStorageConditionId = 0,
		.DemStorageConditionStatus = FALSE,
		.DemStorageConditionReplacementEventRef_type = DEFAULT_REFERENCE_TYPE,
		.DemStorageConditionReplacementEventRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemStorageConditionReplacementEventRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES
	},
	{
		.DemStorageConditionId = 0,
		.DemStorageConditionStatus = FALSE,
		.DemStorageConditionReplacementEventRef_type = DEFAULT_REFERENCE_TYPE,
		.DemStorageConditionReplacementEventRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemStorageConditionReplacementEventRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES
	}
};

/*
* DemStorageConditionGroup Container
*  Configuration Structure
*/
DemStorageConditionGroup_s DemStorageConditionGroup[DEMSTORAGECONDITIONGROUP_SIZE] =
{
	{
		.DemStorageConditionRef_type = DEFAULT_REFERENCE_TYPE,
		.DemStorageConditionRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemStorageConditionRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES
	},
	{
		.DemStorageConditionRef_type = DEFAULT_REFERENCE_TYPE,
		.DemStorageConditionRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemStorageConditionRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES
	},
	{
		.DemStorageConditionRef_type = DEFAULT_REFERENCE_TYPE,
		.DemStorageConditionRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemStorageConditionRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES
	}
};

/*
* DemComponent Container
*  Configuration Structure
*/
DemComponent_s DemComponent[DEMCOMPONENT_SIZE] =
{
	{
		.DemComponentFailedCallbackFnc = DEFAULT_PARAMETER_FUNCTION_NAME_VALUE,
		.DemComponentId = 0,
		.DemComponentIgnoresPriority = TRUE,
		.DemImmediateChildComponentRef_type = DEMCOMPONENT_REFERENCE_TYPE,
		.DemImmediateChildComponentRef_ptr = &DemComponent[0],
		.DemImmediateChildComponentRef_numberOfElements = 1
	},
	{
		.DemComponentFailedCallbackFnc = DEFAULT_PARAMETER_FUNCTION_NAME_VALUE,
		.DemComponentId = 0,
		.DemComponentIgnoresPriority = TRUE,
		.DemImmediateChildComponentRef_type = DEMCOMPONENT_REFERENCE_TYPE,
		.DemImmediateChildComponentRef_ptr = &DemComponent[1],
		.DemImmediateChildComponentRef_numberOfElements = 1
	},
	{
		.DemComponentFailedCallbackFnc = DEFAULT_PARAMETER_FUNCTION_NAME_VALUE,
		.DemComponentId = 0,
		.DemComponentIgnoresPriority = TRUE,
		.DemImmediateChildComponentRef_type = DEMCOMPONENT_REFERENCE_TYPE,
		.DemImmediateChildComponentRef_ptr = &DemComponent[2],
		.DemImmediateChildComponentRef_numberOfElements = 1
	}
};

/*
* DemDTCAttributes Container
*  Configuration Structure
*/
DemDTCAttributes_s DemDTCAttributes[DEMDTCATTRIBUTES_SIZE] =
{
    {
        .DemAgingAllowed = TRUE,
        .DemAgingCycleCounterThreshold = 4,
        .DemAgingCycleCounterThresholdForTFSLC = 3,
        .DemDTCPriority = 3,
        .DemDTCSignificance = DEM_EVENT_SIGNIFICANCE_FAULT,
        .DemMaxNumberFreezeFrameRecords = 3,
        .DemAgingCycleRef_type = DEMOPERATIONCYCLE_REFERENCE_TYPE,
        .DemAgingCycleRef_ptr = &DemOperationCycle[0],
        .DemAgingCycleRef_numberOfElements = 1,
        .DemExtendedDataClassRef_type = DEMEXTENDEDDATACLASS_REFERENCE_TYPE,
        .DemExtendedDataClassRef_ptr = &DemExtendedDataClass[0],
        .DemExtendedDataClassRef_numberOfElements = 1,
        .DemFreezeFrameClassRef_type = DEMFREEZEFRAMECLASS_REFERENCE_TYPE,
        .DemFreezeFrameClassRef_ptr = &DemFreezeFrameClass[0],
        .DemFreezeFrameClassRef_numberOfElements = 1,
        .DemFreezeFrameRecNumClassRef_type = DEMFREEZEFRAMERECNUMCLASS_REFERENCE_TYPE,
        .DemFreezeFrameRecNumClassRef_ptr = &DemFreezeFrameRecNumClass[0],
        .DemFreezeFrameRecNumClassRef_numberOfElements = 1,
        .DemJ1939ExpandedFreezeFrameClassRef_type = DEFAULT_REFERENCE_TYPE,
        .DemJ1939ExpandedFreezeFrameClassRef_ptr = DEFAULT_REFERENCE_VALUE,
        .DemJ1939ExpandedFreezeFrameClassRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
        .DemJ1939FreezeFrameClassRef_type = DEFAULT_REFERENCE_TYPE,
        .DemJ1939FreezeFrameClassRef_ptr = DEFAULT_REFERENCE_VALUE,
        .DemJ1939FreezeFrameClassRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
        .DemMemoryDestinationRef_type = DEMPRIMARYMEMORY_REFERENCE_TYPE,
        .DemMemoryDestinationRef_ptr = &DemPrimaryMemory[0],
        .DemMemoryDestinationRef_numberOfElements = 1,
        .DemWWHOBDFreezeFrameClassRef_type = DEMFREEZEFRAMECLASS_REFERENCE_TYPE,
        .DemWWHOBDFreezeFrameClassRef_ptr = &DemFreezeFrameClass[0],
        .DemWWHOBDFreezeFrameClassRef_numberOfElements = 1
    },
    {
        .DemAgingAllowed = FALSE,
        .DemAgingCycleCounterThreshold = 0,
        .DemAgingCycleCounterThresholdForTFSLC = 0,
        .DemDTCPriority = 0,
        .DemDTCSignificance = DEFAULT_PARAMETER_ENUM_VALUE,
        .DemMaxNumberFreezeFrameRecords = 0,
        .DemAgingCycleRef_type = DEFAULT_REFERENCE_TYPE,
        .DemAgingCycleRef_ptr = DEFAULT_REFERENCE_VALUE,
        .DemAgingCycleRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
        .DemExtendedDataClassRef_type = DEFAULT_REFERENCE_TYPE,
        .DemExtendedDataClassRef_ptr = DEFAULT_REFERENCE_VALUE,
        .DemExtendedDataClassRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
        .DemFreezeFrameClassRef_type = DEFAULT_REFERENCE_TYPE,
        .DemFreezeFrameClassRef_ptr = DEFAULT_REFERENCE_VALUE,
        .DemFreezeFrameClassRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
        .DemFreezeFrameRecNumClassRef_type = DEFAULT_REFERENCE_TYPE,
        .DemFreezeFrameRecNumClassRef_ptr = DEFAULT_REFERENCE_VALUE,
        .DemFreezeFrameRecNumClassRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
        .DemJ1939ExpandedFreezeFrameClassRef_type = DEFAULT_REFERENCE_TYPE,
        .DemJ1939ExpandedFreezeFrameClassRef_ptr = DEFAULT_REFERENCE_VALUE,
        .DemJ1939ExpandedFreezeFrameClassRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
        .DemJ1939FreezeFrameClassRef_type = DEFAULT_REFERENCE_TYPE,
        .DemJ1939FreezeFrameClassRef_ptr = DEFAULT_REFERENCE_VALUE,
        .DemJ1939FreezeFrameClassRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
        .DemMemoryDestinationRef_type = DEFAULT_REFERENCE_TYPE,
        .DemMemoryDestinationRef_ptr = DEFAULT_REFERENCE_VALUE,
        .DemMemoryDestinationRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
        .DemWWHOBDFreezeFrameClassRef_type = DEFAULT_REFERENCE_TYPE,
        .DemWWHOBDFreezeFrameClassRef_ptr = DEFAULT_REFERENCE_VALUE,
        .DemWWHOBDFreezeFrameClassRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES
    },
    {
        .DemAgingAllowed = FALSE,
        .DemAgingCycleCounterThreshold = 0,
        .DemAgingCycleCounterThresholdForTFSLC = 0,
        .DemDTCPriority = 0,
        .DemDTCSignificance = DEFAULT_PARAMETER_ENUM_VALUE,
        .DemMaxNumberFreezeFrameRecords = 0,
        .DemAgingCycleRef_type = DEFAULT_REFERENCE_TYPE,
        .DemAgingCycleRef_ptr = DEFAULT_REFERENCE_VALUE,
        .DemAgingCycleRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
        .DemExtendedDataClassRef_type = DEFAULT_REFERENCE_TYPE,
        .DemExtendedDataClassRef_ptr = DEFAULT_REFERENCE_VALUE,
        .DemExtendedDataClassRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
        .DemFreezeFrameClassRef_type = DEFAULT_REFERENCE_TYPE,
        .DemFreezeFrameClassRef_ptr = DEFAULT_REFERENCE_VALUE,
        .DemFreezeFrameClassRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
        .DemFreezeFrameRecNumClassRef_type = DEFAULT_REFERENCE_TYPE,
        .DemFreezeFrameRecNumClassRef_ptr = DEFAULT_REFERENCE_VALUE,
        .DemFreezeFrameRecNumClassRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
        .DemJ1939ExpandedFreezeFrameClassRef_type = DEFAULT_REFERENCE_TYPE,
        .DemJ1939ExpandedFreezeFrameClassRef_ptr = DEFAULT_REFERENCE_VALUE,
        .DemJ1939ExpandedFreezeFrameClassRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
        .DemJ1939FreezeFrameClassRef_type = DEFAULT_REFERENCE_TYPE,
        .DemJ1939FreezeFrameClassRef_ptr = DEFAULT_REFERENCE_VALUE,
        .DemJ1939FreezeFrameClassRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
        .DemMemoryDestinationRef_type = DEFAULT_REFERENCE_TYPE,
        .DemMemoryDestinationRef_ptr = DEFAULT_REFERENCE_VALUE,
        .DemMemoryDestinationRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES,
        .DemWWHOBDFreezeFrameClassRef_type = DEFAULT_REFERENCE_TYPE,
        .DemWWHOBDFreezeFrameClassRef_ptr = DEFAULT_REFERENCE_VALUE,
        .DemWWHOBDFreezeFrameClassRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES
    }
};

/*
* DemObdDTC Container
*  Configuration Structure
*/
DemObdDTC_s DemObdDTC[DEMOBDDTC_SIZE] =
{
    {
        .DemConsiderPtoStatus = TRUE,
        .DemDtcValue = 3,
        .DemEventOBDReadinessGroup = DEM_OBD_RDY_BOOSTPR,
        .DemJ1939DTCValue = 0
    }
};

/*
* DemDTC Container
*  Configuration Structure
*/
DemDTC_s DemDTC[DEMDTC_SIZE] =
{
	{
		.DemDTCFunctionalUnit = 2,
		.DemDTCSeverity = DEM_SEVERITY_NO_SEVERITY,
		.DemDtcValue = 6,
		.DemNvStorageStrategy = DURING_SHUTDOWN,
		.DemWWHOBDDTCClass = DEM_DTC_WWHOBD_CLASS_A,
		.DemDTCAttributesRef_type = DEMDTCATTRIBUTES_REFERENCE_TYPE,
		.DemDTCAttributesRef_ptr = &DemDTCAttributes[0],
		.DemDTCAttributesRef_numberOfElements = 1,
		.DemObdDTCRef_type = DEMOBDDTC_REFERENCE_TYPE,
		.DemObdDTCRef_ptr = &DemObdDTC[0],
		.DemObdDTCRef_numberOfElements = 1
	},
	{
		.DemDTCFunctionalUnit = 2,
		.DemDTCSeverity = DEM_SEVERITY_NO_SEVERITY,
		.DemDtcValue = 4,
		.DemNvStorageStrategy = DURING_SHUTDOWN,
		.DemWWHOBDDTCClass = DEM_DTC_WWHOBD_CLASS_A,
		.DemDTCAttributesRef_type = DEMDTCATTRIBUTES_REFERENCE_TYPE,
		.DemDTCAttributesRef_ptr = &DemDTCAttributes[1],
		.DemDTCAttributesRef_numberOfElements = 1,
		.DemObdDTCRef_type = DEFAULT_REFERENCE_TYPE,
		.DemObdDTCRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemObdDTCRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES
	},
	{
		.DemDTCFunctionalUnit = 5,
		.DemDTCSeverity = DEM_SEVERITY_NO_SEVERITY,
		.DemDtcValue = 3,
		.DemNvStorageStrategy = DURING_SHUTDOWN,
		.DemWWHOBDDTCClass = DEM_DTC_WWHOBD_CLASS_B2,
		.DemDTCAttributesRef_type = DEMDTCATTRIBUTES_REFERENCE_TYPE,
		.DemDTCAttributesRef_ptr = &DemDTCAttributes[2],
		.DemDTCAttributesRef_numberOfElements = 1,
		.DemObdDTCRef_type = DEFAULT_REFERENCE_TYPE,
		.DemObdDTCRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemObdDTCRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES
	}
};



/*
* DemEventParameter Container
*  Configuration Structure
*/
DemEventParameter_s DemEventParameter[DEMEVENTPARAMETER_SIZE] =
{
	{
		.DemCausalityDelayTime = 19.00,
		.DemComponentPriority = 0,
		.DemEventAvailable = TRUE,
		.DemEventConfirmationThreshold = 14,
		.DemEventFailureCycleCounterThresholdAdaptable = FALSE,
		.DemEventId = 1,
		.DemEventKind = DEM_EVENT_KIND_BSW,
		.DemEventRecoverableInSameOperationCycle = TRUE,
		.DemFFPrestorageSupported = FALSE,
		.DemReportBehavior = REPORT_BEFORE_INIT,
		.DemComponentClassRef_type = DEMCOMPONENT_REFERENCE_TYPE,
		.DemComponentClassRef_ptr = &DemComponent[0],
		.DemComponentClassRef_numberOfElements = 1,
		.DemDTCRef_type = DEMDTC_REFERENCE_TYPE,
		.DemDTCRef_ptr = &DemDTC[0],
		.DemDTCRef_numberOfElements = 1,
		.DemEnableConditionGroupRef_type = DEMENABLECONDITIONGROUP_REFERENCE_TYPE,
		.DemEnableConditionGroupRef_ptr = &DemEnableConditionGroup[1],
		.DemEnableConditionGroupRef_numberOfElements = 1,
		.DemOBDGroupingAssociativeEventsRef_type = DEMEVENTPARAMETER_REFERENCE_TYPE,
		.DemOBDGroupingAssociativeEventsRef_ptr = &DemEventParameter[0],
		.DemOBDGroupingAssociativeEventsRef_numberOfElements = 1,
		.DemOperationCycleRef_type = DEMOPERATIONCYCLE_REFERENCE_TYPE,
		.DemOperationCycleRef_ptr = &DemOperationCycle[0],
		.DemOperationCycleRef_numberOfElements = 1,
		.DemStorageConditionGroupRef_type = DEMSTORAGECONDITIONGROUP_REFERENCE_TYPE,
		.DemStorageConditionGroupRef_ptr = &DemStorageConditionGroup[1],
		.DemStorageConditionGroupRef_numberOfElements = 1,
		.DemCallbackClearEventAllowed_startingIndex = DEMCALLBACKCLEAREVENTALLOWED_0_STARTING_INDEX,
		.DemCallbackClearEventAllowed_numberOfInstances = DEMCALLBACKCLEAREVENTALLOWED_0_NUMBER_INSTANCES,
		.DemCallbackEventDataChanged_startingIndex = DEMCALLBACKEVENTDATACHANGED_0_STARTING_INDEX,
		.DemCallbackEventDataChanged_numberOfInstances = DEMCALLBACKEVENTDATACHANGED_0_NUMBER_INSTANCES,
		.DemCallbackEventUdsStatusChanged_startingIndex = DEMCALLBACKEVENTUDSSTATUSCHANGED_0_STARTING_INDEX,
		.DemCallbackEventUdsStatusChanged_numberOfInstances = DEMCALLBACKEVENTUDSSTATUSCHANGED_0_NUMBER_INSTANCES,
		.DemCallbackInitMForE_startingIndex = DEMCALLBACKINITMFORE_0_STARTING_INDEX,
		.DemCallbackInitMForE_numberOfInstances = DEMCALLBACKINITMFORE_0_NUMBER_INSTANCES,
		.DemCallbackMonitorStatusChanged_startingIndex = DEMCALLBACKMONITORSTATUSCHANGED_0_STARTING_INDEX,
		.DemCallbackMonitorStatusChanged_numberOfInstances = DEMCALLBACKMONITORSTATUSCHANGED_0_NUMBER_INSTANCES,
		.DemDebounceAlgorithmClass_type = DEMDEBOUNCECOUNTERBASED_CONTAINER_TYPE,
		.DemDebounceAlgorithmClass_startingIndex = DEMDEBOUNCECOUNTERBASED_0_STARTING_INDEX,
		.DemDebounceAlgorithmClass_numberOfInstances = DEMDEBOUNCECOUNTERBASED_0_NUMBER_INSTANCES,
		.DemIndicatorAttribute_startingIndex = DEMINDICATORATTRIBUTE_0_STARTING_INDEX,
		.DemIndicatorAttribute_numberOfInstances = DEMINDICATORATTRIBUTE_0_NUMBER_INSTANCES
	},
    {
        .DemCausalityDelayTime = 19.00,
        .DemComponentPriority = 0,
        .DemEventAvailable = TRUE,
        .DemEventConfirmationThreshold = 14,
        .DemEventFailureCycleCounterThresholdAdaptable = FALSE,
        .DemEventId = 2,
        .DemEventKind = DEM_EVENT_KIND_BSW,
        .DemEventRecoverableInSameOperationCycle = TRUE,
        .DemFFPrestorageSupported = FALSE,
        .DemReportBehavior = REPORT_BEFORE_INIT,
        .DemComponentClassRef_type = DEMCOMPONENT_REFERENCE_TYPE,
        .DemComponentClassRef_ptr = &DemComponent[0],
        .DemComponentClassRef_numberOfElements = 1,
        .DemDTCRef_type = DEMDTC_REFERENCE_TYPE,
        .DemDTCRef_ptr = &DemDTC[0],
        .DemDTCRef_numberOfElements = 1,
        .DemEnableConditionGroupRef_type = DEMENABLECONDITIONGROUP_REFERENCE_TYPE,
        .DemEnableConditionGroupRef_ptr = &DemEnableConditionGroup[1],
        .DemEnableConditionGroupRef_numberOfElements = 1,
        .DemOBDGroupingAssociativeEventsRef_type = DEMEVENTPARAMETER_REFERENCE_TYPE,
        .DemOBDGroupingAssociativeEventsRef_ptr = &DemEventParameter[0],
        .DemOBDGroupingAssociativeEventsRef_numberOfElements = 1,
        .DemOperationCycleRef_type = DEMOPERATIONCYCLE_REFERENCE_TYPE,
        .DemOperationCycleRef_ptr = &DemOperationCycle[0],
        .DemOperationCycleRef_numberOfElements = 1,
        .DemStorageConditionGroupRef_type = DEMSTORAGECONDITIONGROUP_REFERENCE_TYPE,
        .DemStorageConditionGroupRef_ptr = &DemStorageConditionGroup[1],
        .DemStorageConditionGroupRef_numberOfElements = 1,
        .DemCallbackClearEventAllowed_startingIndex = DEMCALLBACKCLEAREVENTALLOWED_0_STARTING_INDEX,
        .DemCallbackClearEventAllowed_numberOfInstances = DEMCALLBACKCLEAREVENTALLOWED_0_NUMBER_INSTANCES,
        .DemCallbackEventDataChanged_startingIndex = DEMCALLBACKEVENTDATACHANGED_0_STARTING_INDEX,
        .DemCallbackEventDataChanged_numberOfInstances = DEMCALLBACKEVENTDATACHANGED_0_NUMBER_INSTANCES,
        .DemCallbackEventUdsStatusChanged_startingIndex = DEMCALLBACKEVENTUDSSTATUSCHANGED_0_STARTING_INDEX,
        .DemCallbackEventUdsStatusChanged_numberOfInstances = DEMCALLBACKEVENTUDSSTATUSCHANGED_0_NUMBER_INSTANCES,
        .DemCallbackInitMForE_startingIndex = DEMCALLBACKINITMFORE_0_STARTING_INDEX,
        .DemCallbackInitMForE_numberOfInstances = DEMCALLBACKINITMFORE_0_NUMBER_INSTANCES,
        .DemCallbackMonitorStatusChanged_startingIndex = DEMCALLBACKMONITORSTATUSCHANGED_0_STARTING_INDEX,
        .DemCallbackMonitorStatusChanged_numberOfInstances = DEMCALLBACKMONITORSTATUSCHANGED_0_NUMBER_INSTANCES,
        .DemDebounceAlgorithmClass_type = DEMDEBOUNCECOUNTERBASED_CONTAINER_TYPE,
        .DemDebounceAlgorithmClass_startingIndex = DEMDEBOUNCECOUNTERBASED_0_STARTING_INDEX,
        .DemDebounceAlgorithmClass_numberOfInstances = DEMDEBOUNCECOUNTERBASED_0_NUMBER_INSTANCES,
        .DemIndicatorAttribute_startingIndex = DEMINDICATORATTRIBUTE_0_STARTING_INDEX,
        .DemIndicatorAttribute_numberOfInstances = DEMINDICATORATTRIBUTE_0_NUMBER_INSTANCES
    }
};

/*
* DemMultiEventTriggering Container
*  Configuration Structure
*/
DemMultiEventTriggering_s DemMultiEventTriggering[DEMMULTIEVENTTRIGGERING_SIZE] =
{
	{
		.DemMultiEventTriggeringMasterEventRef_type = DEMEVENTPARAMETER_REFERENCE_TYPE,
		.DemMultiEventTriggeringMasterEventRef_ptr = &DemEventParameter[0],
		.DemMultiEventTriggeringMasterEventRef_numberOfElements = 1,
		.DemMultiEventTriggeringSlaveEventRef_type = DEMEVENTPARAMETER_REFERENCE_TYPE,
		.DemMultiEventTriggeringSlaveEventRef_ptr = &DemEventParameter[0],
		.DemMultiEventTriggeringSlaveEventRef_numberOfElements = 1
	},
	{
		.DemMultiEventTriggeringMasterEventRef_type = DEMEVENTPARAMETER_REFERENCE_TYPE,
		.DemMultiEventTriggeringMasterEventRef_ptr = &DemEventParameter[0],
		.DemMultiEventTriggeringMasterEventRef_numberOfElements = 1,
		.DemMultiEventTriggeringSlaveEventRef_type = DEMEVENTPARAMETER_REFERENCE_TYPE,
		.DemMultiEventTriggeringSlaveEventRef_ptr = &DemEventParameter[0],
		.DemMultiEventTriggeringSlaveEventRef_numberOfElements = 1
	},
	{
		.DemMultiEventTriggeringMasterEventRef_type = DEMEVENTPARAMETER_REFERENCE_TYPE,
		.DemMultiEventTriggeringMasterEventRef_ptr = &DemEventParameter[0],
		.DemMultiEventTriggeringMasterEventRef_numberOfElements = 1,
		.DemMultiEventTriggeringSlaveEventRef_type = DEMEVENTPARAMETER_REFERENCE_TYPE,
		.DemMultiEventTriggeringSlaveEventRef_ptr = &DemEventParameter[0],
		.DemMultiEventTriggeringSlaveEventRef_numberOfElements = 1
	}
};



/*
* DemPidClass Container
*  Configuration Structure
*/
DemPidClass_s DemPidClass[DEMPIDCLASS_SIZE] =
{
	{
		.DemPidIdentifier = 2,
		.DemPidDataElement_startingIndex = DEMPIDDATAELEMENT_0_STARTING_INDEX,
		.DemPidDataElement_numberOfInstances = DEMPIDDATAELEMENT_0_NUMBER_INSTANCES
	}
};

/*
* DemDtr Container
*  Configuration Structure
*/
DemDtr_s DemDtr[DEMDTR_SIZE] =
{
	{
		.DemDtrCompuDenominator0 = 0.00,
		.DemDtrCompuNumerator0 = 0.00,
		.DemDtrCompuNumerator1 = 0.00,
		.DemDtrId = 0,
		.DemDtrMid = 0,
		.DemDtrTid = 0,
		.DemDtrUasid = 0,
		.DemDtrUpdateKind = DEFAULT_PARAMETER_ENUM_VALUE,
		.DemDtrEventRef_type = DEFAULT_REFERENCE_TYPE,
		.DemDtrEventRef_ptr = DEFAULT_REFERENCE_VALUE,
		.DemDtrEventRef_numberOfElements = DEFAULT_REFERENCE_NUMBER_INSTANCES
	}
};

