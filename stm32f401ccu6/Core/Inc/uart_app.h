#ifndef UART_APP_H
#define UART_APP_H

#include "usart.h"   /* для доступа к huart1, сгенерированному CubeMX */
#include <stdint.h>

/* Запускает приём первого байта по прерыванию.
   Вызывается один раз из main(), после MX_USART1_UART_Init(). */
void UART_App_Init(void);

/* Возвращает количество байт, принятых с момента старта (для Дня 4 — статистика) */
uint32_t UART_App_GetByteCount(void);

#endif /* UART_APP_H */
