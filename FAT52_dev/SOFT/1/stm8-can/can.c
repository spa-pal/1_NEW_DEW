/**
 * @authors
 * амдф, 2012
 * @brief Модуль CAN
 * @file can.c
 * @details
 * Проект: Controller Area Network (CAN)
 * Микроконтроллер: STM8S208RB                   
 */

#include "main.h"
#include "can.h"

volatile CAN_MSG CanMsgIn;

CAN_TxStatus_TypeDef CAN_SendMessage(const PCAN_MSG const pCanMsgOut)
{
  return CAN_Send
  (
    pCanMsgOut->id,
    pCanMsgOut->rtr,
    pCanMsgOut->len,
    pCanMsgOut->dat
  );    
}

// TODO: не допустить обращения к NULL-указателю данных
CAN_TxStatus_TypeDef CAN_Send(u16 uId, bool uRtr, u8 uLen, const void* const pData)
{
  CAN_TxStatus_TypeDef TxStatus;  
  CAN_TransmitMailBox_TypeDef TransmitMailbox;  
  u16 uSendLimit;
    
  if (!uRtr)
  {
    if (0 == uLen || uLen > 8 || NULL == pData) return CAN_TxStatus_Failed;
  }
  
  TransmitMailbox = CAN_Transmit(uId, CAN_Id_Standard, uRtr ? CAN_RTR_Remote : CAN_RTR_Data, uLen, (u8*)pData);
    
  uSendLimit = 0xFFF; // Ограничение, чтобы не зависнуть на передаче
  do
  {
    TxStatus = CAN_TransmitStatus(TransmitMailbox); 
  } while (TxStatus != CAN_TxStatus_Ok && uSendLimit--);
  
  if (TxStatus != CAN_TxStatus_Ok)
  {
    printf("CAN: передача сообщения не удалась и отменена.\r\n");
    CAN_CancelTransmit(TransmitMailbox);
  } else
  {
    printf("CAN: Успешная передача сообщения.\r\n");
  }

  return TxStatus;
}

/**
  * @brief Configures the CAN mode and filter
  * @par Parameters:
  * None
  * @retval CAN init status
  * @par Required preconditions:
  * None
  */
