#include "uart_app.h"

/* Буфер на один байт — сюда HAL кладёт каждый принятый байт */
static uint8_t rx_byte;

/* Счётчик принятых байт — пригодится в Дне 4 (статистика) */
static volatile uint32_t rx_byte_count = 0;

void UART_App_Init(void)
{
    rx_byte_count = 0;
    /* Запускаем приём первого байта по прерыванию.
       HAL сам включит нужный бит в регистре USART и будет ждать байт. */
    HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
}

uint32_t UART_App_GetByteCount(void)
{
    return rx_byte_count;
}

/* Этот callback HAL вызывает автоматически из обработчика прерывания
   USART1_IRQHandler каждый раз, когда очередной байт полностью принят.
   ВАЖНО: HAL_UART_Receive_IT одноразовый — после срабатывания приём
   останавливается, поэтому в конце обязательно перезапускаем его заново. */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        rx_byte_count++;

        /* Пока просто эхо — отправляем принятый байт обратно для проверки.
           Позже здесь появится вызов записи в кольцевой буфер (День 3). */
        HAL_UART_Transmit(&huart1, &rx_byte, 1, HAL_MAX_DELAY);

        /* Перезапускаем приём следующего байта — без этого приём "умрёт"
           после первого же байта. */
        HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
    }
}
