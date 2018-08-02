typedef signed char			s8;
typedef signed short		s16;
typedef signed int			s32;

typedef unsigned char		u8;
typedef unsigned short	u16;
typedef unsigned int		u32;


u8											data = 0;

void	TIM2_IRQHandler(void)
{
	data = (data >= 0xFFFF) ? 0 : data + 1;
}

int		main(void)
{
	NVIC->IP[28] = 11<<4; // Setting priority for TIMER2 (28) to 11, bitwise operation needed
	NVIC->ISER[0] = NVIC->ISER[0] | (0x01 << 28); // Enabled TIMER2 interrupt
}
