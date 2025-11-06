#include "../include/Calculate.h"

// подставляет значения переменных в выражение
void Substitute_Variables(const char *expr, char *out, char *mem[26])
{
    char *ptr_out = out;

    for (const char *ptr = expr; *ptr != '\0'; ptr++)
    {
        if (isupper((unsigned char)*ptr))
        {
            int idx = *ptr - 'A';
            if (mem[idx] != NULL)
            {
                size_t len = strlen(mem[idx]);
                memcpy(ptr_out, mem[idx], len);
                ptr_out += len;
            }
            else
                *ptr_out++ = '0';
        }
        else
            *ptr_out++ = *ptr;
    }

    *ptr_out = '\0';
}

int power(int a, int b)
{
    if (b == 0)
        return 1;
    int result = 1;
    for (int i = 0; i < b; i++)
        result *= a;
    return result;
}

StatusCode Calc(char oper, char *first, char *second, char result[])
{
    int int_result = 0;
    switch (oper)
    {
    case '-':
    {
        int_result = atoi(first) - atoi(second);
        break;
    }
    case '+':
    {
        int_result = atoi(first) + atoi(second);
        break;
    }
    case '*':
    {
        int_result = atoi(first) * atoi(second);
        break;
    }
    case '/':
    {
        if (atoi(second) == 0)
            return DIVISION_BY_ZERO;
        int_result = atoi(first) / atoi(second);
        break;
    }
    case '^':
    {
        int_result = power(atoi(first), atoi(second));
        break;
    }
    }
    sprintf(result, "%d", int_result);
    return SUCCESS;
}

StatusCode Rpn_Calculate(Stack *s, int *result)
{
    if (s == NULL || result == NULL)
        return WRONG_ARGUMENT;

    Stack tmp;
    StatusCode status = SUCCESS;

    status = Init_Stack(&tmp);
    CHECK;

    int size = 0;
    status = Stack_Size(s, &size);
    CHECK;

    char *str = (char *)malloc(INT_MAX_LEN * sizeof(char));
    if (str == NULL)
        return MEMORY_ALLOCATE;

    for (int i = 0; i < size; i++)
    {
        status = Stack_Pop(s, &str);
        CHECK;
        status = Stack_Push(&tmp, str);
        CHECK;
    }

    char *first = (char *)malloc(100 * sizeof(char));
    char *second = (char *)malloc(100 * sizeof(char));

    for (int i = 0; i < size; i++)
    {
        status = Stack_Pop(&tmp, &str);
        CHECK;

        if (strlen(str) == 1 && !isdigit(*str))
        {
            char temp_calc[123] = {0};
            Stack_Pop(s, &second);
            Stack_Pop(s, &first);
            status = Calc(*str, first, second, temp_calc);
            CHECK;

            Stack_Push(s, temp_calc);
        }
        else
            Stack_Push(s, str);
    }

    char *temp_result = NULL;
    Stack_Pop(s, &temp_result);
    *result = atoi(temp_result);
    free(temp_result);

    free(str);
    free(first);
    free(second);
    Stack_Destroy(&tmp);
    return SUCCESS;
}