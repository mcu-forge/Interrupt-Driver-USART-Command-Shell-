#include<gpio.h>



void GPIO_Init(GPIO_TypeDef *gpio){
     if(gpio == GPIOA){
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
      }
      else if(gpio == GPIOB){
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
      }
      else if(gpio == GPIOC){
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
      }
      else if(gpio == GPIOD){
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
      }
      else if(gpio == GPIOE){
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
      }
      else if(gpio == GPIOF){
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
      }
      else if(gpio == GPIOG){
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
      }
      else if(gpio == GPIOH){
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
      }
}


void GPIO_MODE(GPIO_TypeDef *gpio,GPIO_Pin_t pin,GPIO_Mode_t mode){
    gpio->MODER &= ~(3U << (pin*2));
    gpio->MODER |=  mode << (pin*2);
}


void GPIO_OUTPUT_TYPE(GPIO_TypeDef *gpio,GPIO_Pin_t pin, GPIO_OUTPUT_Type_t type){
    gpio->OTYPER &= ~(1U << pin);
    gpio->OTYPER |= type << pin;
}


void GPIO_OUTPUT_SPEED(GPIO_TypeDef *gpio, GPIO_Pin_t pin, GPIO_Speed_t speed){
    gpio->OSPEEDR &= ~(3U << (pin*2));
    gpio->OSPEEDR |= speed << (pin*2);
}   


void GPIO_PUPD(GPIO_TypeDef *gpio,GPIO_Pin_t pin, GPIO_pupd_t PUPD){
    gpio->PUPDR &= ~(3U << (pin*2));
    gpio->PUPDR |= PUPD << (pin*2);
}


bool GPIO_READ(GPIO_TypeDef *gpio, GPIO_Pin_t pin){
    return ( gpio->IDR & (1U << pin) ) ; 
}
void GPIO_WRITE(GPIO_TypeDef *gpio,GPIO_Pin_t pin, GPIO_PIN_State_t state){
    if(state) {
         gpio->BSRR |= 1U << pin;
    }
    else {
        gpio->BSRR |= 1U << (pin+16);
    }
}

void GPIO_SET(GPIO_TypeDef *gpio, GPIO_Pin_t pin){
    gpio->BSRR |= 1U << pin;
}

void GPIO_RESET(GPIO_TypeDef *gpio, GPIO_Pin_t pin){
        gpio->BSRR |= 1U << (pin+16);
}


void GPIO_AF(GPIO_TypeDef *gpio,GPIO_Pin_t pin, GPIO_AF_t AF){
    if(pin<=7){
        gpio->AFR[0] &= ~(15U << (pin*4));
        gpio->AFR[0] |= AF << (pin*4);
    }
    else{
        gpio->AFR[1] &= ~(15U << ((pin-8)*4));
        gpio->AFR[1] |= AF << ((pin-8)*4);
    }
}