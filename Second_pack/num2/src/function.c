#include "../include/function.h"

void *memchr(const void *str, int c, size_t n)
{
    const unsigned char *p = (const unsigned char *)str;
    unsigned char uc = (unsigned char)c;

    for (size_t i = 0; i < n; i++)
    {
        if (p[i] == uc)
            return (void *)(p + i);
    }

    return NULL;
}

int memcmp(const void *str1, const void *str2, size_t n)
{
    const unsigned char *p1 = (const unsigned char *)str1;
    const unsigned char *p2 = (const unsigned char *)str2;
    for (size_t i = 0; i < n; i++)
    {
        if (p1[i] != p2[i])
        {
            return (int)p1[i] - (int)p2[i];
        }
    }
    return 0;
}

void *memcpy(void *dest, const void *src, size_t n)
{
    const unsigned char *p1 = (const unsigned char *)src;
    unsigned char *p2 = (unsigned char *)dest;
    for (size_t i = 0; i < n; i++)
        p2[i] = p1[i];

    return dest;
}

void *memset(void *str, int c, size_t n)
{
    unsigned char *p = (unsigned char *)str;
    unsigned char uc = (unsigned char)c;

    for (size_t i = 0; i < n; i++)
        p[i] = uc;

    return str;
}

char *strncat(char *dest, const char *src, size_t n)
{
    char *d = dest;
    while (*d != '\0')
        d++;

    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++)
        d[i] = src[i];

    d[i] = '\0';

    return dest;
}

char *strchr(const char *str, int c)
{
    char ch = (char)c;
    while (*str != '\0')
    {
        if (*str == ch)
            return (char *)str;
        str++;
    }

    if (ch == '\0')
        return (char *)str;
    return NULL;
}

int strncmp(const char *str1, const char *str2, size_t n)
{
    size_t i;
    for (i = 0; i < n; i++)
    {
        unsigned char c1 = (unsigned char)str1[i];
        unsigned char c2 = (unsigned char)str2[i];

        if (c1 != c2)
            return c1 - c2;
        if (c1 == '\0')
            return 0;
    }
    return 0;
}

char *strncpy(char *dest, const char *src, size_t n)
{
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];

    for (; i < n; i++)
        dest[i] = '\0';

    return dest;
}

size_t strcspn(const char *str1, const char *str2)
{
    size_t count = 0;

    for (; str1[count] != '\0'; count++)
    {
        const char *s = str2;
        while (*s != '\0')
        {
            if (str1[count] == *s)
                return count;
            s++;
        }
    }

    return count;
}

#if defined(__APPLE__)
#define ERRMSG_COUNT 5
static const char *error_messages[ERRMSG_COUNT] = {
    "Undefined error: 0",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call"};
#elif defined(__linux__)
#define ERRMSG_COUNT 5
static const char *error_messages[ERRMSG_COUNT] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call"};
#else
#define ERRMSG_COUNT 1
static const char *error_messages[ERRMSG_COUNT] = {
    "Unknown OS error messages"};
#endif

char *strerror(int errnum)
{
    if (errnum < 0 || errnum >= ERRMSG_COUNT)
        return "Unknown error";
    return (char *)error_messages[errnum];
}

size_t strlen(const char *str)
{
    size_t len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

char *strpbrk(const char *str1, const char *str2)
{
    for (size_t i = 0; str1[i] != '\0'; i++)
    {
        for (size_t j = 0; str2[j] != '\0'; j++)
        {
            if (str1[i] == str2[j])
                return (char *)(str1 + i);
        }
    }
    return NULL;
}

char *strrchr(const char *str, int c)
{
    const char *last = NULL;
    char ch = (char)c;

    while (*str != '\0')
    {
        if (*str == ch)
            last = str;
        str++;
    }

    if (ch == '\0')
        return (char *)str;

    return (char *)last;
}

char *strstr(const char *haystack, const char *needle)
{
    if (*needle == '\0')
        return (char *)haystack;

    for (; *haystack != '\0'; haystack++)
    {
        const char *h = haystack;
        const char *n = needle;

        while (*h != '\0' && *n != '\0' && *h == *n)
        {
            h++;
            n++;
        }

        if (*n == '\0')
            return (char *)haystack;
    }

    return NULL;
}

char *strtok(char *str, const char *delim)
{
    static char *next = NULL;

    if (str != NULL)
        next = str;
    if (next == NULL)
        return NULL;

    char *start = next;
    while (*start != '\0')
    {
        int is_delim = 0;
        for (size_t i = 0; delim[i] != '\0'; i++)
        {
            if (*start == delim[i])
            {
                is_delim = 1;
                break;
            }
        }
        if (!is_delim)
            break;
        start++;
    }

    if (*start == '\0')
    {
        next = NULL;
        return NULL;
    }

    char *end = start;
    while (*end != '\0')
    {
        int is_delim = 0;
        for (size_t i = 0; delim[i] != '\0'; i++)
        {
            if (*end == delim[i])
            {
                is_delim = 1;
                break;
            }
        }
        if (is_delim)
        {
            *end = '\0';
            next = end + 1;
            return start;
        }
        end++;
    }

    next = NULL;
    return start;
}