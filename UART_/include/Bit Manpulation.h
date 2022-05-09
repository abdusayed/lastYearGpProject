
#ifndef _BIT_MATH_H
#define _BIT_MATH_H

#define SET_BIT(x,i) x|=(1<<(i))
#define CLR_BIT(x,i) x&=~(1<<(i))
#define TOGGLE_BIT(x,i) x^=(1<<(i))
#define GET_BIT(x,i) (x>>(i))&1
#define CLR_BITS(x,i,Mask) x&=~(Mask<<(i))




#endif
