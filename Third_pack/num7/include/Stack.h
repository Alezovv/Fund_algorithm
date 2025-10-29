#ifndef STACK_H
#define STACK_H

#include "./StatusCode.h"

#include <stdlib.h>

typedef struct Stack
{
    char *str;
    int size;
    int capacity;
} Stack;

StatusCode Init_Stack(Stack *s);

StatusCode Stack_Push(Stack *s, char symbol);

StatusCode Stack_Get(Stack *s, char *symbol);

StatusCode Stack_Pop(Stack *s, char *symbol);

StatusCode Stack_Destroy(Stack *s);

#endif // STACK_H