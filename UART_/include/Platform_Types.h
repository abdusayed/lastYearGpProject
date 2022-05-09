#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H
typedef _Bool      			boolean;
typedef char         		sint8;
typedef unsigned char   	uint8;
typedef signed short       	sint16;
typedef unsigned short  	uint16;
typedef signed long        	sint32;
typedef unsigned long  		uint32;
typedef signed long long   	sint64;
typedef unsigned long long	uint64;
typedef unsigned long       uint8_least;
typedef unsigned long       uint16_least;
typedef unsigned long       uint32_least;
typedef signed long         sint8_least;
typedef signed long         sint16_least;
typedef signed long         sint32_least;
typedef float               float32;
typedef double              float64;


typedef volatile char vint8_t;
typedef volatile uint8 vuint8_t;

typedef volatile sint16 vint16_t;
typedef volatile uint16 vuint16_t;

typedef volatile sint32 vint32_t;
typedef volatile uint32 vuint32_t;

typedef volatile sint64 vint64_t;
typedef volatile uint64 vuint64_t;


//Optimized integer data types
/** Boolean data type. **/

#ifndef FALSE
#define FALSE		(0U)
#endif
#ifndef TRUE
#define TRUE		(1U)
#endif

#ifndef False
#define False		(boolean)0
#endif
#ifndef True
#define True		(boolean)1
#endif

#endif
