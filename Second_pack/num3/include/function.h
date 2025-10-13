#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

int overfprintf(FILE *stream, const char *format, ...);
int oversprintf(char *str, const char *format, ...);

#endif // FUNCTION_H