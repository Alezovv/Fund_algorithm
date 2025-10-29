#include "../include/Stack.h"

StatusCode StackInit(Stack *s)
{
    if (s == NULL)
        return STATUS_ERROR_WRONG_ARGUMENT;

    s->str = (char *)malloc(10 * sizeof(char));
    if (s->str == NULL)
        return STATUS_ERROR_MEMORY_ALLOCATE;

    s->capacity = 10;
    s->size = 0;

    return STATUS_SUCCESS;
}

StatusCode Push(Stack *s, char c)
{
    if (s == NULL)
        return STATUS_ERROR_NOT_CREATED_STACK;

    if (s->size == s->capacity)
    {
        char *tmp = (char *)realloc(s->str, 2 * s->capacity * sizeof(char));
        if (tmp == NULL)
            return STATUS_ERROR_MEMORY_ALLOCATE;
        s->str = tmp;
        s->capacity *= 2;
    }

    s->str[s->size++] = c;
    return STATUS_SUCCESS;
}

StatusCode LegitBrackets(Stack *s, size_t i)
{
    if (s == NULL || i == 0 || i > 8)
        return STATUS_ERROR_WRONG_ARGUMENT;

    bool b = true;
    char c_stack = ' ';
    char brackets[] = {'(', ')', '[', ']', '{', '}', '<', '>'};

    StatusCode status = IsEmpty(s, &b);
    CHECK;

    if (!b)
    {
        status = Get(s, &c_stack);
        CHECK;
        if ((i % 2 == 1) && c_stack == brackets[i - 1])
            return STATUS_SUCCESS;
    }

    return STATUS_ERROR_NOT_ENOUGH_BRACKETS;
}

StatusCode Pop(Stack *s)
{
    if (s == NULL)
        return STATUS_ERROR_NOT_CREATED_STACK;
    if (s->size == 0)
        return STATUS_ERROR_EMPTY_STACK;

    s->size--;
    return STATUS_SUCCESS;
}

StatusCode Get(Stack *s, char *c)
{
    if (s == NULL)
        return STATUS_ERROR_NOT_CREATED_STACK;

    if (c == NULL)
        return STATUS_ERROR_WRONG_ARGUMENT;

    if (s->size == 0)
        return STATUS_ERROR_EMPTY_STACK;

    *c = s->str[s->size - 1];
    return STATUS_SUCCESS;
}

StatusCode IsEmpty(Stack *s, bool *b)
{
    if (s == NULL)
        return STATUS_ERROR_NOT_CREATED_STACK;

    *b = (s->size == 0);
    return STATUS_SUCCESS;
}

void DeleteStack(Stack *s)
{
    if (s == NULL)
        return;
    free(s->str);
    s->str = NULL;
    s->capacity = 0;
    s->size = 0;
}
