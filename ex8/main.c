#include <stm32f10x.h>

typedef unsigned char		u8;
typedef unsigned short	u16;
typedef unsigned int		u32;

typedef signed char			s8;
typedef signed short		s16;
typedef signed int			s32;

s32 main(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // Enable clock for timer 3
	TIM3->PSC = 0;
	return (0);
}