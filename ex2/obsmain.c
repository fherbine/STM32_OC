#include <STM32f10x.h>   
 
char modulo;  
 
void configure(){  
    RCC->APB2ENR |=  RCC_APB2ENR_IOPAEN ;   
    GPIOA->CRL = GPIOA->CRL & ~(0xF << 4*5);    
    GPIOA->CRL = GPIOA->CRL | (0x01 << 4*5);  
}  
  
void blink(){  
    char cycle = 10;
    modulo = modulo+1; 
 
    if (modulo %cycle == 0) 
    { 
        modulo = 0; 
        GPIOA->ODR ^= (1 << 5);  
    } 
}  
  
int main (void)   {   
    configure();  
    while(1)    
    {    
        blink();   
    }    
 
    return 0 ;   
}