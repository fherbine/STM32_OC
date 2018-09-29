#include "bt.h"

void 				UART_init(USART_TypeDef *USART, u8 mode, u32 baud_rate)
{
	u32 fclk = PCLK1;
	u16 brr_int = 0, brr_dec = 0;
	
	if (USART == USART1)
	{
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
		fclk = PCLK2;
	}
	else if (USART == USART2)
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	else if (USART == USART3)
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
	else 
		return ;
	
	USART->CR1 |= USART_CR1_UE; // enable USART
	USART->CR1 &= ~USART_CR1_M; // Selecting 8 bits lenght data with 1 start bit and n stop bits
	USART->CR2 &= USART_CR2_STOP; // Only one stop bit is set
	
	brr_int = (u16)(fclk / (16 * baud_rate));
	brr_dec = (u16)((float)(fclk % (16 * baud_rate)) / (float)(16 * baud_rate) * 10000);
	USART->BRR |= brr_int << 4;
	USART->BRR |= brr_dec;
	
	USART->CR1 = (mode == USART_RX || mode == USART_RX_TX) ? USART->CR1 | USART_CR1_RE : USART->CR1; // Enable or not Reception
	USART->CR1 = (mode == USART_TX || mode == USART_RX_TX) ? USART->CR1 | USART_CR1_TE : USART->CR1; // Enable or not Transmission
}

static void	USART_RX_Idle(USART_TypeDef *USART)
{
	while (!(USART->SR & USART_SR_RXNE));
}

static void USART_TX_Complete(USART_TypeDef *USART)
{
	while (!(USART->SR & USART_SR_TC));
}
	

u8					USART_Read_Data_Byte(USART_TypeDef *USART)
{
	USART_RX_Idle(USART);
	return (USART->DR);
}

void				USART_Send_Data_Byte(USART_TypeDef *USART, u8 data)
{
	USART->DR |= data;
	USART_TX_Complete(USART);
}

u32				fh_strlen(u8 *str)
{
	u32			i = 0;
	
	while (str[i])
		i++;
	return (i);
}

void			u_putchar(USART_TypeDef *USART, u8 c)
{
	USART_Send_Data_Byte(USART, c);
}

void			u_putstr(USART_TypeDef *USART, u8 *str)
{
	u32			i = 0;
	
	while (str[i])
	{
		u_putchar(USART, str[i]);
		i++;
	}
}

void			u_putendl(USART_TypeDef *USART, u8 *str)
{
	u_putstr(USART, str);
	u_putchar(USART, '\n');
}