#ifndef STACK_H
#define STACK_H

#include "./StatusCode.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INT_MAX_LEN 11

typedef struct Stack
{
    char **str;
    int size;
    int capacity;
} Stack;

StatusCode Init_Stack(Stack *s);

StatusCode Stack_Size(Stack *s, int *size);

StatusCode Stack_Push(Stack *s, const char *str);

StatusCode Stack_TopLength(Stack *s, size_t *len);

StatusCode Stack_Get(Stack *s, char **str);

StatusCode Stack_Pop(Stack *s, char **str);

StatusCode Stack_Destroy(Stack *s);

void Stack_Print(Stack *s);

#endif // STACK_H