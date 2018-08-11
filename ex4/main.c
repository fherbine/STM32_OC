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

s32 main(void)
{
	return (0);
}
