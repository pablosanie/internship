#include "uart_app.h"


static uint8_t rx_byte; // буффер на один байт — сюда HAL кладёт каждый принятый байт

static RingBuffer_t rx_ring_buffer; //  буфер


static volatile uint32_t rx_byte_count = 0; // счётчик всех принятых байт
static volatile uint32_t rx_buffered_count = 0; // только попавшие в буфер байты

//static volatile uint32_t last_byte_tick = 0;

void UART_App_Init(void)
{
    rx_byte_count = 0;
    RingBuffer_Init(&rx_ring_buffer);
    /* Запускаем приём первого байта по прерыванию.
       HAL сам включит нужный бит в регистре USART и будет ждать байт. */
    HAL_UART_Receive_IT(&huart1, &rx_byte, 1); // вкл ожидание для прерывания на приём данных
}
bool UART_App_ReadByte(uint8_t *out_byte){ // чтение байт
	return RingBuffer_Get(&rx_ring_buffer, out_byte);
}

uint32_t UART_App_GetByteCount(void) // получить кол-во байт
{
    return rx_byte_count;
}

uint32_t UART_App_GetOverflowCount(void){ // получить кол-во байт, не попавших в буфер
	return rx_ring_buffer.overflow_count;
}
/* Этот callback HAL вызывает автоматически из обработчика прерывания*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1) // проверка какой UART
    {
    	rx_byte_count++; // счётчик всех передаваемых байт
    	if (RingBuffer_Put(&rx_ring_buffer, rx_byte)) // был ли положен байт
    	        {
    	            rx_buffered_count++;  // только если байт реально попал в буфер
    	        }
        HAL_UART_Receive_IT(&huart1, &rx_byte, 1); // запускаем приём следующего байта
    }
}

uint32_t UART_App_GetSpeed(void){
	static uint32_t last_tick = 0; // последний момент времени, в который произошёл расчёт скорости
	static uint32_t last_count = 0; // последний счётчик байт
	static uint32_t last_speed = 0; // последняя скорость (моментальная)

	uint32_t now = HAL_GetTick(); // настоящий момент в мс
	uint32_t delta = now - last_tick; // разница между прошлым вызовом и настоящим временем
	if(delta >= 1000){ // нестрогое равенство т.к. может быть 1001 мс, 1002 мс и т.д.
		uint32_t current_count = rx_byte_count; // = глобальному счётчику байт, который может измениться за время работы алгоритма
		last_speed = (current_count - last_count)*1000/delta; // если прошло чуть больше 1000 мс, то скорость будет это учитывать
		last_count = current_count; // меняем последний счётчик байт до след. иттерации
		last_tick = now; // меняем последний момент времени до след. иттерации
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

//uint32_t UART_App_GetTimeFromLastByte(void){
//	static uint32_t last_count = 0;
//	static uint32_t last_tick = 0;
//	uint32_t now = HAL_GetTick();
//	uint32_t tmp = last_tick;
//	if(rx_byte_count>=last_count+1){
//		last_tick = now;
//		last_count = rx_byte_count;
//	}
//	return (now - tmp)/1000;
//}
uint32_t UART_App_GetBufferedCount(void) // получить байты, которые прошли через буфер
{
    return rx_buffered_count;
}
