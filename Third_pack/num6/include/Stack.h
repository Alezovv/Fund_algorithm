#ifndef STACK_H
#define STACK_H

#include "./StatusCode.h"

#include <stdlib.h>
#include <stdbool.h>

typedef struct Stack
{
    char *str;
    size_t size;
    size_t capacity;
} Stack;

StatusCode StackInit(Stack *s);

StatusCode Push(Stack *s, char c);
StatusCode LegitBrackets(Stack *s, size_t i);
StatusCode Pop(Stack *s);
StatusCode Get(Stack *s, char *c);
StatusCode IsEmpty(Stack *s, bool *b);
void DeleteStack(Stack *s);

#endif // STACK_H