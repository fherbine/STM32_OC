#include <STM32f10x.h>

#define TRUE 1
#define FALSE 0

typedef unsigned char		u8;
typedef unsigned short	u16;
typedef unsigned int		u32;

typedef signed char			s8;
typedef signed short		s16;
typedef signed int			s32;


/*	Simple value checking on IDR port B	*/

u32	portb_idr_status(void)
{
	u32 value;
	
	value = *(u32 *)0x40010C08; // RM0008 - ref. man p.50 ==> address for Input Data Register for port B (offset 0x08)
	return (value);
}


/*	Simple value checking on ODR port B	*/

u32	portb_odr_status(void)
{
	u32 value;
	
	value = *(u32 *)0x40010C0C; // Same for Output Data register (ODR) for GPIO port B
	return (value);
}


/*	Same as port B IDR, with simple synthax and port A	*/

u32 porta_idr_status_new(void)
{
	u32 value;
	
	value = GPIOA->IDR;
	return (value);
}


void gpio_c3_config(void)
{
	GPIOC->CRL = GPIOC->CRL & ~(0xF << 4*3);
	GPIOC->CRL = GPIOC->CRL | (0x3 << 4*3);
}

void open_close_gpio_c3(void)
{
	GPIOC->ODR = GPIOC->ODR ^ (1 << 3);
}

void basic_wait(void)
{
	u16 c = 0;
	
	while (c < 0xFF)
		c++;
}

s32 main(void)
{
	RCC->APB2ENR = RCC->APB2ENR | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN;
	
	
	gpio_c3_config();
	open_close_gpio_c3();
	
	while (TRUE) {
	open_close_gpio_c3();
	}
	return (0);
}
