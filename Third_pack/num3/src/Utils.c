#include "../include/Utils.h"

void print_usage()
{
    printf("Usage: <program name> <path_to_file>\n");
    printf("Example: main file.txt\n");
}

void select_options()
{
    printf("Select options\n");
    printf("0 - Search person\n");
    printf("1 - Change person\n");
    printf("2 - Delete person\n");
    printf("3 - Add person\n");
    printf("4 - Write to file\n");
    printf("5 - Discard last n / 2 modification\n");
}
