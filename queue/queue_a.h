#ifndef __INCLUDED_QUEUE_A__
#define __INCLUDED_QUEUE_A__
#include <stdint.h>
#define MAX_QUEUE_LEN 32

// Queue (Circular) using Array
typedef struct _queue_ Queue;
struct _queue_
{
    uint32_t size;            // Actual Size
    uint32_t count;           // Occupied Size
    uint32_t head;            // Pointer for removing at head
    uint32_t tail;            // Pointer for adding at tail
    int32_t q[MAX_QUEUE_LEN]; // Actual Contents
};

#define QUEUE_OK 1
#define QUEUE_FULL 2
#define QUEUE_EMPTY 4
typedef struct _queue_result_ QueueResult;
struct _queue_result_
{
    int32_t data;
    uint32_t status;
};

void queue_display(const Queue *q);
Queue queue_new(uint32_t size);
Queue *queue_add(Queue *q, int32_t data, QueueResult *result);
Queue *queue_remove(Queue *q, QueueResult *result);
uint32_t queue_full(Queue *q);
uint32_t queue_empty(Queue *q);
Queue *queue_reverse_first_k(Queue *q, uint32_t k);

#endif