#include "../include/FileProcessing.h"
#include "../include/Conversion.h"
#include "../include/Utils.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NUMBER_LENGTH 256

FileProcessingStatus process_files(const char *input_path, const char *output_path)
{
    if (input_path == NULL || output_path == NULL)
    {
        return FILE_PROCESSING_INVALID_FORMAT;
    }

    FILE *input_file = fopen(input_path, "r");
    if (input_file == NULL)
    {
        return FILE_PROCESSING_OPEN_ERROR;
    }

    // Проверка на пустой файл
    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    if (file_size == 0)
    {
        fclose(input_file);
        return FILE_PROCESSING_INVALID_FORMAT;
    }
    fseek(input_file, 0, SEEK_SET);

    FILE *output_file = fopen(output_path, "w");
    if (output_file == NULL)
    {
        fclose(input_file);
        return FILE_PROCESSING_OPEN_ERROR;
    }

    char buffer[MAX_NUMBER_LENGTH];
    int buffer_index = 0;
    int c;
    int has_numbers = 0;

    while ((c = fgetc(input_file)) != EOF)
    {
        if (Is_Sign(c))
        {
            // Если в буфере есть число - обрабатываем его
            if (buffer_index > 0)
            {
                buffer[buffer_index] = '\0';
                has_numbers = 1;

                // Обрабатываем число
                char number_copy[MAX_NUMBER_LENGTH];
                strcpy(number_copy, buffer);
                remove_leading_zeros(number_copy);

                int min_base;
                long long decimal_value;

                ConversionStatus base_status = find_min_base(number_copy, &min_base);
                ConversionStatus convert_status = convert_to_decimal(number_copy, min_base, &decimal_value);

                if (base_status == CONVERSION_SUCCESS && convert_status == CONVERSION_SUCCESS)
                {
                    fprintf(output_file, "%s %d %lld\n", number_copy, min_base, decimal_value);
                }
                else
                {
                    fprintf(output_file, "%s invalid_number\n", number_copy);
                }

                buffer_index = 0;
            }
        }
        else
        {
            // Добавляем символ в буфер, если есть место
            if (buffer_index < MAX_NUMBER_LENGTH - 1)
            {
                // Приводим к верхнему регистру для единообразия
                buffer[buffer_index++] = toupper(c);
            }
        }
    }

    // Обрабатываем последнее число в файле, если оно есть
    if (buffer_index > 0)
    {
        buffer[buffer_index] = '\0';
        has_numbers = 1;

        char number_copy[MAX_NUMBER_LENGTH];
        strcpy(number_copy, buffer);
        remove_leading_zeros(number_copy);

        int min_base;
        long long decimal_value;

        ConversionStatus base_status = find_min_base(number_copy, &min_base);
        ConversionStatus convert_status = convert_to_decimal(number_copy, min_base, &decimal_value);

        if (base_status == CONVERSION_SUCCESS && convert_status == CONVERSION_SUCCESS)
        {
            fprintf(output_file, "%s %d %lld\n", number_copy, min_base, decimal_value);
        }
        else
        {
            fprintf(output_file, "%s invalid_number\n", number_copy);
        }
    }

    fclose(input_file);
    fclose(output_file);

    if (!has_numbers)
    {
        return FILE_PROCESSING_INVALID_FORMAT;
    }

    return FILE_PROCESSING_SUCCESS;
}