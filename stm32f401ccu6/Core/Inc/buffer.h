#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>
#include <stdbool.h>

#define RING_BUFFER_SIZE 256 // размер буфера

typedef struct
{
	uint8_t data[RING_BUFFER_SIZE];
	volatile uint16_t head; // двигается в callback
	volatile uint16_t tail; // двигается основным кодом
	volatile uint32_t overflow_count;
} RingBuffer_t;

void RingBuffer_Init(RingBuffer_t *rb); // инициализаця буфера или его сброс
bool RingBuffer_Put(RingBuffer_t *rb, uint8_t byte); // положить байт в буфер
bool RingBuffer_Get(RingBuffer_t *rb, uint8_t *out_byte); // прочитать байт из буфера
bool RingBuffer_HasData(const RingBuffer_t *rb);
uint16_t RingBuffer_Count(const RingBuffer_t *rb);

#endif
