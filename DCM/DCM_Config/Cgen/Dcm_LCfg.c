

/******************************************************************************************
****************************************Dcm Module****************************************
*********************************Link-Time Configurations*********************************
******************************************************************************************/

#include "Dcm_LCfg.h"
#include "Dcm_Types.h"



/*
* DcmDsp Container
*  Configuration Structure
*/
DcmDsp_s DcmDsp[DCMDSP_SIZE] =
{
	{
		.DcmDspDataDefaultEndianness = BIG_ENDIAN,
		.DcmDspDDDIDcheckPerSourceDID = TRUE,
		.DcmDspEnableObdMirror = TRUE,
		.DcmDspMaxDidToRead = 22,
		.DcmDspMaxPeriodicDidToRead = 36545,
		.DcmDspPowerDownTime = 67,
		.DcmResponseToEcuReset = AFTER_RESET,
		.DcmDspClearDTC_startingIndex = DCMDSPCLEARDTC_0_STARTING_INDEX,
		.DcmDspClearDTC_numberOfInstances = DCMDSPCLEARDTC_0_NUMBER_INSTANCES,
		.DcmDspComControl_startingIndex = DCMDSPCOMCONTROL_0_STARTING_INDEX,
		.DcmDspComControl_numberOfInstances = DCMDSPCOMCONTROL_0_NUMBER_INSTANCES,
		.DcmDspCommonAuthorization_startingIndex = DCMDSPCOMMONAUTHORIZATION_0_STARTING_INDEX,
		.DcmDspCommonAuthorization_numberOfInstances = DCMDSPCOMMONAUTHORIZATION_0_NUMBER_INSTANCES,
		.DcmDspControlDTCSetting_startingIndex = DCMDSPCONTROLDTCSETTING_0_STARTING_INDEX,
		.DcmDspControlDTCSetting_numberOfInstances = DCMDSPCONTROLDTCSETTING_0_NUMBER_INSTANCES,
		.DcmDspData_startingIndex = DCMDSPDATA_0_STARTING_INDEX,
		.DcmDspData_numberOfInstances = DCMDSPDATA_0_NUMBER_INSTANCES,
		.DcmDspDataInfo_startingIndex = DCMDSPDATAINFO_0_STARTING_INDEX,
		.DcmDspDataInfo_numberOfInstances = DCMDSPDATAINFO_0_NUMBER_INSTANCES,
		.DcmDspDid_startingIndex = DCMDSPDID_0_STARTING_INDEX,
		.DcmDspDid_numberOfInstances = DCMDSPDID_0_NUMBER_INSTANCES,
		.DcmDspDidInfo_startingIndex = DCMDSPDIDINFO_0_STARTING_INDEX,
		.DcmDspDidInfo_numberOfInstances = DCMDSPDIDINFO_0_NUMBER_INSTANCES,
		.DcmDspDidRange_startingIndex = DCMDSPDIDRANGE_0_STARTING_INDEX,
		.DcmDspDidRange_numberOfInstances = DCMDSPDIDRANGE_0_NUMBER_INSTANCES,
		.DcmDspMemory_startingIndex = DCMDSPMEMORY_0_STARTING_INDEX,
		.DcmDspMemory_numberOfInstances = DCMDSPMEMORY_0_NUMBER_INSTANCES,
		.DcmDspPeriodicTransmission_startingIndex = DCMDSPPERIODICTRANSMISSION_0_STARTING_INDEX,
		.DcmDspPeriodicTransmission_numberOfInstances = DCMDSPPERIODICTRANSMISSION_0_NUMBER_INSTANCES,
		.DcmDspPid_startingIndex = DCMDSPPID_0_STARTING_INDEX,
		.DcmDspPid_numberOfInstances = DCMDSPPID_0_NUMBER_INSTANCES,
		.DcmDspRequestControl_startingIndex = DCMDSPREQUESTCONTROL_0_STARTING_INDEX,
		.DcmDspRequestControl_numberOfInstances = DCMDSPREQUESTCONTROL_0_NUMBER_INSTANCES,
		.DcmDspRequestFileTransfer_startingIndex = DCMDSPREQUESTFILETRANSFER_0_STARTING_INDEX,
		.DcmDspRequestFileTransfer_numberOfInstances = DCMDSPREQUESTFILETRANSFER_0_NUMBER_INSTANCES,
		.DcmDspRoe_startingIndex = DCMDSPROE_0_STARTING_INDEX,
		.DcmDspRoe_numberOfInstances = DCMDSPROE_0_NUMBER_INSTANCES,
		.DcmDspRoutine_startingIndex = DCMDSPROUTINE_0_STARTING_INDEX,
		.DcmDspRoutine_numberOfInstances = DCMDSPROUTINE_0_NUMBER_INSTANCES,
		.DcmDspSecurity_startingIndex = DCMDSPSECURITY_0_STARTING_INDEX,
		.DcmDspSecurity_numberOfInstances = DCMDSPSECURITY_0_NUMBER_INSTANCES,
		.DcmDspSession_startingIndex = DCMDSPSESSION_0_STARTING_INDEX,
		.DcmDspSession_numberOfInstances = DCMDSPSESSION_0_NUMBER_INSTANCES,
		.DcmDspVehInfo_startingIndex = DCMDSPVEHINFO_0_STARTING_INDEX,
		.DcmDspVehInfo_numberOfInstances = DCMDSPVEHINFO_0_NUMBER_INSTANCES
	}
}