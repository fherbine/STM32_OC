#include <STM32f10x.h>

#define TRUE	1
#define FALSE	0

typedef unsigned char		u8;
typedef unsigned short	u16;
typedef unsigned int		u32;

typedef signed char			s8;
typedef signed short		s16;
typedef signed int			s32;

s32		main(void)
{
	while(TRUE)
	{
		__nop();
	}
	return (0);
}
