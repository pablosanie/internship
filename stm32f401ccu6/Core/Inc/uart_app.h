#ifndef UART_APP_H
#define UART_APP_H

#include "usart.h"   // для доступа к huart1, сгенерированному CubeMX
#include "buffer.h" // кольцевой буффер
#include <stdint.h>
#include <stdbool.h>




/* Запускает приём первого байта по прерыванию.
   Вызывается один раз из main(), после MX_USART1_UART_Init(). */
void UART_App_Init(void);

bool UART_App_ReadByte(uint8_t *out_byte);

/* Возвращает количество байт, принятых с момента старта (для Дня 4 — статистика) */
uint32_t UART_App_GetByteCount(void);

uint32_t UART_App_GetOverflowCount(void);

uint32_t UART_App_GetSpeed(void);

uint32_t UART_App_GetTimeFromLastByte(void);

uint32_t UART_App_GetBufferedCount(void);

#endif /* UART_APP_H */
