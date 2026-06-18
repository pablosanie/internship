#include "uart_app.h"


static uint8_t rx_byte; // буффер на один байт — сюда HAL кладёт каждый принятый байт

static RingBuffer_t rx_ring_buffer;
/* Счётчик принятых байт — пригодится в Дне 4 (статистика) */
static volatile uint32_t rx_byte_count = 0;

void UART_App_Init(void)
{
    rx_byte_count = 0;
    RingBuffer_Init(&rx_ring_buffer);
    /* Запускаем приём первого байта по прерыванию.
       HAL сам включит нужный бит в регистре USART и будет ждать байт. */
    HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
}
bool UART_App_ReadByte(uint8_t *out_byte){
	return RingBuffer_Get(&rx_ring_buffer, out_byte);
}

uint32_t UART_App_GetByteCount(void)
{
    return rx_byte_count;
}

uint32_t UART_App_GetOverflowCount(void){
	return rx_ring_buffer.overflow_count;
}
/* Этот callback HAL вызывает автоматически из обработчика прерывания*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        rx_byte_count++;
        RingBuffer_Put(&rx_ring_buffer, rx_byte);
        HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
    }
}
