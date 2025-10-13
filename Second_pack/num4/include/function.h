#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdarg.h>

int overfscanf(FILE *stream, const char *format, ...);
int oversscanf(const char *str, const char *format, ...);

#endif // FUNCTION_H