#include "buffer.h"

void RingBuffer_Init(RingBuffer_t *rb){ // инициализируем буфер
	rb->head = 0;
	rb->overflow_count=0;
	rb->tail=0;
}

bool RingBuffer_Put(RingBuffer_t *rb, uint8_t byte){ // кладём в буфер данные
	uint16_t next_head = (rb->head+1)%RING_BUFFER_SIZE; // благодаря остатку от деления мы замыкаем буфер
	if(next_head==rb->tail){ // переполнение буфера, если итератор, указывающий на следующую голову равен tail
		rb->overflow_count++;
		return false; // байт не положен в буфер
	}
	rb->data[rb->head]=byte; // кладём байт в буфер
	rb->head = next_head; // сдвигаем голову
	return true; // байт положен в буфер
}

bool RingBuffer_Get(RingBuffer_t *rb, uint8_t *out_byte){ // чтение из буфера
	if(rb->head == rb->tail){ // чтение заканчивается, когда head совпадает с tail
		return false; // байт не прочитан
	}
	*out_byte = rb->data[rb->tail]; // сохраняем прочитанный байт в переменную out_byte с помощью разыменования указателя
	rb->tail = (rb->tail +1)% RING_BUFFER_SIZE; // благодаря остатку от деления мы замыкаем буфер и передвигаем tail
	return true; // байт прочитан
}

bool RingBuffer_HasData(const RingBuffer_t *rb){ // проверка наличия данных в кольцевом буфере
	if(rb->head==rb->tail){ // если head = tail, то данных для чтения нет
		return false;
	}
	else{
		return true;
	}
}

uint16_t RingBuffer_Count(const RingBuffer_t *rb){ // подсчёт количества данных в кольцевом буфере
	if(rb->head>=rb->tail){ // если head впереди tail, то не прочитаны только данные между ними
		return rb->head - rb->tail;
	}
	else{
		return (RING_BUFFER_SIZE - rb->tail)+rb->head; // если head позади tail, то не прочитаны данные конец - tail и от начала  до head
	}
}
