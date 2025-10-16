#include "../include/function.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

static int tolow(const char *s1, const char *s2, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        char c1 = (char)tolower((unsigned char)s1[i]);
        char c2 = (char)tolower((unsigned char)s2[i]);
        if (c1 != c2)
            return c1 - c2;
        if (c1 == '\0')
            break;
    }
    return 0;
}

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
            if (tolow(p, numerals[i], len) == 0)
            {
                *result += values[i];
                p += len;
                matched = 1;
                break;
            }
        }
        if (!matched)
            break;
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
    if (len < 2 || z[len - 1] != '1')
        return 0;

    for (int i = 0; i < len - 1; i++)
        if (z[i] == '1')
            result += fib[i];
    return result;
}

static void read_token(FILE *stream, char *buf, size_t size)
{
    int c;
    size_t i = 0;

    while ((c = fgetc(stream)) != EOF && isspace(c))
        ;

    if (c == EOF)
    {
        buf[0] = '\0';
        return;
    }

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

    for (const char *p = format; *p; p++)
    {
        if (*p != '%')
            continue;
        p++;

        switch (*p)
        {
        case 'R':
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
        case 'Z':
            if (*(p + 1) == 'r')
            {
                p++;
                unsigned int *out = va_arg(args, unsigned int *);
                char token[128];
                read_token(stream, token, sizeof(token));
                *out = zeckendorf_to_uint(token);
                count++;
            }
            break;
        case 'C':
            if (*(p + 1) == 'v' || *(p + 1) == 'V')
            {
                int upper = (*(p + 1) == 'V');
                p++;
                int *out = va_arg(args, int *);
                int base = va_arg(args, int);
                if (base < 2 || base > 36)
                    base = 10;
                char token[128];
                read_token(stream, token, sizeof(token));
                if (upper)
                    for (char *t = token; *t; t++)
                        *t = (char)toupper(*t);
                else
                    for (char *t = token; *t; t++)
                        *t = (char)tolower(*t);
                *out = (int)strtol(token, NULL, base);
                count++;
            }
            break;
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

int oversscanf(const char *str, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    const char *p = format;
    const char *s = str;
    int count = 0;
    char token[128];

    while (*p)
    {
        if (*p == '%')
        {
            p++;
            while (isspace((unsigned char)*s))
                s++;

            if (strncmp(p, "Ro", 2) == 0)
            {
                int *out = va_arg(args, int *);
                sscanf(s, "%127s", token);
                from_rom(token, out);
                s += strlen(token);
                count++;
                p += 2;
            }
            else if (strncmp(p, "Zr", 2) == 0)
            {
                unsigned int *out = va_arg(args, unsigned int *);
                sscanf(s, "%127s", token);
                *out = zeckendorf_to_uint(token);
                s += strlen(token);
                count++;
                p += 2;
            }
            else if (strncmp(p, "Cv", 2) == 0 || strncmp(p, "CV", 2) == 0)
            {
                int upper = (p[1] == 'V');
                int *out = va_arg(args, int *);
                int base = va_arg(args, int);
                if (base < 2 || base > 36)
                    base = 10;

                sscanf(s, "%127s", token);
                if (upper)
                    for (char *t = token; *t; t++)
                        *t = (char)toupper(*t);
                else
                    for (char *t = token; *t; t++)
                        *t = (char)tolower(*t);

                *out = (int)strtol(token, NULL, base);
                s += strlen(token);
                count++;
                p += 2;
            }
            else
            {
                char fmt[8];
                snprintf(fmt, sizeof(fmt), "%%%c", *p);
                void *ptr = va_arg(args, void *);
                int cnt = sscanf(s, fmt, ptr);
                if (cnt > 0)
                    count += cnt;
                p++;
            }
        }
        else
            p++;
    }

    va_end(args);
    return count;
}
