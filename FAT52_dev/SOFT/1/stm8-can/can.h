/**
 * @authors
 * амдф, 2012
 * @brief Интерфейс модуля CAN
 * @file can.h
 * @details
 * Проект: Controller Area Network (CAN)
 * Микроконтроллер: STM8S208RB
 */

#ifndef _CAN_H_
#define _CAN_H_

typedef struct _CAN_MSG 
{
  u16 id;
  u8  rtr;
  u8  len;
  u8  dat[8];
} CAN_MSG, *PCAN_MSG;

CAN_InitStatus_TypeDef Init_CAN(void);
CAN_TxStatus_TypeDef CAN_SendMessage(PCAN_MSG pCanMsgOut);
CAN_TxStatus_TypeDef CAN_Send(u16 uId, bool uRtr, u8 uLen, const void* const pData);

#endif // _CAN_H_
