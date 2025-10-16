#include "../include/function.h"

static void from_rom(const char *str, int *result)
{
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *numerals[] = {"M", "CM", "D", "CD", "C", "XC",
                              "L", "XL", "X", "IX", "V", "IV", "I"};

    *result = 0;
    const char *p = str;

    while (*p)
    {
        int matched = 0;
        for (int i = 0; i < 13; i++)
        {
            size_t len = strlen(numerals[i]);
            if (strncmp(p, numerals[i], len) == 0)
            {
                *result += values[i];
                p += len;
                matched = 1;
                break;
            }
        }
        if (!matched)
            p++;
    }
}

unsigned int zeckendorf_to_uint(const char *z)
{
    unsigned int fib[64];
    fib[0] = 1;
    fib[1] = 2;
    for (int i = 2; i < 64; i++)
        fib[i] = fib[i - 1] + fib[i - 2];

    unsigned int result = 0;
    int len = strlen(z);
    for (int i = 0; i < len - 1; i++)
        if (z[i] == '1')
            result += fib[i];
    return result;
}

static void read_token(FILE *stream, char *buf, size_t size)
{
    int c = 0;
    size_t i = 0;
    while ((c = fgetc(stream)) != EOF && isspace(c))
        ;
    if (c == EOF)
        buf[0] = '\0';
    do
    {
        if (isspace(c))
            break;
        if (i < size - 1)
            buf[i++] = (char)c;
    } while ((c = fgetc(stream)) != EOF);

    buf[i] = '\0';
}

int overfscanf(FILE *stream, const char *format, ...)
{
    if (stream == NULL || format == NULL)
        return -1;
    va_list args;
    va_start(args, format);
    int count = 0;

    for (const char *p = format; *p != '\0'; p++)
    {
        if (*p != '%')
            continue;
        p++;

        switch (*p)
        {
        case 'R':
        {
            if (*(p + 1) == 'o')
            {
                p++;
                int *out = va_arg(args, int *);
                char token[128];
                read_token(stream, token, sizeof(token));
                from_rom(token, out);
                count++;
            }
            break;
        }
        case 'Z':
        {
            if (*(p + 1) == 'r')
            {
                p++;
                unsigned int *val = va_arg(args, unsigned int *);
                char token[128];
                read_token(stream, token, sizeof(token));
                *val = zeckendorf_to_uint(token);
                count++;
            }
            break;
        }
        case 'C':
        {
            if (*(p + 1) == 'v' || *(p + 1) == 'V')
            {
                int up = (*(p + 1) == 'V');
                p++;

                int *out = va_arg(args, int *);
                int base = va_arg(args, int);
                if (base < 2 || base > 36)
                    base = 10;

                char token[128];
                read_token(stream, token, sizeof(token));

                if (up)
                {
                    for (char *t = token; *t; t++)
                        *t = (char)toupper(*t);
                }
                else
                {
                    for (char *t = token; *t; t++)
                        *t = (char)tolower(*t);
                }

                *out = (int)strtol(token, NULL, base);
                count++;
            }
            break;
        }
        default:
        {
            char fmt[8] = {'%', *p, '\0'};
            void *ptr = va_arg(args, void *);
            if (fscanf(stream, fmt, ptr) == 1)
                count++;
            break;
        }
        }
    }
    va_end(args);
    return count;
}