#include <stdio.h>
#include <string.h>
#include "../include/validations.h"
#include "../include/flags.h"

void print_usage(void)
{
    printf("Usage: <program> <flag> <name_file> (<name_output_file>)\n");
    printf("Flags:\n");
    printf("  -d  excludes Arabic numerals\n");
    printf("  -i  find out the number of letters in the Latin alphabet\n");
    printf("  -s  Find out how many characters there are that are not Latin letters, Arabic numerals, or the space character.\n");
    printf("  -a  Replace non-numeric characters with ASCII code written in base 16 notation.\n");
    printf("Example1: bin/main -d Grust_i_labi output\n");
    printf("Example2: bin/main -s Veselie_i_proverki\n");
}

void print_out(const char *filename)
{
    printf("The result is written to the file: %s\n", filename);
}

void handle_validation_error(ValidationStatus status)
{
    switch (status)
    {
    case VALIDATION_INVALID_ARGC:
        printf("Error: Invalid number of arguments\n");
        break;
    case VALIDATION_INVALID_FLAG:
        printf("ERROR: Invalid flag\n");
        break;
    case VALIDATION_INVALID_FILE:
        printf("ERROR: Invalid file name\n");
        break;
    default:
        printf("ERROR: undefined error\n");
        break;
    }
}

int main(int argc, char *argv[])
{
    ValidationStatus status = validate_arguments(argc, argv);
    if (status != VALIDATION_SUCCESS)
    {
        handle_validation_error(status);
        print_usage();
        return 1;
    }

    status = validate_file(argv[2]);
    if (status != VALIDATION_SUCCESS)
    {
        handle_validation_error(status);
        print_usage();
        return 1;
    }

    FILE *input_file = fopen(argv[2], "r");
    if (input_file == NULL)
    {
        perror("Input file opening error");
        return 1;
    }

    FILE *output_file = NULL;
    const char *output_filename = NULL;

    char file_out[256];
    if (argc == 3)
    {
        snprintf(file_out, sizeof(file_out), "out_%s", argv[2]);
        output_filename = file_out;
    }
    else if (argc == 4)
    {
        output_filename = argv[3];
    }

    if (output_filename != NULL)
    {
        output_file = fopen(output_filename, "w");
        if (output_file == NULL)
        {
            perror("Output file opening error");
            fclose(input_file);
            return 1;
        }
    }

    const char *flag_str = argv[1];
    char flag_char = '\0';

    status = validate_flag(flag_str);
    if (status == VALIDATION_SUCCESS)
    {
        flag_char = flag_str[1];
    }
    else
    {
        handle_validation_error(status);
        print_usage();
        fclose(input_file);
        if (output_file)
            fclose(output_file);
        return 1;
    }

    switch (flag_char)
    {
    case 'd':
        flag_d(input_file, output_file);
        break;
    case 'i':
        flag_i(input_file, output_file);
        break;
    case 's':
        flag_s(input_file, output_file);
        break;
    case 'a':
        flag_a(input_file, output_file);
        break;
    default:
        printf("Error: Unknown flag '%c'\n", flag_char);
        print_usage();
        fclose(input_file);
        if (output_file)
            fclose(output_file);
        return 1;
    }

    print_out(output_filename);

    fclose(input_file);
    if (output_file)
        fclose(output_file);

    return 0;
}