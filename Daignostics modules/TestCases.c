/*
 * TestCases.c
 *
 *  Created on: May 3, 2021
 *      Author: Mounir
 */


#include"Dem.h"
#include"Dem_LCfg.h"
/**
 * main.c
 */
extern DemEventParameter_s DemEventParameter[DEMEVENTPARAMETER_SIZE];
extern DemDTC_s DemDTC[DEMDTC_SIZE] ;
extern DemEnableConditionGroup_s DemEnableConditionGroup[DEMENABLECONDITIONGROUP_SIZE];
extern DemFreezeFrameClass_s DemFreezeFrameClass[DEMFREEZEFRAMECLASS_SIZE];
extern DemGroupOfDTC_s DemGroupOfDTC[DEMGROUPOFDTC_SIZE];
extern DemComponent_s DemComponent[DEMCOMPONENT_SIZE] ;

Dem_ConfigType cfg =
{
 .EventParameter        = &DemEventParameter,
 .GroupOfDTC            = &DemGroupOfDTC,
 .FreezeFrameClass      = &DemFreezeFrameClass,
 .Component             = &DemComponent,
 .Dtc                   = &DemDTC,
 .EnableConditionGroup  = &DemEnableConditionGroup,
};

//TODO test case passed or fail
/********************************************************************************************/
/**
*  @brief <b>set_eventBeforPreinit</b>
*  this test case set an event before calling the Dem_PreInit() so it will return NOT_OK
*/
/********************************************************************************************/
void set_eventBeforPreinit()
{
    //Dem_SetEventStatus(1, DEM_EVENT_STATUS_PREPASSED);
    Dem_PreInit();
    Dem_Init(&cfg);
}
/********************************************************************************************/
/**
*  @brief <b>set_eventBeforinitafterPreinit</b>
*  this test case set an event after calling  Dem_PreInit() and before Dem_Init without
*  make it's operation state to start so it will return NOT_OK
*/
/********************************************************************************************/
void set_eventBeforinitafterPreinit()
{
    Dem_PreInit();
    Dem_SetEventStatus(1, DEM_EVENT_STATUS_PREPASSED);
    Dem_Init(&cfg);
}
/********************************************************************************************/
/**
*  @brief <b>set_eventBeforinitafterPreinitAndStartOperation</b>
*  this test case set an event after calling  Dem_PreInit() , Dem_SetOperationCycleState()
*  and before Dem_Init save the event in the error buffer till Dem_Init() be called
*/
/********************************************************************************************/
void set_eventBeforinitafterPreinitAndStartOperation()
{
    Dem_PreInit();
    Dem_SetOperationCycleState(1, DEM_CYCLE_STATE_START);
    Dem_SetEventStatus(1, DEM_EVENT_STATUS_PREPASSED);
    Dem_Init(&cfg);

}
/********************************************************************************************/
/**
*  @brief <b>setEventForUnavailableEvent</b>
*  this test case set an event status after making this event to Unavailable so to will
*  return NOT_OK
*/
/********************************************************************************************/
void setEventForUnavailableEvent()
{
    Dem_PreInit();
    Dem_Init(&cfg);
    Dem_SetEventAvailable(1, FALSE );
    Dem_SetEventStatus(1, DEM_EVENT_STATUS_PREPASSED);
}
/********************************************************************************************/
/**
*  @brief <b>setPrepassedStatusMoreThenThresholdValue</b>
*  this test case set an event to <b>DEM_EVENT_STATUS_PREPASSED</b> number of time more then the
*  threshold value of the passed status so it will make the event to passeds
*/
/********************************************************************************************/
void setPrepassedStatusMoreThenThresholdValue()
{
    Dem_PreInit();
    Dem_Init(&cfg);
    Dem_SetOperationCycleState(1, DEM_CYCLE_STATE_START);
    uint8 i = 0 ;
    while(i < 16)
    {
        Dem_SetEventStatus(1, DEM_EVENT_STATUS_PREPASSED);
        i++;
    }
}
/********************************************************************************************/
/**
*  @brief <b>setPrepassedStatusThenGetTheCounter</b>
*  this test case set an event status and then get the FaultDetectionCounter of that event
*  by using functtion Dem_GetFaultDetectionCounter()
*/
/********************************************************************************************/
void setPrepassedStatusThenGetTheCounter()
{
    sint8 x;
    Dem_PreInit();
    Dem_Init(&cfg);
    Dem_SetOperationCycleState(1, DEM_CYCLE_STATE_START);
    Dem_SetEventStatus(1, DEM_EVENT_STATUS_PREPASSED);
    Dem_GetFaultDetectionCounter(1,&x);
}
/********************************************************************************************/
/**
*  @brief <b>GetSuppressionOfDtcWitoutSelectDtc</b>
*  this test case uses function  Dem_GetDTCSuppression to get the availability
*  of the Dtc without using Dem_SelectDTC first so it expected to return NOT_OK
*/
/********************************************************************************************/
void GetSuppressionOfDtcWitoutSelectDtc()
{
    uint8 x;
    Dem_PreInit();
    Dem_Init(&cfg);
    Dem_SetOperationCycleState(1, DEM_CYCLE_STATE_START);
    Dem_GetDTCSuppression( 0 , &x );

}
/********************************************************************************************/
/**
*  @brief <b>GetSuppressionOfDtc</b>
*  this test case uses function Dem_SelectDTC then Dem_GetDTCSuppression to get the availability
*  of the Dtc
*/
/********************************************************************************************/
void GetSuppressionOfDtc()
{
    uint8 x;
    Dem_PreInit();
    Dem_Init(&cfg);
    Dem_SetOperationCycleState(1, DEM_CYCLE_STATE_START);
    Dem_SelectDTC(0, 6, DEM_DTC_FORMAT_UDS, DEM_DTC_ORIGIN_PRIMARY_MEMORY);
    Dem_GetDTCSuppression( 0 , &x );

}
/********************************************************************************************/
/**
*  @brief <b>GetStatusOfDTC</b>
* this test case Reset the two events which belong to the same DTC and then Get the status
* for that DTC
*/
/********************************************************************************************/
void GetStatusOfDTC()
{
    uint8 x;
    Dem_PreInit();
    Dem_Init(&cfg);
    Dem_SetOperationCycleState(1, DEM_CYCLE_STATE_START);
    Dem_ResetEventStatus(1);
    Dem_ResetEventStatus(2);
    Dem_SelectDTC(0,6,DEM_DTC_FORMAT_UDS,DEM_DTC_ORIGIN_PRIMARY_MEMORY);
    Dem_GetStatusOfDTC( 0 ,&x);

}
/********************************************************************************************/
/**
*  @brief <b>GetStatusOfDTC</b>
* this test case uses function Dem_GetDTCOfEvent to get the DTC number of the Two events 1
* and 2
*/
/********************************************************************************************/
void GetDTCOfEvent(void)
{
    uint32 x;
    Dem_PreInit();
    Dem_Init(&cfg);
    Dem_SetOperationCycleState(1, DEM_CYCLE_STATE_START);
    Dem_GetDTCOfEvent(1, DEM_DTC_FORMAT_UDS, &x);
    Dem_GetDTCOfEvent(2, DEM_DTC_FORMAT_UDS, &x);

}

void setFailedtatus(void)
{
    sint8 x;
    Dem_PreInit();
    Dem_Init(&cfg);
    Dem_SetOperationCycleState(1, DEM_CYCLE_STATE_START);
    Dem_SetEventStatus(1, DEM_EVENT_STATUS_FAILED);
    Dem_SetOperationCycleState(2, DEM_CYCLE_STATE_START);
    Dem_SetEventStatus(2, DEM_EVENT_STATUS_FAILED);
    Dem_SetOperationCycleState(3, DEM_CYCLE_STATE_START);
    Dem_SetEventStatus(3, DEM_EVENT_STATUS_FAILED);
    Dem_GetFaultDetectionCounter(1,&x);
}

