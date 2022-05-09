
#ifndef NVM_TYPES_H_
#define NVM_TYPES_H_

#include "Std_Types.h"
#if defined(CFG_NVM_USE_SERVICE_COMPONENT)
#include "Rte_NvM.h"
#endif


typedef uint8 NvM_RequestResultType;    /** @req NVM470 */
#define NVM_REQ_OK                  0x00
#define NVM_REQ_NOT_OK              0x01
#define NVM_REQ_PENDING             0x02
#define NVM_REQ_INTEGRITY_FAILED    0x03
#define NVM_REQ_BLOCK_SKIPPED       0x04
#define NVM_REQ_NV_INVALIDATED      0x05
#define NVM_REQ_CANCELLED           0x06


/* 0 and 1 is reserved, sequential order */
#if !defined(_DEFINED_TYPEDEF_FOR_NvM_BlockIdType_)
typedef uint16 NvM_BlockIdType;
#endif

#define NVM_MULTI_BLOCK_REQUEST_ID          0
#define NVM_REDUNDANT_BLOCK_FOR_CONFIG_ID   1


#endif /*NVM_TYPES_H_*/
