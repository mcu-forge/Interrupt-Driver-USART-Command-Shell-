#include<ring_buffer.h>


void ring_init(ring_t *ring, uint8_t *buff, uint16_t size){
    ring->buff = buff;
    ring->head = 0;
    ring->tail = 0;
    ring->size = size;
    ring->overflow_count = 0;
}

bool ring_push(ring_t *ring, uint8_t byte){
    uint16_t next = (ring->head +1) % ring->size;
    if(next == ring->tail){
        ring->overflow_count++;
        return false;
    }
    else{
        ring->buff[ring->head] = byte;
        ring->head = next;
        return true; 
    }

}
bool ring_pop(ring_t *ring, uint8_t *byte){
    if(ring->head == ring->tail){
        return false;
    }
    else{
    *byte = ring->buff[ring->tail];
    ring->tail = (ring->tail+1) % ring->size;
    return true; 
    }
}

bool ring_is_empty(ring_t *ring){
    return (ring->head == ring->tail);
}
uint16_t ring_count(ring_t *ring){
    return ((ring->head + ring->size - ring->tail) % ring->size);
}
uint32_t ring_overflow_count(ring_t *ring){
    return ring->overflow_count; 
}