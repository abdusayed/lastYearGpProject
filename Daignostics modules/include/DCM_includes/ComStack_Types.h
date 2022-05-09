/******************************************************************************
 * File Name   : ComStack_Types.h                                             *
 * Description : Header file of CommStack Common Types                        *
 * Created on  : April 6, 2020                                                *
 ******************************************************************************/


#ifndef INCLUDE_COMSTACK_TYPES_H_
#define INCLUDE_COMSTACK_TYPES_H_


#include <stdint.h>
#include "Com_Types.h"


/* Module Version 1.0.0 */
#define COMSTACK_TYPES_SW_MAJOR_VERSION           (1U)
#define COMSTACK_TYPES_SW_MINOR_VERSION           (0U)
#define COMSTACK_TYPES_SW_PATCH_VERSION           (0U)

/* AUTOSAR Version 4.3.1 */
#define COMSTACK_TYPES_AR_RELEASE_MAJOR_VERSION   (4U)
#define COMSTACK_TYPES_AR_RELEASE_MINOR_VERSION   (3U)
#define COMSTACK_TYPES_AR_RELEASE_PATCH_VERSION   (1U)



typedef uint32 TPParameterType ;
typedef uint32 PduIdType ;
typedef uint32 PduLengthType ;

typedef enum
{
    BUFREQ_OK,                         /*: success */
    BUFREQ_E_NOT_OK,                   /*: development error detected */
    BUFREQ_E_BUSY,                     /*: all buffers in use */
    BUFREQ_E_OVFL                      /*: requested buffer too large */
}BufReq_ReturnType ;


typedef struct
{
   uint8*            SduDataPtr;
   uint8*            MetaDataPtr;
   PduLengthType     SduLength;
} PduInfoType;
typedef enum
{
    TP_DATACONF,
    TP_DATARETRY,
    TP_CONFPENDING,
    TP_NORETRY,
} TpDataStateType;

typedef struct
{
    TpDataStateType TpDataState;
    PduLengthType TxTpDataCnt;
} RetryInfoType;

typedef uint8 NotifResultType;

#define NTFRSLT_OK                      0x00
#define NTFRSLT_E_NOT_OK                0x01
#define NTFRSLT_E_CANCELATION_NOT_OK    0x0C
#define NTFRSLT_E_WRONG_SN              0x05
#define NTFRSLT_E_NO_BUFFER             0x09


typedef uint8 BusTrcvErrorType;

/*
    [SWS_COMTYPE_00039]
    IcomConfigIdType defines the configuration ID. An ID of 0 is the defaultconfiguration.
    An ID greater than 0 shall identify a configuration for Pretended Networking.
    There is more than 1 configuration possible.
*/
typedef uint8 IcomConfigIdType;
/*
    [SWS_COMTYPE_00040]
    IcomSwitch_ErrorType defines the errors which can occur when activating or
    deactivating Pretended Networking.
    1- The activation of Pretended Networking was successful.
    2- The activation of Pretended Networking was not successful
*/
typedef uint8 IcomSwitch_ErrorType;
#define ICOM_SWITCH_E_OK      ((IcomSwitch_ErrorType) 0x00U)
#define ICOM_SWITCH_E_FAILED  ((IcomSwitch_ErrorType) 0x01U)


#define BUSTRCV_NO_ERROR    0x00
#define BUSBUSTRCV_E_ERROR  0x01


#define COMSTACKTYPE_AR_MINOR_VERSION       1
#define COMSTACKTYPE_AR_MAJOR_VERSION       0
#define COMSTACKTYPE_AR_PATCH_VERSION       0

typedef uint8 NetworkHandleType;


#endif /* INCLUDE_COMSTACK_TYPES_H_ */
