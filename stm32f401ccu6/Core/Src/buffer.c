#include "buffer.h"

void RingBuffer_Init(RingBuffer_t *rb){
	rb->head = 0;
	rb->overflow_count=0;
	rb->tail=0;
}

bool RingBuffer_Put(RingBuffer_t *rb, uint8_t byte){
	uint16_t next_head = (rb->head+1)%RING_BUFFER_SIZE;
	if(next_head==rb->tail){
		rb->overflow_count++;
		return false;
	}
	rb->data[rb->head]=byte;
	rb->head = next_head;
	return true;
}

bool RingBuffer_Get(RingBuffer_t *rb, uint8_t *out_byte){
	if(rb->head == rb->tail){
		return false;
	}
	*out_byte = rb->data[rb->tail];
	rb->tail = (rb->tail +1)% RING_BUFFER_SIZE;
	return true;
}

bool RingBuffer_HasData(const RingBuffer_t *rb){
	if(rb->head==rb->tail){
		return false;
	}
	else{
		return true;
	}
}

uint16_t RingBuffer_Count(const RingBuffer_t *rb){
	if(rb->head>=rb->tail){
		return rb->head - rb->tail;
	}
	else{
		return (RING_BUFFER_SIZE - rb->tail)+rb->head;
	}
}
