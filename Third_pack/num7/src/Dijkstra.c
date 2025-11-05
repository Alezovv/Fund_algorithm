#include "../include/Dijkstra.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

StatusCode Check_Priority(char oper, int *priority)
{
    if (priority == NULL)
        return WRONG_ARGUMENT;

    switch (oper)
    {
    case '+':
    case '-':
        *priority = 1;
        break;
    case '*':
    case '/':
        *priority = 2;
        break;
    case '^':
        *priority = 3;
        break;
    default:
        return WRONG_ARGUMENT;
    }

    return SUCCESS;
}

StatusCode Dijkstra(const char *str, Stack *s_rpn)
{
    if (str == NULL || s_rpn == NULL)
        return WRONG_ARGUMENT;

    Stack s_oper;
    StatusCode status = Init_Stack(&s_oper);
    CHECK;

    status = Init_Stack(s_rpn);
    CHECK;

    char number[64];
    size_t num_len = 0;
    char *top_oper = NULL;
    int cur_priority = 0, top_priority = 0;

    for (const char *ptr = str; *ptr != '\0';)
    {
        while (isspace((unsigned char)*ptr))
            ptr++;

        // число
        if (isdigit((unsigned char)*ptr))
        {
            num_len = 0;
            while (isdigit((unsigned char)*ptr))
            {
                if (num_len < sizeof(number) - 1)
                    number[num_len++] = *ptr;
                ptr++;
            }
            number[num_len] = '\0';

            status = Stack_Push(s_rpn, number);
            CHECK;
        }
        // оператор
        else if (strchr("+-*/^", *ptr))
        {
            char op_str[2] = {*ptr, '\0'};

            while (1)
            {
                int size;
                Stack_Size(&s_oper, &size);
                if (size == 0)
                    break;

                status = Stack_Get(&s_oper, &top_oper);
                CHECK;

                if (Check_Priority(*top_oper, &top_priority) != SUCCESS)
                {
                    free(top_oper);
                    break;
                }

                Check_Priority(*ptr, &cur_priority);

                if ((cur_priority < top_priority) ||
                    (cur_priority == top_priority && *ptr != '^'))
                {
                    char *popped = NULL;
                    status = Stack_Pop(&s_oper, &popped);
                    CHECK;
                    Stack_Push(s_rpn, popped);
                    free(popped);
                }
                else
                {
                    free(top_oper);
                    break;
                }

                free(top_oper);
            }

            Stack_Push(&s_oper, op_str);
            ptr++;
        }
        else
            ptr++;
    }

    while (1)
    {
        int size;
        Stack_Size(&s_oper, &size);
        if (size == 0)
            break;

        char *popped = NULL;
        status = Stack_Pop(&s_oper, &popped);
        CHECK;
        Stack_Push(s_rpn, popped);
        free(popped);
    }

    Stack_Destroy(&s_oper);
    return SUCCESS;
}
