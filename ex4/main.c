typedef unsigned char		u8;
typedef unsigned short	u16;
typedef unsigned int		u32;

typedef signed char			s8;
typedef signed short		s16;
typedef signed int			s32;


u32	portb_idr_status(void)
{
	u32 value;
	
	value = *(u32 *)0x40010C08;
	return (value);
}	

s32 main(void)
{
	return (0);
}
