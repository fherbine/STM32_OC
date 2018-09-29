#ifndef BT_H
# define BT_H

# include <stm32f10x.h>

typedef unsigned char		u8;
typedef unsigned short	u16;
typedef unsigned int		u32;

typedef signed char			s8;
typedef signed short		s16;
typedef signed int			s32;

# define PCLK1 36000000
# define PCLK2 72000000

# define USART_RX 0
# define USART_TX 1
# define USART_RX_TX 2

s8 											config_gpio_alt_pp(GPIO_TypeDef *gpio, u8 pin);

void 										UART_init(USART_TypeDef *USART, u8 mode, u32 baud_rate);
u8											USART_Read_Data_Byte(USART_TypeDef *USART);
void										USART_Send_Data_Byte(USART_TypeDef *USART, u8 data);
u32											fh_strlen(u8 *str);
void										u_putchar(USART_TypeDef *USART, u8 c);
void										u_putstr(USART_TypeDef *USART, u8 *str);
void										u_putendl(USART_TypeDef *USART, u8 *str);
#endif