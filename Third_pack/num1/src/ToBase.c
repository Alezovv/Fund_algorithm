#include "../include/ToBase.h"

char *to_base_2r(unsigned int x, int n)
{
    const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUV";
    unsigned int mask = (1u << n) - 1u;

    char *result = (char *)malloc(8 * sizeof(int) + 1);
    if (!result)
        return NULL;

    char *ptr = result;
    if (x == 0)
        *ptr++ = '0';
    else
    {
        while (x)
        {
            unsigned int digit_bits = x & mask;
            *ptr++ = digits[digit_bits];
            x >>= n;
        }
    }

    *ptr = '\0';

    char *start = result;
    char *end = ptr - 1;
    while (start < end)
    {
        char tmp = *start;
        *start++ = *end;
        *end-- = tmp;
    }

    return result;
}

void print_table(int number)
{
    char **result = init_array();
    if (result == NULL)
    {
        printf("Error\n");
        return;
    }

    for (int i = 1; i <= r; i++)
        result[i - 1] = to_base_2r(number, i);

    print_array(number, result);
    free_array(result);
}