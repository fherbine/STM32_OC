# include "bt.h"

s32 main(void)
{
	config_gpio_alt_pp(GPIOA, 2);
	UART_init(USART2, USART_TX, 9600);
	
	while(1)
	{
		u_putendl(USART2, "Hello world");
	}
	return(0);
}
