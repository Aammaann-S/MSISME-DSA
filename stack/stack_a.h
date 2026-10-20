// Header File
// stack_a+.h

// Stack using Array
#ifndef __INCLUDED_STACK_H__
#define __INCLUDED_STACK_H__
#include <stdint.h>
#define MAX_DEPTH 32

typedef struct _stack_ Stack;
typedef struct _stack_result_ StackResult;

struct _stack_
{
    uint32_t size;        // requested stack depth
    int32_t top;          // index of the top modt element
    float data[MAX_DEPTH] // Actual Contents
};

#define RESULT_INVALID 0
#define STACK_OK 1
#define STACK_FULL 2
#define STACK_EMPTY 4
struct _stack_result_
{
    float data;
    uint32_t status;
};

/*
The ADT (Abstract Data Type) Interface
*/
Stack stack_new(uint32_t size);
uint32_t stack_full(const Stack *stk);
uint32_t stack_empty(const Stack *stk);
Stack *stack_push(Stack *stk, float data, StackResult *result);
Stack *stack_pop(Stack *stk, StackResult *result);
Stack *stack_peek(const Stack *stk, StackResult *result);

#endif
