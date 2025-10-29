#ifndef ARR_H
#define ARR_H

#define r 5

#include <stdio.h>
#include <stdlib.h>

char **init_array();

void free_array(char **array);

void print_array(int number, char **array);

#endif // ARR_H