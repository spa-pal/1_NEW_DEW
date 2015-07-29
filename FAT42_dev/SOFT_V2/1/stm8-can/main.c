/**
 * @authors
 * амдф, 2012
 * @brief Главный модуль
 * @file main.c
 * @details
 * Проект: Controller Area Network (CAN)
 * Микроконтроллер: STM8S208RB
 */

#include "main.h"

//! Интервал очистки консоли от сообщений
#define CLEAR_INTERVAL 6

extern volatile u8 uSeconds; // counter.c

void Init_CPU(void);
void Init_UART(void);

void main(void)
{
  u8 uClear = CLEAR_INTERVAL;
  CAN_MSG CanMsgOut;
  
  disableInterrupts();  
  
  //////////////////////////////
  
  Init_CPU();
  
  
  // CAN_TX
  GPIO_Init( GPIOG, GPIO_PIN_0, GPIO_MODE_OUT_PP_HIGH_FAST );
  // CAN_RX
  GPIO_Init( GPIOG, GPIO_PIN_1, GPIO_MODE_IN_PU_NO_IT );
  // Configure the CAN transceiver in active mode
  GPIO_Init( GPIOE, GPIO_PIN_6, GPIO_MODE_OUT_PP_LOW_FAST );
  
  Init_UART(); 
  
  if (CAN_InitStatus_Failed == Init_CAN())
  {
    // Очистить экран и переместить курсор в верхний левый угол экрана
    printf("\x1B[2J\x1B[1;1H");
    COLOR_RED_ON;
    printf("CAN init failed\r\n");
    COLOR_OFF;
    for (;;)
    {
      ;
    }
  }
  
  CounterTimerStart();  
  
  enableInterrupts();
  
  CanMsgOut.dat[0] = 'a';
  CanMsgOut.dat[1] = 'b';
  CanMsgOut.dat[2] = 'c';
  CanMsgOut.id = 0x123;
  CanMsgOut.len = 3;
  CanMsgOut.rtr = 0;
  
  COLOR_RED_ON;
  printf("Controller Area Network, собрано %s (%s)\r\n", __DATE__, __TIME__);
  COLOR_OFF;  
  
  uClear = 6;
  for (;;)
  {   

    if (uSeconds > 0)
    {
      uSeconds = 0;  

      if (0 == uClear--)
      {
        uClear = CLEAR_INTERVAL;
        // Очистить экран и переместить курсор в верхний левый угол экрана
        //printf("\x1B[2J\x1B[1;1H");        
      }
      
      CAN_SendMessage(&CanMsgOut);
      CAN_Send(0x444, 1, 0, NULL);
      CAN_Send(0x444, 1, 8, NULL);
    }        

  }
}

/**
  * @brief Инициализация микроконтроллера
  * @par
  * Параметры отсутствуют
  * @retval
  * Возвращаемое значение отсутствует
*/
void Init_CPU(void)
{  
  ErrorStatus status = FALSE;
  u8 cnt = 0;

  // Внешний источник частоты, 12 МГц. Частота должна быть указана в stm8s_conf.h в HSE_VALUE.
  status = CLK_ClockSwitchConfig( CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSE, DISABLE, DISABLE );

  // Ждать стабилизации частоты
  while (CLK_GetSYSCLKSource() != CLK_SOURCE_HSE)
  {
    if ( --cnt == 0 )
      return;
  }
  
  // Отключить внутренний источник частоты
  CLK_HSICmd(DISABLE);
  
  // Конфигурация предделителя CAN
  CLK_CANConfig( CLK_CANDIVIDER_1 );
}

/**
  * @brief Инициализация UART
  * @par
  * Параметры отсутствуют
  * @retval
  * Возвращаемое значение отсутствует
*/
void Init_UART(void)
{  
  UART1_DeInit();
  // 115200 8N1
  UART1_Init((u32)115200, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
              UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);  

  UART1_Cmd(ENABLE);
}