#ifndef CHECK_BRACKETS_H
#define CHECK_BRACKETS_H

#include "./StatusCode.h"
#include "./Stack.h"
#include <stdlib.h>

#define BRACKETS {'(', ')', '[', ']', '{', '}', '<', '>'}
#define COUNT_BRACKETS 9
#define MAX_VALUE 100

StatusCode check_brackets(Stack *s, const char *str);

#endif // CHECK_BRACKETS_H