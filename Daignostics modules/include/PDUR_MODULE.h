/******************************************************************************
 * Module      : PduR Demo                                                    *
 * File Name   : PDUR_MODULE.h                                                *
 * Description : Header file of PduR Demo                                     *
 * Created on  : April 6, 2020                                                *
 ******************************************************************************/

#ifndef PDUR_MODULE_H_
#define PDUR_MODULE_H_

#include "DiagHandler.h"
#include "Dcm.h"
#include "Dcm_Lcfg.h"

//#include "tm4c123gh6pm.h"


/*******************************************************
 *            Test Cases for Dsl Sub-Module            *
 *******************************************************/

/*
 * Start Of Reception test cases :
 */

#define REQUEST_WITH_NON_CONFIGURED_ID                                      FALSE
#define REQUEST_WITH_TOTAL_SIZE_EQUAL_TO_ZERO                               FALSE
#define REQUEST_WITH_TOTAL_SIZE_LARGER_THAN_DCM_BUFFER                      FALSE
#define REQUEST_CAME_ACROSS_LOCKED_BUFFER                                   FALSE
#define PHYSICAL_TESTER_PRESENT_REQUEST_CAME_ACROSS_LOCKED_BUFFER           FALSE
#define FUNCTIONAL_TESTER_PRESENT_REQUEST_ANOTHER_CONNECTION                FALSE
#define ALL_VERIFICATIONS_PASSED_GLOBAL_BUFFER                              FALSE
#define ALL_VERIFICATIONS_PASSED_LOCAL_BUFFER                               FALSE


/*
 * CoyRx Test Cases :
 */

#define GLOBAL_LOCKED_BUFFER_PROVIDED_PDUR_BUT_EMPTY                        FALSE
#define COPYING_LARGE_DATA_IN_GLOBAL_BUFFER                                 FALSE
#define COPYING_TESTER_PRESENT_DATA_IN_LOCAL_BUFFER                         FALSE


/*
 * Rx_Indication Test Cases :
 */

#define PDUR_CALLING_WITH_PARA_E_NOT_OK                                     FALSE
#define PDUR_CALLING_WITH_PARA_E_OK_GLOBAL_BUFFER_USED                      FALSE
#define PDUR_CALLING_WITH_PARA_E_OK_LOCAL_BUFFER_USED                       FALSE



#define DCM_DSL_DIAG_RESP_MAX_NUM_RESP_PEND_EXCEEDED                       FALSE



/**********************************
 *  Test Cases for DSD Sub-Module *
 **********************************/

#define SID_OUT_OF_RANGE                                                    FALSE
#define SID_NOT_SUPPORTED                                                   FALSE
#define NON_DEFAULT_SERVICE                                                 FALSE
#define SERVICE_WITH_SECURITY_LEV_1                                         FALSE
#define SERVICE_WITH_SUPPRESSED_POS_RES                                     FALSE


/**********************************
 *  Test Cases for DSP Sub-Module *
 **********************************/


/*
 * Tester present and session control test cases
 */

#define SESSION_CONTROL_WITHOUT_TESTER_PRESENT                              FALSE
#define PHYSICAL_TESTER_PRESENT_WITHOUT_SESSION_CONTROL                     FALSE
#define SESSION_CONTROL_WITH_FUNCTIONAL_TESTER_PRESENT                      FALSE


/*
 * Security Access test cases
 */

#define SECURITY_ACCESS_BEFORE_BOOT_TIMER_EXPIRED                          FALSE
#define SECURITY_ACCESS_GET_SEED_AND_COMPARE_KEY                           FALSE
#define SECURITY_ACCESS_TEST_FAILD_CASES_PENDING                           FALSE

/*
 * Read Data By ID test cases
 */

#define PRESENTATION_DEMO  TRUE

#define READ_DATA_BY_ID_WITH_INVALID_SESSION             FALSE
#define READ_DATA_BY_ID_WITH_VALID_SESSION_INVALID_SEC   FALSE
#define READ_DATA_BY_ID_WITH_VALID_SESSION_VALID_SEC     FALSE
#define READ_DATA_BY_ID_TWO_DID_SYN_ASYN                 FALSE

/*
 * Routine Control test cases
 */
#define ROUTINE_CONTROL_TESTING                          FALSE

/*
 * Write Data By ID test cases
 */

#define WRITE_DATA_BY_ID                                 FALSE



extern void Pdur_main(void);

extern Std_ReturnType PduR_DcmTransmit(PduIdType TxPduId, PduInfoType *TxPduInfo);


#endif /* PDUR_MODULE_H_ */
