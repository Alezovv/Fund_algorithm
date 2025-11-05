#include "../include/Stack.h"

StatusCode Init_Stack(Stack *s)
{
    if (s == NULL)
        return WRONG_ARGUMENT;

    s->str = (char **)malloc(10 * sizeof(char *));
    if (s->str == NULL)
        return MEMORY_ALLOCATE;

    for (size_t i = 0; i < 10; i++)
        s->str[i] = NULL;

    s->capacity = 10;
    s->size = 0;

    return SUCCESS;
}

StatusCode Stack_Size(Stack *s, int *size)
{
    if (s == NULL || size == NULL)
        return WRONG_ARGUMENT;

    *size = s->size;
    return SUCCESS;
}

StatusCode Stack_Push(Stack *s, const char *str)
{
    if (s == NULL || str == NULL)
        return WRONG_ARGUMENT;

    if (s->size == s->capacity)
    {
        size_t new_capacity = s->capacity * 2;
        char **tmp = (char **)realloc(s->str, new_capacity * sizeof(char *));
        if (tmp == NULL)
            return MEMORY_ALLOCATE;

        s->str = tmp;
        for (size_t i = s->capacity; i < new_capacity; i++)
            s->str[i] = NULL;

        s->capacity = new_capacity;
    }

    size_t str_len = strlen(str) + 1;
    s->str[s->size] = (char *)malloc(str_len);
    if (s->str[s->size] == NULL)
        return MEMORY_ALLOCATE;

    strcpy(s->str[s->size], str);
    s->size++;

    return SUCCESS;
}

StatusCode Stack_TopLength(Stack *s, size_t *len)
{
    if (s == NULL || len == NULL)
        return WRONG_ARGUMENT;
    if (s->size == 0)
        return STACK_EMPTY;

    *len = strlen(s->str[s->size - 1]);
    return SUCCESS;
}

StatusCode Stack_Get(Stack *s, char **str)
{
    if (s == NULL || str == NULL)
        return WRONG_ARGUMENT;
    if (s->size == 0)
        return STACK_EMPTY;

    size_t len = strlen(s->str[s->size - 1]) + 1;
    *str = (char *)malloc(len);
    if (*str == NULL)
        return MEMORY_ALLOCATE;

    strcpy(*str, s->str[s->size - 1]);
    return SUCCESS;
}

StatusCode Stack_Pop(Stack *s, char **str)
{
    if (s == NULL || str == NULL)
        return WRONG_ARGUMENT;
    if (s->size == 0)
        return STACK_EMPTY;

    size_t len = strlen(s->str[s->size - 1]) + 1;
    *str = (char *)malloc(len);
    if (*str == NULL)
        return MEMORY_ALLOCATE;

    strcpy(*str, s->str[s->size - 1]);
    free(s->str[s->size - 1]);
    s->str[s->size - 1] = NULL;
    s->size--;

    return SUCCESS;
}

StatusCode Stack_Destroy(Stack *s)
{
    if (s == NULL)
        return WRONG_ARGUMENT;

    if (s->str != NULL)
    {
        for (int i = 0; i < s->size; i++)
        {
            free(s->str[i]);
            s->str[i] = NULL;
        }
        free(s->str);
        s->str = NULL;
    }

    s->size = 0;
    s->capacity = 0;

    return SUCCESS;
}

void Stack_Print(Stack *s)
{
    if (s == NULL)
        return;

    for (int i = 0; i < s->size; i++)
    {
        printf("%s ", s->str[i]);
    }
    printf("\n");
}
