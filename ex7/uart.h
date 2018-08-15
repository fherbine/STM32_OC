#ifndef UART_H
# define UART_H

# include <STM32f10x.h>

# define TRUE 1
# define FALSE 0
#	define EXIT_SUCCESS 0
# define EXIT_FAILURE -1

typedef unsigned char		u8;
typedef unsigned short	u16;
typedef unsigned int		u32;

typedef signed char			s8;
typedef signed short		s16;
typedef signed int 			s32;

void		init_uart1_9600(void);
void		uart1_send_byte(u8 data);
void 		print_alpha(void);

s32			configure_gpio_alt_push_pull(GPIO_TypeDef *gpio, u8 pin);

#endif