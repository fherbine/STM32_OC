#include "STM32f10x.h"
int main (void) 
{
    RCC->APB2ENR |=  RCC_APB2ENR_IOPAEN ;
    GPIOA->CRL = GPIOA->CRL & ~(0xF << 4*5); 
    GPIOA->CRL = GPIOA->CRL | (0x01 << 4*5);
    while(1) 
    { 
        GPIOA->ODR ^= (1 << 5);
    } 
    return (0); 
}
