#include "../include/Validation.h"
#include "../include/Utils.h"
#include "../include/FileProcessing.h"
#include <stdio.h>

void print_usage()
{
    printf("Usage: <program> <input_file> <output_file>\n");
    printf("Example: main input.txt output.txt\n");
}

void handle_validation_error(ValidationStatus status)
{
    switch (status)
    {
    case VALIDATION_INVALID_ARGUMENTS:
        printf("Error: Invalid number of arguments\n");
        break;
    case VALIDATION_FILE_NOT_FOUND:
        printf("Error: File not found\n");
        break;
    case VALIDATION_WRONG_NUMBER:
        printf("Invalid number found\n");
        break;
    case VALIDATION_EMPTY_FILE:
        printf("Given an empty file\n");
        break;
    default:
        printf("Error: undefined error\n");
    }
}

void handle_file_processing_error(FileProcessingStatus status)
{
    switch (status)
    {
    case FILE_PROCESSING_OPEN_ERROR:
        printf("Error: Cannot open file\n");
        break;
    case FILE_PROCESSING_READ_ERROR:
        printf("Error: Cannot read from file\n");
        break;
    case FILE_PROCESSING_WRITE_ERROR:
        printf("Error: Cannot write to file\n");
        break;
    case FILE_PROCESSING_MEMORY_ERROR:
        printf("Error: Memory allocation failed\n");
        break;
    case FILE_PROCESSING_INVALID_FORMAT:
        printf("Error: Invalid file format or empty file\n");
        break;
    default:
        printf("Error: Unknown file processing error\n");
    }
}

int main(int argc, char *argv[])
{
    ValidationStatus status = Validate_Argument(argc, argv);
    if (status != VALIDATION_SUCCESS)
    {
        handle_validation_error(status);
        print_usage();
        return 1;
    }

    const char *input_path = argv[1];
    const char *output_path = argv[2];

    FileProcessingStatus process_status = process_files(input_path, output_path);
    if (process_status != FILE_PROCESSING_SUCCESS)
    {
        handle_file_processing_error(process_status);
        return 1;
    }

    printf("File processed successfully. Results written to %s\n", output_path);
    return 0;
}