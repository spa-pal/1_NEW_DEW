/**
 * @authors
 * амдф, 2012
 * @brief Интерфейс главного модуля
 * @file main.c
 * @details
 * Проект: Controller Area Network (CAN)
 * Микроконтроллер: STM8S208RB
 */

#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <string.h>
#include "stm8s.h"
#include "counter.h"
#include "can.h"

enum { false, true };

#define COLOR_RED_ON printf("\x1B[1m\x1B[31m")
#define COLOR_YELLOW_ON printf("\x1B[1m\x1B[33m")
#define COLOR_OFF printf("\x1B[0m")

#endif