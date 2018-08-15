#include "uart.h"

s32 main(void)
{
	configure_gpio_alt_push_pull(GPIOA, 9);
	init_uart1_9600();
	print_alpha();
	while (TRUE);
	return(EXIT_SUCCESS);
}
