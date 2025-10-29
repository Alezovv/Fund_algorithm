#include "../include/Utils.h"

void print_usage()
{
    printf("Usage: <program> <in_file_path> <out_file_path>\n");
    printf("Example: main ./file.txt ./out.txt\n");
}

void print_options()
{
    printf("\nSelect option: \n");
    printf("0 - Search by:\n");
    printf("1 - Sort by:\n");
}

void print_attribute()
{
    printf("\nSelect attribute: \n");
    printf("0 - id\n");
    printf("1 - surname\n");
    printf("2 - name\n");
    printf("3 - group\n");
}

void status_handle(StatusCode status)
{
    switch (status)
    {
    case WRONG_FILE_PATH:
    {
        printf("Input valid path to file\n");
        break;
    }
    case WRONG_ID:
    {
        printf("Input valid id\n");
        break;
    }
    case WRONG_NAME:
    {
        printf("Input valid name\n");
        break;
    }
    case WRONG_GROUP:
    {
        printf("Input valid group\n");
        break;
    }
    case ERROR_ALLOCATE_MEMORY:
    {
        printf("ERROR: no memory allocated!\n");
        break;
    }
    case WRONG_NOTES:
    {
        printf("Input valid notes!\n");
        break;
    }
    case ERROR_VALID:
    {
        printf("Wrong data!\n");
        break;
    }
    case ERROR_NOT_FOUND:
    {
        printf("Student not found!\n");
        break;
    }
    default:
    {
        printf("Undefined error!\n");
        break;
    }
    }
}

void valid_handle(ValidCode status)
{
    switch (status)
    {
    case VALID_ID_ERROR:
    {
        printf("Input wrong id!\n");
        break;
    }
    case VALID_WRONG_OPTIONS:
    {
        printf("Input wrong options/attribute!\n");
        break;
    }
    case VALID_WRONG_PATH:
    {
        printf("Input valid path to file!\n");
        break;
    }
    case VALID_WRONG_ARGUMETS:
    {
        printf("Input valid arguments!\n");
        break;
    }
    case VALID_SURNAME_ERROR:
    {
        printf("Input valid surname!\n");
        break;
    }
    case VALID_GROUP_ERROR:
    {
        printf("Input valid group!\n");
        break;
    }
    default:
    {
        printf("Undefined validation error!\n");
        break;
    }
    }
}