CAN_InitStatus_TypeDef Init_CAN(void)
{
  CAN_InitStatus_TypeDef status = CAN_InitStatus_Failed;
  
  /* Filter Parameters */
  CAN_FilterNumber_TypeDef CAN_FilterNumber;
  FunctionalState CAN_FilterActivation;
  CAN_FilterMode_TypeDef CAN_FilterMode;
  CAN_FilterScale_TypeDef CAN_FilterScale;
  u8 CAN_FilterID1;
  u8 CAN_FilterID2;
  u8 CAN_FilterID3;
  u8 CAN_FilterID4;
  u8 CAN_FilterIDMask1;
  u8 CAN_FilterIDMask2;
  u8 CAN_FilterIDMask3;
  u8 CAN_FilterIDMask4; 
  
  /* Init Parameters*/
  CAN_MasterCtrl_TypeDef CAN_MasterCtrl;
  CAN_Mode_TypeDef CAN_Mode;
  CAN_SynJumpWidth_TypeDef CAN_SynJumpWidth;
  CAN_BitSeg1_TypeDef CAN_BitSeg1;
  CAN_BitSeg2_TypeDef CAN_BitSeg2;
  CAN_ClockSource_TypeDef CAN_ClockSource;
  u8 CAN_Prescaler; 
  
  /* /////////////////////////////////////////////////////////////// */
  
  /* CAN register init */
  CAN_DeInit();
    
  /* CAN  init */
  CAN_MasterCtrl=CAN_MasterCtrl_AllDisabled;
  CAN_Mode = CAN_Mode_Normal;
  //CAN_Mode = CAN_Mode_LoopBack;
  
  // 25 КГц, проверено вместе с БУ-3П/7
  
  CAN_SynJumpWidth = CAN_SynJumpWidth_1TimeQuantum;
  CAN_BitSeg1 = CAN_BitSeg1_7TimeQuantum;
  CAN_BitSeg2 = CAN_BitSeg2_2TimeQuantum;
  CAN_Prescaler = 48;

  CAN_ClockSource = CAN_ClockSource_Internal;
  
  status = CAN_Init
  (
    CAN_MasterCtrl, CAN_Mode, CAN_SynJumpWidth, CAN_BitSeg1,
    CAN_BitSeg2, CAN_ClockSource, CAN_Prescaler
  );

  if (CAN_InitStatus_Success == status)
  {
    /* CAN filter init */

    /*
      CAN_FilterMode_IdMask                 id/mask mode 
      CAN_FilterMode_IdMask_IdList           Id/Mask mode First and IdList mode second 
      CAN_FilterMode_IdList_IdMask           IdList mode First and IdMask mode second 
      CAN_FilterMode_IdList                  identifier list mode   

      Пример фильтрации: 8-битный режим фильтрации по списку идентификаторов.

      CAN_FilterNumber = 0;
      CAN_FilterActivation = ENABLE;    
      CAN_FilterMode = CAN_FilterMode_IdList;
      CAN_FilterScale = CAN_FilterScale_8Bit;

      Фильтрация возможна по битам 3-10 стандартного идентификатора.        
    */    
    CAN_FilterNumber = 0;
    CAN_FilterActivation = ENABLE;
    CAN_FilterMode = CAN_FilterMode_IdList;
    CAN_FilterScale = CAN_FilterScale_8Bit;

    CAN_FilterID1     = (0x5FC >> 3);
    CAN_FilterIDMask1 = 0;
    CAN_FilterID2     = 0;
    CAN_FilterIDMask2 = 0;
    CAN_FilterID3     = 0;
    CAN_FilterIDMask3 = 0;
    CAN_FilterID4     = 0;
    CAN_FilterIDMask4 = 0;

    CAN_FilterInit
    (
      CAN_FilterNumber, CAN_FilterActivation, CAN_FilterMode, CAN_FilterScale,
      CAN_FilterID1, CAN_FilterID2, CAN_FilterID3, CAN_FilterID4,
      CAN_FilterIDMask1, CAN_FilterIDMask2, CAN_FilterIDMask3, CAN_FilterIDMask4
    );
    
    CAN_ITConfig(CAN_IT_FMP, ENABLE);   
  }
  
  return status;
}

void CAN_PrintMsg(void)
{
  u8 i;
    
  if (!CanMsgIn.rtr)
  {
    printf("ИД: %04X\tДлина: %d\tRTR: %d\tДанные:", CanMsgIn.id, (int)CanMsgIn.len, (int)CanMsgIn.rtr ? 1 : 0);
    for (i = 0; i < CanMsgIn.len; i++)
    {
      printf(" %02X", (int)CanMsgIn.dat[i]);
    }
  } 
    else
  {
    printf("ИД: %04X\tДлина: %d\tRTR: %d\t", CanMsgIn.id, (int)CanMsgIn.len, (int)CanMsgIn.rtr ? 1 : 0);
    printf("(Запрос сообщения)");
  }
  printf("\r\n");
}

/*
Обрабатывать входящие данные прямо в прерывании, или помещать их в очередь и обрабатывать позднее?
Зависит от объёма обрабатываемых данных и того, насколько часто они поступают
*/
/**
  * @brief CAN RX Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
*/

void CAN_RX_IRQHandler(void) interrupt 8
{
  u8 i;
  /* Receiver Receives Frame */
  CAN_Receive();
  CanMsgIn.id = CAN_GetReceivedId();
  CanMsgIn.rtr = CAN_GetReceivedRTR();
  CanMsgIn.len = CAN_GetReceivedDLC();
  for (i = 0; i < CanMsgIn.len; i++)
  {
    CanMsgIn.dat[i] = CAN_GetReceivedData(i);  
  }  
  
  CAN_PrintMsg();
}
