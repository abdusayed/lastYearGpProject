#include "Dem_Types.h"
#include "Dem_LCfg.h"
#include "Dem_Cfg.h"

typedef struct
{
    uint16 DemEventId ;
    boolean DemEventAvailable ;
    DemEventKind_Enum  DemEventKind ;
    uint8 DemStorageConditionId ;
    uint32 DemDtcValue;
    sint16 occurrence;
    boolean errorStatusChanged;
    uint8 confirmationCounter;
    Dem_UdsStatusByteType   eventStatus;
    uint16                  dataSize;
    uint8                   recordNumber;
    uint8                   data[DEMMAXNUMBERPRESTOREDFF];

}EventInfo;

Std_ReturnType Get_DtcEvents(EventInfo *des_buffer , uint32 Dtc);
void Get_EventsData(EventInfo *des_buffer);
