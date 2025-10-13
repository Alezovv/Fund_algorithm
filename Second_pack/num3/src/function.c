#include "../include/function.h"

static void to_roman(int num, char *result)
{
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char *numerals[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    result[0] = '\0';

    for (int i = 0; i < 13; i++)
    {
        while (num >= values[i])
        {
            strcat(result, numerals[i]);
            num -= values[i];
        }
    }
}

static void cekendorf(int number, char *str)
{
    int fib[32];
    int fib_size = 0;
    fib[0] = 1;
    fib[1] = 2;
    fib_size = 2;

    while (fib_size < 32)
    {
        int next = fib[fib_size - 1] + fib[fib_size - 2];
        if (next > number)
            break;
        fib[fib_size] = next;
        fib_size++;
    }

    int bits[32];
    int bit_count = 0;
    int n = number;
    for (int i = fib_size - 1; i >= 0; i--)
    {
        if (n >= fib[i])
        {
            bits[bit_count++] = 1;
            n -= fib[i];
            i--;
        }
        else
        {
            bits[bit_count++] = 0;
        }
    }

    bits[bit_count++] = 1;

    int pos = 0;
    for (int i = 0; i < bit_count; i++)
    {
        pos += sprintf(str + pos, "%d", bits[i]);
        if (i < bit_count - 1)
        {
            pos += sprintf(str + pos, " ");
        }
    }
}

static void char_sys(int val, int base, int capital, char *result)
{
    char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char digits_u[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int sign = 1;
    int i = 0;

    if (val == 0)
    {
        result[0] = '0';
        result[1] = '\0';
        return;
    }

    if (val < 0)
    {
        sign = -1;
        val = -val;
    }

    while (val > 0)
    {
        int tmp = val % base;
        if (capital == 0)
            result[i++] = digits[tmp];
        else
            result[i++] = digits_u[tmp];
        val /= base;
    }

    if (sign == -1)
        result[i++] = '-';

    for (int j = 0; j < i / 2; j++)
    {
        char temp = result[j];
        result[j] = result[i - j - 1];
        result[i - j - 1] = temp;
    }
    result[i] = '\0';
}

static void to_decimal(const char *str, int base, int capital, int *result)
{
    int sign = 1;
    *result = 0;
    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    for (const char *p = str; *p != '\0'; p++)
    {
        int value;
        char c = *p;
        if (c >= '0' && c <= '9')
            value = c - '0';
        else if (capital == 0 && c >= 'a' && c <= 'z')
            value = c - 'a' + 10;
        else if (capital == 1 && c >= 'A' && c <= 'Z')
            value = c - 'A' + 10;
        else
            break;

        if (value >= base)
            break;

        *result = *result * base + value;
    }
    if (sign == -1)
        *result = -*result;
}

static void memory_dump(__int32_t value, char *result)
{
    unsigned char *p = (unsigned char *)&value;
    char *r = result;

    for (int i = 0; i < 4; i++)
    {
        for (int b = 7; b >= 0; b--)
        {
            *r = ((p[i] >> b) & 1) ? '1' : '0';
            r++;
        }
        if (i != 3)
        {
            *r = ' ';
            r++;
        }
    }
    *r = '\0';
}

static void memory_dump_unsigned(__uint32_t value, char *result)
{
    unsigned char *p = (unsigned char *)&value;
    char *r = result;

    for (int i = 0; i < 4; i++)
    {
        for (int b = 7; b >= 0; b--)
        {
            *r = ((p[i] >> b) & 1) ? '1' : '0';
            r++;
        }
        if (i != 3)
        {
            *r = ' ';
            r++;
        }
    }
    *r = '\0';
}

static void memory_dump_double(double value, char *result)
{
    unsigned char *p = (unsigned char *)&value;
    char *r = result;

    for (int i = 0; i < 8; i++)
    {
        for (int b = 7; b >= 0; b--)
        {
            *r = ((p[i] >> b) & 1) ? '1' : '0';
            r++;
        }
        if (i != 7)
        {
            *r = ' ';
            r++;
        }
    }
    *r = '\0';
}

static void memory_dump_float(float value, char *result)
{
    unsigned char *p = (unsigned char *)&value;
    char *r = result;

    for (int i = 0; i < 4; i++)
    {
        for (int b = 7; b >= 0; b--)
        {
            *r = ((p[i] >> b) & 1) ? '1' : '0';
            r++;
        }
        if (i != 3)
        {
            *r = ' ';
            r++;
        }
    }
    *r = '\0';
}

int overfprintf(FILE *stream, const char *format, ...)
{
    if (stream == NULL || format == NULL)
        return -1;

    va_list args;
    va_start(args, format);
    int count = 0;
    for (const char *p = format; *p != '\0'; p++)
    {
        if (*p != '%')
        {
            fputc(*p, stream);
            count++;
            continue;
        }
        p++;
        if (*p == '\0')
        {
            va_end(args);
            return -1;
        }

        switch (*p)
        {
        case 'd':
        {
            int val = va_arg(args, int);
            count += fprintf(stream, "%d", val);
            break;
        }
        case 's':
        {
            const char *str = va_arg(args, const char *);
            count += fprintf(stream, "%s", str);
            break;
        }
        case 'c':
        {

            char c = va_arg(args, int);
            count += fprintf(stream, "%c", c);
            break;
        }
        case 'R':
            if (*(p + 1) == 'o')
            {
                p++;
                int val = va_arg(args, int);
                if (val < 1 || val > 3999)
                {
                    count += fprintf(stream, "%d", val);
                }
                else
                {
                    char result[20];
                    to_roman(val, result);
                    count += fprintf(stream, "%s", result);
                }
            }
            else
            {
                if (fputc('%', stream) == EOF || fputc(*p, stream) == EOF)
                {
                    va_end(args);
                    return -1;
                }
                count += 2;
            }
            break;
        case 'Z':
        {
            if (*(p + 1) == 'r')
            {
                p++;

                int val = va_arg(args, int);
                if (val < 1)
                {
                    count += fprintf(stream, "%d", val);
                }
                else
                {
                    char result[64];
                    cekendorf(val, result);
                    count += fprintf(stream, "%s", result);
                }
            }
            else
            {
                if (fputc('%', stream) == EOF || fputc(*p, stream) == EOF)
                {
                    va_end(args);
                    return -1;
                }
                count += 2;
            }
            break;
        }
        case 'C':
        {
            if (*(p + 1) == 'v' || *(p + 1) == 'V')
            {
                p++;
                int val = va_arg(args, int);
                int base = va_arg(args, int);
                if (base < 2 || base > 36)
                    base = 10;
                char result[64];
                int capital = 0;
                if (*p == 'V')
                    capital = 1;
                char_sys(val, base, capital, result);
                count += fprintf(stream, "%s", result);
            }
            else
            {
                if (fputc('%', stream) == EOF || fputc(*p, stream) == EOF)
                {
                    va_end(args);
                    return -1;
                }
            }
            break;
        }
        case 't':
        {
            if (*(p + 1) == 'o')
            {
                p++;
                const char *str = va_arg(args, const char *);
                if (!str)
                    str = "0";
                int base = va_arg(args, int);
                if (base < 2 || base > 36)
                    base = 10;
                int result = 0;
                to_decimal(str, base, 0, &result);
                count += fprintf(stream, "%d", result);
            }
            else
            {
                if (fputc('%', stream) == EOF || fputc(*p, stream) == EOF)
                {
                    va_end(args);
                    return -1;
                }
            }
            break;
        }
        case 'T':
        {
            if (*(p + 1) == 'O')
            {
                p++;
                const char *str = va_arg(args, const char *);
                if (!str)
                    str = "0";
                int base = va_arg(args, int);
                if (base < 2 || base > 36)
                    base = 10;
                int result = 0;
                to_decimal(str, base, 1, &result);
                count += fprintf(stream, "%d", result);
            }
            else
            {
                if (fputc('%', stream) == EOF || fputc(*p, stream) == EOF)
                {
                    va_end(args);
                    return -1;
                }
            }
            break;
        }
        case 'm':
        {
            switch (*(p + 1))
            {
            case 'i':
            {
                p++;
                __int32_t value = va_arg(args, __int32_t);
                char result[36];
                memory_dump(value, result);
                count += fprintf(stream, "%s", result);
                break;
            }
            default:
            {
                if (fputc('%', stream) == EOF || fputc(*p, stream) == EOF)
                {
                    va_end(args);
                    return -1;
                }
                count += 2;
                break;
            }
            case 'u':
            {
                p++;
                __uint32_t value = va_arg(args, __uint32_t);
                char result[36];
                memory_dump_unsigned(value, result);
                count += fprintf(stream, "%s", result);
                break;
            }
            case 'd':
                p++;
                double val_d = va_arg(args, double);
                char result_d[80];
                memory_dump_double(val_d, result_d);
                count += fprintf(stream, "%s", result_d);
                break;
            case 'f':
                p++;
                float val_f = (float)va_arg(args, double);
                char result_f[36];
                memory_dump_float(val_f, result_f);
                count += fprintf(stream, "%s", result_f);
                break;
            }
            break;
        }
        default:
        {
            if (fputc('%', stream) == EOF || fputc(*p, stream) == EOF)
            {
                va_end(args);
                return -1;
            }
            count += 2;
            break;
        }
        }
    }
    va_end(args);
    return count;
}

int oversprintf(char *str, const char *format, ...)
{
    if (!str || !format)
        return -1;

    va_list args;
    va_start(args, format);
    int count = 0;
    char *buf = str;

    for (const char *p = format; *p; p++)
    {
        if (*p != '%')
        {
            *buf++ = *p;
            count++;
            continue;
        }

        p++;
        if (!*p)
        {
            va_end(args);
            return -1;
        }

        switch (*p)
        {
        case 'd':
        {
            int val = va_arg(args, int);
            int n = sprintf(buf, "%d", val);
            buf += n;
            count += n;
            break;
        }
        case 's':
        {
            const char *s = va_arg(args, const char *);
            int n = sprintf(buf, "%s", s);
            buf += n;
            count += n;
            break;
        }
        case 'c':
        {
            char c = (char)va_arg(args, int);
            *buf++ = c;
            count++;
            break;
        }
        case 'R':
        {
            if (*(p + 1) == 'o')
            {
                p++;
                int val = va_arg(args, int);
                char result[20];
                if (val < 1 || val > 3999)
                    buf += sprintf(buf, "%d", val);
                else
                {
                    to_roman(val, result);
                    int n = sprintf(buf, "%s", result);
                    buf += n;
                    count += n;
                }
            }
            else
            {
                *buf++ = '%';
                *buf++ = *p;
                count += 2;
            }
            break;
        }
        case 'Z':
        {
            if (*(p + 1) == 'r')
            {
                p++;
                unsigned int val = va_arg(args, unsigned int);
                char result[64];
                cekendorf(val, result);
                int n = sprintf(buf, "%s", result);
                buf += n;
                count += n;
            }
            else
            {
                *buf++ = '%';
                *buf++ = *p;
                count += 2;
            }
            break;
        }
        case 'C':
        {
            if (*(p + 1) == 'v' || *(p + 1) == 'V')
            {
                int capital = (*(p + 1) == 'V') ? 1 : 0;
                p++;
                int val = va_arg(args, int);
                int base = va_arg(args, int);
                if (base < 2 || base > 36)
                    base = 10;
                char result[64];
                char_sys(val, base, capital, result);
                int n = sprintf(buf, "%s", result);
                buf += n;
                count += n;
            }
            else
            {
                *buf++ = '%';
                *buf++ = *p;
                count += 2;
            }
            break;
        }
        case 't':
        {
            if (*(p + 1) == 'o')
            {
                p++;
                const char *s = va_arg(args, const char *);
                if (!s)
                    s = "0";
                int base = va_arg(args, int);
                if (base < 2 || base > 36)
                    base = 10;
                int result;
                to_decimal(s, base, 0, &result);
                int n = sprintf(buf, "%d", result);
                buf += n;
                count += n;
            }
            else
            {
                *buf++ = '%';
                *buf++ = *p;
                count += 2;
            }
            break;
        }
        case 'T':
        {
            if (*(p + 1) == 'O')
            {
                p++;
                const char *s = va_arg(args, const char *);
                if (!s)
                    s = "0";
                int base = va_arg(args, int);
                if (base < 2 || base > 36)
                    base = 10;
                int result;
                to_decimal(s, base, 1, &result);
                int n = sprintf(buf, "%d", result);
                buf += n;
                count += n;
            }
            else
            {
                *buf++ = '%';
                *buf++ = *p;
                count += 2;
            }
            break;
        }
        case 'm':
        {
            switch (*(p + 1))
            {
            case 'i':
            {
                p++;
                __int32_t val = va_arg(args, __int32_t);
                char result[36];
                memory_dump(val, result);
                int n = sprintf(buf, "%s", result);
                buf += n;
                count += n;
                break;
            }
            case 'u':
            {
                p++;
                __uint32_t val = va_arg(args, __uint32_t);
                char result[36];
                memory_dump_unsigned(val, result);
                int n = sprintf(buf, "%s", result);
                buf += n;
                count += n;
                break;
            }
            case 'd':
            {
                p++;
                double val = va_arg(args, double);
                char result[80];
                memory_dump_double(val, result);
                int n = sprintf(buf, "%s", result);
                buf += n;
                count += n;
                break;
            }
            case 'f':
            {
                p++;
                float val = (float)va_arg(args, double);
                char result[36];
                memory_dump_float(val, result);
                int n = sprintf(buf, "%s", result);
                buf += n;
                count += n;
                break;
            }
            default:
            {
                *buf++ = '%';
                *buf++ = *p;
                count += 2;
                break;
            }
            }
            break;
        }
        default:
        {
            *buf++ = '%';
            *buf++ = *p;
            count += 2;
            break;
        }
        }
    }

    *buf = '\0';
    va_end(args);
    return count;
}
