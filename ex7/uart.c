#include "uart.h"

void	init_uart1_9600(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	USART1->CR1 |= USART_CR1_UE; // Enable UART1
	USART1->CR1 &= ~USART_CR1_M; // 8 data bits
	USART1->CR2 &= USART_CR2_STOP; // Setting only one stop bit
	USART1->BRR |= (468 << 4); // integer part of the baud rate divider
	USART1->BRR |= 75; // Decimal part of the baud rate divider
	USART1->CR1 |= USART_CR1_TE; // Enable transmitter >> send first waiting trame
}

void	uart1_send_byte(u8 data)
{
	USART1->DR |= data;
	while (!(USART1->SR));
}

void print_alpha(void)
{
	u8 data = 'A';
	u8 c = 0;
	
	while (c < 26)
	{
		uart1_send_byte(data+c);
		c++;
	}
}
