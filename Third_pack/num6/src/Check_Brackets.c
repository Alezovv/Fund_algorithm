#include "../include/Check_Brackets.h"

StatusCode check_brackets(Stack *s, const char *str)
{
    if (s == NULL || str == NULL)
        return STATUS_ERROR_WRONG_ARGUMENT;

    char brackets[8] = {'(', ')', '[', ']', '{', '}', '<', '>'};
    StatusCode status = STATUS_SUCCESS;

    for (const char *ptr = str; *ptr != '\0'; ptr++)
    {
        char tmp = *ptr;

        for (size_t i = 0; i < 8; i++)
        {
            if (tmp == brackets[i])
            {
                if (i % 2 == 0)
                {
                    status = Push(s, brackets[i]);
                    if (status != STATUS_SUCCESS)
                        return status;
                }
                else
                {
                    status = LegitBrackets(s, i);
                    CHECK;
                    status = Pop(s);
                    CHECK;
                }
            }
        }
    }

    bool b = true;
    status = IsEmpty(s, &b);
    CHECK;
    if (!b)
        return STATUS_ERROR_NOT_ENOUGH_BRACKETS;

    return STATUS_SUCCESS;
}
