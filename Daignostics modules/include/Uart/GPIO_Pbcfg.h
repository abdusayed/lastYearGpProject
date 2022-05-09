#include"Platform_Types.h"

typedef uint8 Enum_Port_Type;
#define PORTA   (0u)
#define PORTB   (1)
#define PORTC   (2)
#define PORTD   (3)
#define PORTE   (4)
#define PORTF   (5)

/*Advanced Perphiral Bus Base addresses*/
#define PORTA_APB_BASE    0x40004000
#define PORTB_APB_BASE    0x40005000
#define PORTC_APB_BASE    0x40006000
#define PORTD_APB_BASE    0x40007000
#define PORTE_APB_BASE    0x40024000
#define PORTF_APB_BASE    0x40025000

/*Advanced Perphiral Bus Base addresses*/
#define PORTA_AHB_BASE    0x40058000
#define PORTB_AHB_BASE    0x40059000
#define PORTC_AHB_BASE    0x4005A000
#define PORTD_AHB_BASE    0x4005B000
#define PORTE_AHB_BASE    0x4005C000
#define PORTF_AHB_BASE    0x4005D000

typedef struct
{ 
   Enum_Port_Type   Port;
}str_PortConfig_t;

extern str_PortConfig_t portObj ;
