
#ifndef TUFAN_UART_REGISTER_F103_H
#define TUFAN_UART_REGISTER_F103_H

#include "stm32f1xx.h"  // STM32F103 için gerekli başlık dosyası

// Fonksiyon prototipleri
void GPIO_Clock(void);
void AFIO_Clock(void);
void USART2_Clock(void);
void TIM2_Clock(void);
void GPIOA_Init(void);
void USART2_Init(void);
void TIM2_Init(void);
void TIM2_CounterStart(void);
void NVIC_Enable(void);
void USART2_Enable(void);
void USART2_DataTransmit(void);
void TIM2_IRQHandler(void);

#endif /* TUFAN_UART_REGISTER_F103_H */
