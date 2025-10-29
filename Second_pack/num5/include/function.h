#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_WIDTH 80

void justify_line(const char *line, char *out);

void process_line(FILE *fout, char *buffer);

#endif // FUNCTION_H