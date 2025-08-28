#include "defines.h"
#include "Hardware/CDC/CDC.h"
#include "Hardware/HAL/HAL.h"
#include "Modules/HC12/HC12.h"
#include "Modules/NEO-M8N/NEO-M8N.h"
#include "Hardware/Beeper.h"
#include <stm32f3xx_hal.h>


#ifndef WIN32
    #pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif


void NMI_Handler(void)
{
}


void HardFault_Handler(void)
{
//    static int line = Debug::line[0];
//    static pchar file = Debug::file[0];
//    static int type = Debug::type;

    while (1) //-V776
    {
//        line = line; //-V570
//        file = file; //-V570
//        type = type; //-V570
    }
}


void MemManage_Handler(void)
{
    while (1)
    {
    }
}


void BusFault_Handler(void)
{
    while (1)
    {
    }
}


void UsageFault_Handler(void)
{
    while (1)
    {
    }
}


void SVC_Handler(void)
{

}


void DebugMon_Handler(void)
{

}


void PendSV_Handler(void)
{

}


void SysTick_Handler(void)
{
    HAL_IncTick();
}


void USB_LP_CAN_RX0_IRQHandler(void)
{
    HAL_PCD_IRQHandler((PCD_HandleTypeDef *)handlePCD);
}

void USART1_IRQHandler(void)
{
    HAL_UART_IRQHandler((UART_HandleTypeDef *)HAL_USART1::handle);
}


void USART2_IRQHandler(void)
{
    HAL_UART_IRQHandler((UART_HandleTypeDef *)HAL_USART2::handle);
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *handle)
{
    if (handle == HAL_USART1::handle)
    {
        HC12::CallbackOnReceive();
    }
    else if (handle == HAL_USART2::handle)
    {
        NEO_M8N::CallbackOnReceive();
    }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *handle)
{
    if (handle == HAL_USART2::handle)
    {
        HAL_USART2::ReInit();
    }
}


void ADC1_2_IRQHandler(void)
{
    HAL_ADC_IRQHandler((ADC_HandleTypeDef *)HAL_ADC::handle);
}


void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler((TIM_HandleTypeDef *)Beeper::handleTIM3);
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) //-V2009
{
    if (htim == Beeper::handleTIM3)
    {
        Beeper::CallbackOnTimer();
    }
}
