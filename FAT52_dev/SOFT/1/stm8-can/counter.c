/**
 * @authors
 * амдф, 2012
 * @brief Управление внутренним счётчиком
 * @file counter.c
 * @details
 * Проект: Controller Area Network (CAN)
 * Микроконтроллер: STM8S208RB
 */

#include "main.h"
#include "counter.h"

//! Счётчик, отсчитывающий секунды
volatile u8 uSeconds = 0;

/**
  * @brief Включить таймер № 2.
  * @par
  * Параметры отсутствуют
  * @retval
  * Возвращаемое значение отсутствует
*/
void CounterTimerStart(void)
{
  TIM2_DeInit();
  
  TIM2_TimeBaseInit(TIM2_PRESCALER_32768, 610);
  
  TIM2_ITConfig(TIM2_IT_UPDATE, ENABLE);  
  
  TIM2_Cmd(ENABLE); 
}

/**
  * @brief Прерывание внутреннего счётчика. Таймер № 2.
  * @par
  * Параметры отсутствуют
  * @retval
  * Возвращаемое значение отсутствует
*/
#ifdef _COSMIC_
@far @interrupt void TIM2_UPD_OVF_BRK_IRQHandler(void)
#else /* _RAISONANCE_ */
void TIM2_UPD_OVF_BRK_IRQHandler(void) interrupt 13
#endif /* _COSMIC_ */
{
  // Интервал 1 секунда
  ++uSeconds;
  TIM2_ClearITPendingBit(TIM2_IT_UPDATE);   
}
