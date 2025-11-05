#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "./Stack.h"
#include "./StatusCode.h"
#include <ctype.h>

#define OPERATOR {'+', '-', '*', '/', '^'}

StatusCode Dijkstra(const char *str, Stack *s_rpn);

#endif // DIJKSTRA_H