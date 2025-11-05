#include "../include/StatusCode.h"

StatusCode Validate_Expression(char *str, int *is_print)
{
    if (str == NULL)
        return WRONG_ARGUMENT;

    int len = strlen(str);
    if (len == 0)
        return WRONG_ARGUMENT;

    int has_print = 0;
    int has_expression = 0;
    int equals_count = 0;
    int expect_operand = 1;
    int paren_count = 0;
    int in_print = 0;
    int has_content = 0;

    *is_print = 0;

    for (int i = 0; i < len; i++)
    {
        if (isspace(str[i]))
            continue;

        has_content = 1;

        // Проверка на print(
        if (!in_print && !has_expression && i + 6 <= len && strncmp(&str[i], "print(", 6) == 0)
        {
            has_print = 1;
            in_print = 1;
            paren_count = 1;
            i += 5;
            *is_print = 1;
            continue;
        }

        if (in_print)
        {
            if (str[i] == '(')
                paren_count++;
            else if (str[i] == ')')
            {
                paren_count--;
                if (paren_count == 0)
                {
                    in_print = 0;
                    for (int j = i + 1; j < len; j++)
                    {
                        if (!isspace(str[j]))
                            return WRONG_ARGUMENT;
                    }
                    break;
                }
            }
            else if (!isupper(str[i]) && !isspace(str[i]))
                return WRONG_ARGUMENT;
            continue;
        }

        has_expression = 1;
        *is_print = 0;

        if (expect_operand)
        {
            if (isupper(str[i]))
                expect_operand = 0;
            else if (isdigit(str[i]))
            {
                while (i < len && isdigit(str[i]))
                    i++;
                i--;
                expect_operand = 0;
            }
            else if (str[i] == '=' && equals_count == 0)
            {
                equals_count++;
                expect_operand = 1;
            }
            else
                return WRONG_ARGUMENT;
        }
        else
        {
            if (str[i] == '+' || str[i] == '-' || str[i] == '*' ||
                str[i] == '/' || str[i] == '^')
                expect_operand = 1;
            else if (str[i] == '=' && equals_count == 0)
            {
                equals_count++;
                expect_operand = 1;
            }
            else
                return WRONG_ARGUMENT;
        }
    }

    if (in_print)
        return WRONG_ARGUMENT;
    if (has_expression && expect_operand)
        return WRONG_ARGUMENT;
    if (!has_content)
        return WRONG_ARGUMENT;
    if (has_print && has_expression)
        return WRONG_ARGUMENT;

    return SUCCESS;
}