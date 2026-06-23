#include "uart_app.h"


static uint8_t rx_byte; // буффер на один байт — сюда HAL кладёт каждый принятый байт

static RingBuffer_t rx_ring_buffer;

/* Счётчик принятых байт — пригодится в Дне 4 (статистика) */
static volatile uint32_t rx_byte_count = 0;

//static volatile uint32_t last_byte_tick = 0;

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

uint32_t UART_App_GetSpeed(void){
	static uint32_t last_tick = 0;
	static uint32_t last_count = 0;
	static uint32_t last_speed = 0;

	uint32_t now = HAL_GetTick();

	if((now - last_tick) >= 1000){
		uint32_t current_count = rx_byte_count;
		last_speed = current_count - last_count;
		last_count = current_count;
		last_tick = now;
	}
	return last_speed;

}
//uint32_t UART_AppGetTimeFromLastByte(void){
//	return HAL_GetTick() - last_byte_tick;
//}
//
//bool UART_App_TimeOut(uint32_t tms){
//	return UART_AppGetTimeFromLastByte() >= tms;
//}

uint32_t UART_App_GetTimeFromLastByte(void){
	static uint32_t last_count = 0;
	static uint32_t last_tick = 0;
	uint32_t now = HAL_GetTick();
	uint32_t tmp = last_tick;
	if(rx_byte_count>=last_count+1){
		last_tick = now;
		last_count = rx_byte_count;
	}
	return (now - tmp)/1000;
}
