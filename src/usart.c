#include<usart.h>

#define buff_size 100
static uint8_t rx_buff[buff_size];
static volatile uint16_t rx_head = 0;
static volatile uint16_t rx_tail = 0; 

void USART_Init(USART_TypeDef *usart){
     if(usart == USART1){
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    }
    else if(usart == USART2){
        RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    }
    else if(usart == USART3){
        RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
    }
    else if(usart == UART4){
        RCC->APB1ENR |= RCC_APB1ENR_UART4EN;
    }
    else if(usart == UART5){
        RCC->APB1ENR |= RCC_APB1ENR_UART5EN;
    }
    else if(usart == USART6){
        RCC->APB2ENR |= RCC_APB2ENR_USART6EN;
    }
}

void USART_Start(USART_TypeDef *usart){
    usart->CR1 |= USART_CR1_TE;
    usart->CR1 |= USART_CR1_RE;
    usart->CR1 |= USART_CR1_UE;

}


void USART_CONFIG(USART_TypeDef *usart,uint32_t baudrate,USART_word_len_t data, USART_stop_bit_t stopbit){
    bool over8 = usart->CR1 & (USART_CR1_OVER8);

    float USART_DIV = (float)get_UsartBusClock(usart)/(float)((baudrate*8*(2-over8)));
    float fraction = (USART_DIV - (int)USART_DIV) * (8*(2-over8));

    fraction = round(fraction);
    int mantissa = (int)USART_DIV;

    if(over8){
        if(fraction>7){
            mantissa = mantissa + 1;
            fraction = 0;
        }
    }
    else{
       if(fraction > 15){
        mantissa = mantissa + 1;
        fraction = 0;
       } 
    }

    usart->BRR = 0;
    usart->BRR |= mantissa << USART_BRR_DIV_Mantissa_Pos;
    if(over8){
    usart->BRR |= (int)fraction;
    }
    else{
        usart->BRR |= (int)fraction << USART_BRR_DIV_Fraction_Pos;
    }
    usart->CR1 &= ~USART_CR1_M_Msk;
    usart->CR1 |= data << USART_CR1_M_Pos;

    usart->CR2 &= ~USART_CR2_STOP_Msk;
    usart->CR2 |= stopbit << USART_CR2_STOP_Pos;
    

}

bool USART_IsTxComplete(USART_TypeDef *usart){
    return (usart->SR & USART_SR_TC) != 0;
}
bool USART_IsRxReady(USART_TypeDef *usart){
    return (usart->SR & USART_SR_RXNE) != 0;
}

void USART_Send(USART_TypeDef *usart, uint8_t byte){
        while(!USART_IsTxComplete(usart)){}
        usart->DR = byte;
}
void USART_SendString(USART_TypeDef *usart, const char *str){
    while(*str){
        USART_Send(usart,*str++);
    }
}
void USART_SendBuffer(USART_TypeDef *usart, const uint8_t *buf, uint16_t len){

    for(uint16_t i=0;i<len;i++){
        USART_Send(usart,*buf++);
    }

}
uint8_t USART_Receive(USART_TypeDef *usart){
    while(!(usart->SR & USART_SR_RXNE)){}
    return (uint8_t)usart->DR;
}
void USART_ReceiveString(USART_TypeDef *usart, char *buf , uint16_t max_len){

        for(uint16_t i=0;i<max_len;i++){
            uint8_t data = USART_Receive(usart);
            if(data == '\r' || data == '\n'){
                buf[i] = '\0';
                return;
            }
            else{
                buf[i] = data;
            }
        }
        buf[max_len - 1] = '\0';
}


uint32_t get_UsartBusClock(USART_TypeDef *usart){
    uint8_t apb_div_table[8] ={1, 1, 1, 1, 2, 4, 8, 16};
    uint8_t bitAPB1;
    uint8_t bitAPB2; 
       
         bitAPB2 = (RCC->CFGR>>13) & 0x7;  // for APB2
        
         bitAPB1 = (RCC->CFGR>>10) & 0x7;  // for APB1 

    uint32_t APB1_clk = SystemCoreClock/apb_div_table[bitAPB1];
    uint32_t APB2_clk = SystemCoreClock/apb_div_table[bitAPB2];

    if(usart == USART1 || usart == USART6){
        return APB2_clk;
    }
    else{
        return APB1_clk;
    } 
}



//------------Interrupts and Ring buffer------------//
void USART_RX_Interrupt_Enable(USART_TypeDef *usart){
    usart->CR1 |= USART_CR1_RXNEIE;
    if(usart == USART1){
        NVIC_EnableIRQ(USART1_IRQn);
    }
    else if(usart == USART2){
        NVIC_EnableIRQ(USART2_IRQn);
    }
    else if(usart == USART3){
        NVIC_EnableIRQ(USART3_IRQn);
    }
    else if(usart == UART4){
        NVIC_EnableIRQ(UART4_IRQn);
    }
    else if(usart == UART5){
        NVIC_EnableIRQ(UART5_IRQn);
    }
    else if(usart == USART6){
        NVIC_EnableIRQ(USART6_IRQn);
    }

}

void USART_RX_Interrupt_Disable(USART_TypeDef *usart){
        usart->CR1 &= ~USART_CR1_RXNEIE;
    if(usart == USART1){
        NVIC_DisableIRQ(USART1_IRQn);
    }
    else if(usart == USART2){
        NVIC_DisableIRQ(USART2_IRQn);
    }
    else if(usart == USART3){
        NVIC_DisableIRQ(USART3_IRQn);
    }
    else if(usart == UART4){
        NVIC_DisableIRQ(UART4_IRQn);
    }
    else if(usart == UART5){
        NVIC_DisableIRQ(UART5_IRQn);
    }
    else if(usart == USART6){
        NVIC_DisableIRQ(USART6_IRQn);
    }
}

void USART_TX_Interrupt_Enable(USART_TypeDef *usart){
    usart->CR1 |= USART_CR1_TCIE;
    usart->CR1 |= USART_CR1_TXEIE;
    if(usart == USART1){
        NVIC_EnableIRQ(USART1_IRQn );
    }
    else if(usart == USART2){
        NVIC_EnableIRQ(USART2_IRQn);
    }
    else if(usart == USART3){
        NVIC_EnableIRQ(USART3_IRQn);
    }
    else if(usart == UART4){
        NVIC_EnableIRQ(UART4_IRQn);
    }
    else if(usart == UART5){
        NVIC_EnableIRQ(UART5_IRQn);
    }
    else if(usart == USART6){
        NVIC_EnableIRQ(USART6_IRQn);
    }
}
void USART_TX_Interrupt_Disable(USART_TypeDef *usart);




void USART_RX_Buffer_Init(void){
    rx_head = 0;
    rx_tail = 0;
}

void USART_RX_Buffer_Push(uint8_t byte){
    uint16_t next = (rx_head +1) % buff_size;
    if(next == rx_tail){
        return;
    }
    else{
        rx_buff[rx_head] = byte;
        rx_head = next;
    }
}


bool USART_RX_Buffer_Pop(uint8_t *byte){

    if(rx_tail == rx_head){
        return false;
    }
    else{
        *byte = rx_buff[rx_tail];
        rx_tail = (rx_tail+1) % buff_size;
        return true;
    }
}

bool USART_RX_Buffer_IsEmpty(void){
    return rx_head == rx_tail;
}

uint16_t USART_RX_Buffer_Count(void){
    return (rx_head + buff_size - rx_tail) % buff_size;
}
