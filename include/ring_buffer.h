#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include<stdint.h>
#include<stdbool.h>


typedef struct{
    uint8_t *buff;
    uint16_t head;
    uint16_t tail;
    uint16_t size;
    uint32_t overflow_count;
}ring_t;


void ring_init(ring_t *ring, uint8_t *buff, uint16_t size);
bool ring_push(ring_t *ring, uint8_t byte);
bool ring_pop(ring_t *ring, uint8_t *byte);
bool ring_is_empty(ring_t *ring);
uint16_t ring_count(ring_t *ring);
uint32_t ring_overflow_count(ring_t *ring);

#endif