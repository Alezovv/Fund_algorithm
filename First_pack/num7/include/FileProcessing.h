#ifndef FILE_PROCESSING_H
#define FILE_PROCESSING_H

#include <stdio.h>

typedef enum
{
    FILE_PROCESSING_SUCCESS = 0,
    FILE_PROCESSING_OPEN_ERROR,
    FILE_PROCESSING_READ_ERROR,
    FILE_PROCESSING_WRITE_ERROR,
    FILE_PROCESSING_MEMORY_ERROR,
    FILE_PROCESSING_INVALID_FORMAT
} FileProcessingStatus;

// Обрабатывает входной файл и записывает результат в выходной
FileProcessingStatus process_files(const char *input_path, const char *output_path);

#endif