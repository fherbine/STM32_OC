# include "bt.h"

s32 main(void)
{
	config_gpio_alt_pp(GPIOA, 9);
	UART_init(USART1, USART_TX, 9600);
	
	while(1)
	{
		u_putchar(USART1, 'A');
		int i = 0;
		while (i< 10000)
			i++;
	}
	return(0);
}
