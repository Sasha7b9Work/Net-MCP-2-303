// 2023/04/04 09:57:45 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include <stm32f1xx_hal.h>


namespace HAL_USART2
{
    static UART_HandleTypeDef handleUART;

    void *handle = (void *)&handleUART;

    static uint8 buffer;
}


void HAL_USART2::Init()
{
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */

    GPIO_InitTypeDef is;

    is.Pin = GPIO_PIN_2;
    is.Mode = GPIO_MODE_AF_PP;
    is.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &is);

    is.Pin = GPIO_PIN_3;
    is.Mode = GPIO_MODE_INPUT;
    is.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &is);

    handleUART.Instance = USART2;
    handleUART.Init.BaudRate = 9600;
    handleUART.Init.WordLength = UART_WORDLENGTH_8B;
    handleUART.Init.StopBits = UART_STOPBITS_1;
    handleUART.Init.Parity = UART_PARITY_NONE;
    handleUART.Init.Mode = UART_MODE_TX_RX;
    handleUART.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    handleUART.Init.OverSampling = UART_OVERSAMPLING_16;

    HAL_UART_Init(&handleUART);

    HAL_NVIC_SetPriority(USART2_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(USART2_IRQn);

    HAL_UART_Receive_IT(&handleUART, &buffer, 1);
}


void HAL_USART2::ReceiveCallback()
{
    NEO_M8N::ReceiveNewSymbolHandler((char)buffer);

    HAL_UART_Receive_IT(&handleUART, &buffer, 1);
}
