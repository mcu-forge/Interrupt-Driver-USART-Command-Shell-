#include<usart.h>
#include<gpio.h>

volatile bool flag = 0;

void USART2_IRQHandler(void){
    if(USART2->SR & USART_SR_RXNE){
        USART_RX_Buffer_Push((uint8_t)(USART2->DR & 0xFFU));
    }
}   


int main(){
    GPIO_Init(GPIOD);
    GPIO_Init(GPIOA);

    GPIO_MODE(GPIOA,2,GPIO_MODE_AF);
    GPIO_MODE(GPIOA,3,GPIO_MODE_AF);
    GPIO_MODE(GPIOD,13,GPIO_MODE_OUTPUT);
    GPIO_MODE(GPIOD,12,GPIO_MODE_OUTPUT);

    GPIO_AF(GPIOA,2,GPIO_AF_7);
    GPIO_AF(GPIOA,3,GPIO_AF_7);

    USART_Init(USART2);
    USART_CONFIG(USART2,115200,BIT_8,STOP_BIT_1);
    USART_Start(USART2);
    USART_RX_Buffer_Init();
    USART_RX_Interrupt_Enable(USART2);

    while (1)
    {    
      
        if(get_UsartBusClock(USART2) == 16000000){
            GPIO_SET(GPIOD,13);
        }
        else{
            GPIO_RESET(GPIOD,13);
        }
        uint8_t byte;
        if (USART_RX_Buffer_Pop(&byte)) {
            if (byte == 'a')
                GPIO_SET(GPIOD, 12);
            else
                GPIO_RESET(GPIOD, 12);
        } 

    }
   


return 0;    
}