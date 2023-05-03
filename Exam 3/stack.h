/************************************
* Developer:      Aviv Shalom       *
* Reviewer:       Idan              *
* Version:        1.0               *    
* Description:    API for stack.c   * 
*************************************/
#ifndef __OL134_STACK_H__
#define __OL134_STACK_H__

#include <stddef.h> /* for size_t */

typedef struct stack stack_t;

stack_t *StackCreate(size_t capacity, size_t element_size); 

void StackDestroy(stack_t *stack);

void StackPush(stack_t *stack, const void *new_element);

void StackPop(stack_t *stack);

void *StackPeek(const stack_t *stack);

size_t StackSize(const stack_t *stack);

int StackIsEmpty(const stack_t *stack);

size_t StackCapacity(const stack_t *stack);

#endif /*__OL134_STACK_H__*/










