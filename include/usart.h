#ifndef USART_H
#define USART_H


#include<stm32f407xx.h>
#include<core_cm4.h>
#include<string.h>
#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<math.h>


typedef enum{
    BIT_8 = 0U,
    BIT_9 = 1U,
}USART_word_len_t;

typedef enum{
    STOP_BIT_1   = 0U,
    STOP_BIT_0_5 = 1U,
    STOP_BIT_2   = 2U,
    STOP_BIT_1_5 = 3U,
}USART_stop_bit_t;

void USART_Init(USART_TypeDef *usart);
void USART_Start(USART_TypeDef *usart);
void USART_CONFIG(USART_TypeDef *usart,
uint32_t baudrate,USART_word_len_t data, USART_stop_bit_t stopbit);
bool USART_IsTxComplete(USART_TypeDef *usart);
bool USART_IsRxReady(USART_TypeDef *usart);
void USART_Send(USART_TypeDef *usart, uint8_t byte);
void USART_SendString(USART_TypeDef *usart, const char *str);
void USART_SendBuffer(USART_TypeDef *usart, const uint8_t *buf, uint16_t len);
uint8_t USART_Receive(USART_TypeDef *usart);
void USART_ReceiveString(USART_TypeDef *usart, char *buf , uint16_t max_len);


//------------Interrupts------------//
void USART_RX_Interrupt_Enable(USART_TypeDef *usart);
void USART_RX_Interrupt_Disable(USART_TypeDef *usart);
void USART_TX_Interrupt_Enable(USART_TypeDef *usart);
void USART_Interrupt_Init(USART_TypeDef *usart);
void USART_Receive_IT(USART_TypeDef *usart, char *str, uint16_t max_len);
void USART_Send_IT(USART_TypeDef *usart,const uint8_t *buf, uint16_t size);

void USART_RX_Buffer_Init(void);
void USART_RX_Buffer_Push(uint8_t byte);
bool USART_RX_Buffer_Pop(uint8_t *byte);
bool USART_RX_Buffer_IsEmpty(void);
uint16_t USART_RX_Buffer_Count(void);

uint32_t get_UsartBusClock(USART_TypeDef *usart);







#endif
