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

void	open_close_c3(void)
{
	GPIOC->ODR ^= (0x1 << 3);
}

void	config_usr_but(void)
{
	GPIOC->CRH &= ~(0xF << 20);
	GPIOC->CRH |= (0x8 << 20);
}

void	init_tim2(u32 reload, u32 prescaler)
{
	TIM2->ARR = reload;
	TIM2->PSC = prescaler;
}

void	init_1sec_tim(void)
{
	init_tim2(9999, 7199);
}

void	start_tim2(void)
{
	TIM2->CR1 |= 0x1; // we can write TIM2->CR1 |= TIM1_CR1_CEN instead
}

s32		main(void)
{
	u8 start = 0;
	RCC->APB2ENR = RCC->APB2ENR | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN; // mandatory to use GPIOs
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // mandatory to use timer2
	
	config_gpio_c3();
	config_usr_but();
	
	init_1sec_tim();
	start_tim2();
	
	while (TRUE)
	{
		if (!(GPIOC->IDR & (0x1 << 13)))
			start = (start)? 0 : 1;
		if (start && (TIM2->SR & TIM_SR_UIF)) // If an overflow occured
		{
			open_close_c3();
			TIM2->SR &= ~TIM_SR_UIF;
		}
	}
	return(0);
}
