#include "TUFAN_UART_REGISTER_F103.h"

void GPIO_Clock(void)
{
    RCC -> APB2ENR |= (1 << 2);          // GPIOA Clock enable
}

void AFIO_Clock(void)
{
    RCC -> APB2ENR |= (1 << 0);          // AFIO Clock enable
}

void USART2_Clock(void)
{
    RCC -> APB1ENR |= (1 << 17);         // USART2 Clock enable
}

void TIM2_Clock(void)
{
    RCC -> APB1ENR |= (1 << 0);          // TIM2 Clock enable
}

void GPIOA_Init(void)
{
    GPIOA -> CRL |= (1 << 8) | (1 << 9);     // MODE2 for PA2 pin (USART2 TX) - Output mode, 50 MHz speed
    GPIOA -> CRL &= ~(1 << 10);              // CNF2 for PA2 (USART2 TX) - Push-pull
    GPIOA -> CRL |= (1 << 11);               
}

void USART2_Init(void)
{
    USART2 -> CR2 &= ~((1 << 12) | (1 << 13));    // 1 stop bit
    USART2 -> BRR = (52 << 4) | 1;                // Baud rate 9600 (mantissa = 52, fraction = 1)
    USART2 -> CR1 |= (1 << 3);                    // Transmit enable
}

void TIM2_Init(void)
{
    TIM2 -> DIER |= (1 << 0);           // Update Interrupt Enable
    TIM2 -> PSC = 7999;                 // Prescaler: 8000 (PSC + 1), 1 kHz timer clock
    TIM2 -> ARR = 999;                  // Auto-reload value for 100 ms
}

void TIM2_CounterStart(void)
{
    TIM2 -> CNT = 0;                    // Reset counter
    TIM2 -> CR1 |= (1 << 0);            // Counter enable
}

void NVIC_Enable(void)
{
    NVIC -> ISER[0] |= (1 << 28);       // NVIC Interrupt set enable for TIM2
}

void USART2_Enable(void)
{
    USART2 -> CR1 |= (1 << 3);           // Transmit enable
    USART2 -> CR1 |= (1 << 13);         // USART2 enable
}

void USART2_DataTransmit(void)
{
    while(!(USART2 -> SR & (1 << 7)));      // Wait until TXE is set
    USART2 -> DR = 'T';                     // Send data
    while(!(USART2 -> SR & (1 << 6)));      // Wait until TC is set
}

void TIM2_IRQHandler(void)
{
    if(TIM2 -> SR & (1 << 0))           // Update interrupt flag control
    {
        TIM2 -> SR &= ~(1 << 0);        // Clear update interrupt flag
        USART2_DataTransmit();          // Transmit data   
    }
}
