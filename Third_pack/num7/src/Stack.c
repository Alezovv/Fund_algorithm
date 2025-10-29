#include "../include/Stack.h"

StatusCode Init_Stack(Stack *s)
{
    if (s == NULL)
        return WRONG_ARGUMENT;

    s->str = (char *)malloc(10 * sizeof(char));
    if (s->str == NULL)
        return MEMORY_ALLOCATE;

    s->capacity = 10;
    s->size = 0;

    return SUCCESS;
}

StatusCode Stack_Push(Stack *s, char symbol)
{
    if (s == NULL || symbol == NULL)
        return WRONG_ARGUMENT;

    if (s->size == s->capacity)
    {
        char *tmp = (char *)realloc(s->str, 2 * s->capacity);
        if (tmp == NULL)
            return MEMORY_ALLOCATE;

        s->str = tmp;
        s->capacity *= 2;
    }
    s->str[s->size++] = symbol;
    return SUCCESS;
}

StatusCode Stack_Get(Stack *s, char *symbol)
{
    if (s == NULL)
        return WRONG_ARGUMENT;
    if (s->size == 0)
        return STACK_EMPTY;

    *symbol = s->str[s->size - 1];
    return SUCCESS;
}

StatusCode Stack_Pop(Stack *s, char *symbol)
{
    if (s == NULL)
        return WRONG_ARGUMENT;
    if (s->size == 0)
        return STACK_EMPTY;

    *symbol = s->str[s->size - 1];
    s->size--;
    return SUCCESS;
}

StatusCode Stack_Destroy(Stack *s)
{
    if (s == NULL)
        return WRONG_ARGUMENT;

    free(s->str);
    s->str = NULL;

    s->size = 0;
    s->capacity = 0;
    return SUCCESS;
}