#include <STM32f10x.h>

#define TRUE	1
#define FALSE	0

typedef unsigned char		u8;
typedef unsigned short	u16;
typedef unsigned int		u32;

typedef signed char			s8;
typedef signed short		s16;
typedef signed int			s32;

u8		blink = FALSE;

void	init_gpio_c3(void)
{
	GPIOC->CRL &= ~(0xF << 12);
	GPIOC->CRL |= (0x3 << 12);
}

void	open_close_gpio_c3(void)
{
	GPIOC->ODR ^= (0x1 << 3);
}

void	init_usr_but(void)
{
	GPIOC->CRH &= ~(0xF << 20);
	GPIOC->CRH |= (0x8 << 20);
	
	EXTI->RTSR |= (0x1 << 3);
	EXTI->SWIER |= (0x1 << 3);
	
	NVIC->ISER[0] |= (0x1 << 9);
	NVIC->IP[9] |= (7 << 4);
}

void EXTI3_IRQHandler(void)
{
	EXTI->PR &= ~(0x1 << 3);
	blink ^= 1;
}

void	init_tim3(u32 autoreload, u32 prescaler)
{
	TIM3->ARR = autoreload;
	TIM3->PSC = prescaler;
	
	TIM3->DIER |= TIM_DIER_UIE; // Enable interrupts for timer 3
	NVIC->ISER[0] |= (0x1 << 29); // We could use NVIC_ISER_29 instead of (0x1 << 29)
	NVIC->IP[29] |= (8 << 4); // set priority
	
	TIM3->CR1 |= TIM_CR1_CEN; // Enable timer1
}

void	init_all(void)
{
	init_gpio_c3();
	init_usr_but();
	init_tim3(9999, 7199);
}

void	TIM3_IRQHandler(void)
{
	TIM3->SR &= ~TIM_SR_UIF;
	if (blink)
		open_close_gpio_c3();
}

s32		main(void)
{
 	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	
	init_all();
	
	while(TRUE)
	{
		if (!(GPIOC->IDR & (0x1 << 13)))
			blink ^= 1;
		__nop();
	}
	return (0);
}
