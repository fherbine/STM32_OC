#include <STM32f10x.h>

#define TRUE 1
#define FALSE 0

typedef unsigned char		u8;
typedef unsigned short	u16;
typedef unsigned int		u32;

typedef signed char			s8;
typedef signed short		s16;
typedef signed int			s32;

s32	main(void)
{
	RCC->APB2ENR = RCC->APB2ENR | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN; // mandatory to use GPIOs
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // mandatory to use timer2
	
	while (TRUE)
	{
		__nop();
	}
	return(0);
}
