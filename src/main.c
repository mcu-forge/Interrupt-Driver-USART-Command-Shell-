#include<usart.h>
#include<gpio.h>
#include<ring_buffer.h>

#define ring_mem_len 64

#define LEN 100
char data[LEN];
uint8_t idx = 0 ;

uint8_t rx_ring_mem[ring_mem_len];
uint8_t tx_ring_mem[ring_mem_len];

ring_t rx_ring;
ring_t tx_ring;

void USART2_IRQHandler(void){
    if(USART2->SR & USART_SR_RXNE){
       ring_push(&rx_ring,(uint8_t)(USART2->DR & 0xFFU));
    }
//----------------------------------------------------------//
    if(USART2->SR & USART_SR_TXE){
        uint8_t byte;
        if(ring_pop(&tx_ring, &byte)){
            USART2->DR = byte;
        } 
        else {
            USART2->CR1 &= ~USART_CR1_TXEIE;
            USART2->CR1 |=  USART_CR1_TCIE;
        }
    }
//------------------------------------------------------------//
        if(USART2->SR & USART_SR_TC){
        USART2->CR1 &= ~USART_CR1_TCIE; 
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

    ring_init(&rx_ring,rx_ring_mem,ring_mem_len);
    ring_init(&tx_ring,tx_ring_mem,ring_mem_len);
    USART_RX_Interrupt_Enable(USART2);
    USART_TX_Interrupt_Enable(USART2);


    while (1)
    {   
        char *msg = "Starting...\r\n";
        while(*msg){
            ring_push(&tx_ring,*msg++);
        }
        USART2->CR1 |= USART_CR1_TXEIE;

        if(get_UsartBusClock(USART2) == 16000000){
            GPIO_SET(GPIOD, 13);
        }
        else{
            GPIO_RESET(GPIOD, 13);
        } 
        for(volatile uint32_t i=0;i<=10000;i++){__asm("NOP");}
        // uint8_t byte;
        // if(ring_pop(&rx_ring,&byte)){
        //     if(byte == '\r' || byte == '\n'){
        //         data[idx] = '\0';
        //         idx = 0;
        //     }
        //     else{
        //         data[idx++] = byte;
        //     }
            
        // }
        // if(strcmp(data,"This is a test message") == 0){GPIO_SET(GPIOD,GPIO_PIN_12);}
        // else{GPIO_RESET(GPIOD,GPIO_PIN_12);}


    }                                                   


return 0;    
}

