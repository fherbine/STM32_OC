#include "uart.h"

s32	configure_gpio_alt_push_pull(GPIO_TypeDef *gpio, u8 pin)
{
	if (gpio == GPIOA)
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	else if (gpio == GPIOB)
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	else if (gpio == GPIOC)
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	else
		return(EXIT_FAILURE);
	if (pin < 8)
	{
		gpio->CRL &= ~(0xF << 4*pin);
		gpio->CRL |= (0xA << 4*pin);
	}
	else if (pin < 15)
	{
		gpio->CRH &= ~(0xF << 4*pin);
		gpio->CRH |= (0xA << 4*pin);
	}
	else
		return(EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
