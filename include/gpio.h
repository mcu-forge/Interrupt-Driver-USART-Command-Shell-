#ifndef GPIO_H
#define GPIO_H


#include<stm32f407xx.h>
#include<stdbool.h>
#include<stdint.h>

typedef enum{
    GPIO_MODE_INPUT  = 0U,
    GPIO_MODE_OUTPUT = 1U,
    GPIO_MODE_AF     = 2U,
    GPIO_MODE_ANALOG = 3U,
}GPIO_Mode_t;

typedef enum{
    PUSH_PULL  = 0U,
    OPEN_DRAIN = 1U
}GPIO_OUTPUT_Type_t;

typedef enum{
     LOW       = 0U,
     MEDIUM    = 1U,
     HIGH      = 2U,
     VERY_HIGH = 3U,
}GPIO_Speed_t;

typedef enum{
    NO_PUPD = 0U,
    PU      = 1U,
    PD      = 2U,
}GPIO_pupd_t;

typedef enum{
    GPIO_PIN_0 = 0U,GPIO_PIN_1 = 1U, GPIO_PIN_2 = 2U,GPIO_PIN_3 = 3U,
    GPIO_PIN_4 = 4U,GPIO_PIN_5 = 5U, GPIO_PIN_6 = 6U,GPIO_PIN_7 = 7U,
    GPIO_PIN_8 = 8U,GPIO_PIN_9 = 9U, GPIO_PIN_10 = 10U,GPIO_PIN_11 = 11U,
    GPIO_PIN_12 = 12U,GPIO_PIN_13 = 13U, GPIO_PIN_14 = 14U,GPIO_PIN_15 = 15U,  

}GPIO_Pin_t;

typedef enum{
    GPIO_PIN_LOW  = 0U,
    GPIO_PIN_HIGH = 1U,
}GPIO_PIN_State_t;

typedef enum{
    GPIO_AF_0 = 0U,GPIO_AF_1 = 1U, GPIO_AF_2 = 2U,GPIO_AF_3 = 3U,
    GPIO_AF_4 = 4U,GPIO_AF_5 = 5U, GPIO_AF_6 = 6U,GPIO_AF_7 = 7U,
    GPIO_AF_8 = 8U,GPIO_AF_9 = 9U, GPIO_AF_10 = 10U,GPIO_AF_11 = 11U,
    GPIO_AF_12 = 12U,GPIO_AF_13 = 13U, GPIO_AF_14 = 14U,GPIO_AF_15 = 15U, 
}GPIO_AF_t;

void GPIO_Init(GPIO_TypeDef *gpio);
void GPIO_MODE(GPIO_TypeDef *gpio,GPIO_Pin_t pin,GPIO_Mode_t mode);
void GPIO_OUTPUT_TYPE(GPIO_TypeDef *gpio,GPIO_Pin_t pin, GPIO_OUTPUT_Type_t type);
void GPIO_OUTPUT_SPEED(GPIO_TypeDef *gpio, GPIO_Pin_t pin, GPIO_Speed_t speed);
void GPIO_PUPD(GPIO_TypeDef *gpio,GPIO_Pin_t pin, GPIO_pupd_t PUPD);
bool GPIO_READ(GPIO_TypeDef *gpio, GPIO_Pin_t pin);
void GPIO_WRITE(GPIO_TypeDef *gpio,GPIO_Pin_t pin, GPIO_PIN_State_t state);
void GPIO_SET(GPIO_TypeDef *gpio, GPIO_Pin_t pin);
void GPIO_RESET(GPIO_TypeDef *gpio, GPIO_Pin_t pin);
void GPIO_AF(GPIO_TypeDef *gpio,GPIO_Pin_t pin, GPIO_AF_t AF);









#endif 