#include <stddef.h>
#include <assert.h>
#include "queue_a.h"

/* Display queue (front to rear) without modifying */
void queue_display(const Queue *q)
{
    uint32_t i;
    uint32_t index = q->head;

    for (i = 0; i < q->count; i++)
    {
        printf("%d ", q->q[index]);
        index = (index + 1) % q->size;
    }

    printf("\n");
}

Queue queue_new(uint32_t size)
{
    size = (size > 0 && size < MAX_QUEUE_LEN) ? size : MAX_QUEUE_LEN;
    Queue q = {size, 0 /*count*/, 0 /*head*/, 0 /*tail*/, {0} /*data*/};
    return q;
}

Queue *queue_add(Queue *q, int32_t data, QueueResult *result)
{
    assert(q != NULL && q->count <= q->size);
    if (q->count < q->size)
    {
        q->q[q->tail] = data;
        // 1st q = main Queue object
        // 2nd q = data array q company
        // 3rd q = q->tail gives the index for the 2nd q (dataarray queue)
        q->tail = (q->tail + 1) % q->size; // Circular Queue part : x%size gives the next position value
        ++q->count;
        result->status = QUEUE_OK;
    }
    else
    {
        result->status = QUEUE_FULL;
    }
    assert(result->status == QUEUE_OK || q->count == q->size);
    return q;
}

Queue *queue_remove(Queue *q, QueueResult *result)
{
    assert(q != NULL && q->count <= q->size);
    if (q->count > 0)
    {
        result->data = q->q[q->head];
        q->head = (q->head + 1) % q->size; // Circular Queue part : x%size gives the next position value
        --q->count;
        result->status = QUEUE_OK;
    }
    else
    {
        result->status = QUEUE_EMPTY;
    }
    assert(q->count < q->size);
    assert(result->status == QUEUE_OK || q->count == 0);
    return q;
}

uint32_t queue_full(Queue *q)
{
    assert(q != NULL && q->count <= q->size);
    return (q->count == q->size);
}

uint32_t queue_empty(Queue *q)
{
    return (q->count == 0 && q->head == q->tail);
}

/* Helper function: reverse first k elements recursively */
static void reverse_k_recursive(Queue *q, uint32_t k)
{
    QueueResult result;

    if (k == 0)
        return;

    /* Remove the front element */
    queue_remove(q, &result);
    assert(result.status == QUEUE_OK);

    int32_t data = result.data;

    /* Reverse the remaining k - 1 elements */
    reverse_k_recursive(q, k - 1);

    /* Add this element after the reversed elements */
    queue_add(q, data, &result);
    assert(result.status == QUEUE_OK);
}

/*
Lab Assignment - Ques-3
Program to Reverse first k elements of Queue
*/
Queue *queue_reverse_first_k(Queue *q, uint32_t k)
{
    uint32_t i;
    uint32_t remaining;

    if (q == NULL || k == 0 || k > q->count)
        return q;

    remaining = q->count - k;

    reverse_k_recursive(q, k);

    /* Move the original remaining elements to the rear */
    for (i = 0; i < remaining; i++)
    {
        QueueResult result;

        queue_remove(q, &result);
        assert(result.status == QUEUE_OK);

        queue_add(q, result.data, &result);
        assert(result.status == QUEUE_OK);
    }

    return q;
}
