#include <STM32f10x.h>

#define TRUE 1
#define FALSE 0

typedef unsigned char		u8;
typedef unsigned short	u16;
typedef unsigned int		u32;

typedef signed char			s8;
typedef signed short		s16;
typedef signed int			s32;

void	config_gpio_c3(void)
{
	GPIOC->CRL &= ~(0xF << 12);
	GPIOC->CRL |= (0x3 << 12);
}

void	config_usr_but(void)
{
	GPIOC->CRH &= ~(0xF << 20);
	GPIOC->CRH |= (0x8 << 20);
}

s32		main(void)
{
	RCC->APB2ENR = RCC->APB2ENR | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN; // mandatory to use GPIOs
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // mandatory to use timer2
	
	config_gpio_c3();
	config_usr_but();
	
	while (TRUE)
	{
		__nop();
	}
	return(0);
}
