
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "queue_a.h"

int test_queue_a(void)
{
    Queue q = queue_new(32);
    QueueResult result;

    queue_add(&q, 10, &result);
    queue_add(&q, 20, &result);
    queue_add(&q, 30, &result);
    queue_add(&q, 40, &result);
    queue_add(&q, 50, &result);

    printf("Original queue: ");
    queue_display(&q);

    uint32_t k = 3;

    // Lab Assignment - Ques-3
    // Reverse the first k elements
    queue_reverse_first_k(&q, k);

    printf("After reversing first %u elements: ", (unsigned int)k);
    queue_display(&q);

    return 0;
}

int main(void)
{
    test_queue_a();
    return 0;
}
