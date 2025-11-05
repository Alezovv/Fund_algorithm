#ifndef CALCULATE_H
#define CALCULATE_H

#include "./StatusCode.h"
#include "./Stack.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

void Substitute_Variables(const char *expr, char *out, char *mem[26]);

StatusCode Rpn_Calculate(Stack *s, int *result);

#endif // CALCULATE_H