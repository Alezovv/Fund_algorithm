#include "../include/flags.h"

void flag_d(FILE *in_file, FILE *out_file)
{
    int c;

    while ((c = fgetc(in_file)) != EOF)
    {
        if (!isdigit(c))
            fputc(c, out_file);
    }
    fflush(out_file);
}

void flag_i(FILE *in_file, FILE *out_file)
{
    int c;
    int count = 0;
    int is_new_line = 1;

    while ((c = fgetc(in_file)) != EOF)
    {
        if (c == '\n')
        {
            fprintf(out_file, "%d\n", count);
            count = 0;
            is_new_line = 1;
        }
        else
        {
            if (isalpha(c))
                count++;

            is_new_line = 0;
        }
    }
    if (!is_new_line)
        fprintf(out_file, "%d\n", count);

    fflush(out_file);
}

void flag_s(FILE *in_file, FILE *out_file)
{
    int c;
    int count = 0;
    int is_new_line = 1;

    while ((c = fgetc(in_file)) != EOF)
    {
        if (c == '\n')
        {
            fprintf(out_file, "%d\n", count);
            count = 0;
            is_new_line = 1;
        }
        else
        {
            if (!isalpha(c) && !isdigit(c) && c != ' ')
                count++;

            is_new_line = 0;
        }
    }

    if (!is_new_line)
        fprintf(out_file, "%d\n", count);

    fflush(out_file);
}

void flag_a(FILE *in_file, FILE *out_file)
{
    int c;

    while ((c = fgetc(in_file)) != EOF)
    {
        if (isdigit(c))
            fputc(c, out_file);
        else
            fprintf(out_file, "%02X", (unsigned char)c);
    }

    fflush(out_file);
}