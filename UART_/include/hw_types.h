#include"Platform_Types.h"
//*****************************************************************************

//

// Macros for hardware access, both direct and via the bit-band region.

//

//*****************************************************************************


#define HWREG(x)                                                              \
        (*((volatile unsigned long *)(x)))

#define HWREGH(x)   (*((volatile uint16 *)(x)))

#define HWREGB(x)   (*((volatile uint8 *)(x)))

#define HWREGBITW(x, b)  HWREG(((uint32)(x) & 0xF0000000) | 0x02000000 |  (((uint32)(x) & 0x000FFFFF) << 5) | ((b) << 2))

#define HWREGBITH(x, b)  HWREGH(((uint32)(x) & 0xF0000000) | 0x02000000 |  (((uint32)(x) & 0x000FFFFF) << 5) | ((b) << 2))

#define HWREGBITB(x, b)  HWREGB(((uint32)(x) & 0xF0000000) | 0x02000000 |  (((uint32)(x) & 0x000FFFFF) << 5) | ((b) << 2))
