#ifndef __DATATYPE_H__
#define __DATATYPE_H__

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

#ifndef __cplusplus
    typedef unsigned char bool;
	#define true 1
    #define false 0
#endif

#define ITEMS_OF(_array_) (sizeof(_array_)/sizeof(_array_[0]))

#endif // __DATATYPE_H__
