#ifndef UTILS_H
#define UTILS_H

#include "../include/Liver_List.h"
#include "../include/StatusCode.h"
#include <stdlib.h>
#include <stdio.h>

void print_usage();

void select_options();

StatusCode valid_path(const char *path);

StatusCode scan_file(const char *path, list *lst);

StatusCode write_to_file(const char *path, list *lst);

#endif // UTILS_H
