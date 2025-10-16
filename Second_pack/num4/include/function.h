#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int overfscanf(FILE *stream, const char *format, ...);
int oversscanf(const char *str, const char *format, ...);

#endif // FUNCTION_H