#ifndef VALIDATION_H
#define VALIDATION_H

typedef enum
{
    VALIDATION_SUCCESS = 0,
    VALIDATION_INVALID_ARGUMENTS,
    VALIDATION_FILE_NOT_FOUND,
    VALIDATION_WRONG_NUMBER,
    VALIDATION_EMPTY_FILE
} ValidationStatus;

ValidationStatus Validate_Argument(int argc, char *argv[]);
ValidationStatus Validate_File(const char *path);
ValidationStatus Validate_Number(char c);

#endif