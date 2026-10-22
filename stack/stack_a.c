// slist_stack.c
#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include "stack_a.h"

/* We deal with small size with stack data structure
stack object are passed to functions by reference
this is more efficient than passing by value */
Stack stack_new(uint32_t size)
{
    size = (size > 0 && size < MAX_DEPTH) ? size : MAX_DEPTH;
    Stack s = {size, -1, {0}};
    // size : stack depth
    // -1 : initial top
    // {0} : initialize whole stack as {0}
    return s;
}

uint32_t stack_full(const Stack *stk)
{
    assert(stk != NULL);
    return ((stk->top + 1 == stk->size));
}

uint32_t stack_empty(const Stack *stk)
{
    assert(stk != NULL);
    return ((stk->top == -1));
}

Stack *stack_push(Stack *stk, float data, StackResult *result)
{
    assert(stk != NULL);
    if (stk->top + 1 < stk->size)
    {
        stk->data[++stk->top] = data;
        result->data = data;
        result->status = STACK_OK;
    }
    else
    {
        result->data = data;
        result->status = STACK_FULL;
    }
    return stk;
}

Stack *stack_pop(Stack *stk, StackResult *result)
{
    assert(stk != NULL);
    if (stk->top > -1)
    {
        result->data = stk->data[stk->top];
        result->status = STACK_OK;
        --stk->top;
    }
    else
    {
        result->status = STACK_EMPTY;
    }
    return stk;
}

Stack *stack_peek(const Stack *stk, StackResult *result)
{
    assert(stk != NULL);
    if (stk->top > -1)
    {
        result->data = stk->data[stk->top];
        result->status = STACK_OK;
    }
    else
    {
        result->status = STACK_EMPTY;
    }
    return stk;
}

void stack_display_key(const Stack *stk, int32_t key)
{
    int32_t i;

    assert(stk != NULL);

    for (i = stk->top; i >= 0; --i)
    {
        if (stk->data[i] == key)
        {
            printf("Key found: %d\n", key);
            return;
        }
    }

    printf("Key not found: %d\n", key);
}
