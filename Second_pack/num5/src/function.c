#include "../include/function.h"

static void justify_line(const char *line, char *out)
{
    char words[LINE_WIDTH][LINE_WIDTH];
    int word_lengths[LINE_WIDTH];
    int n_words = 0;

    int i = 0, j = 0;
    int len = strlen(line);

    while (i < len)
    {
        while (i < len && isspace((unsigned char)line[i]))
            i++;
        if (i >= len)
            break;

        j = 0;
        while (i < len && !isspace((unsigned char)line[i]))
            words[n_words][j++] = line[i++];

        words[n_words][j] = '\0';
        word_lengths[n_words] = j;
        n_words++;
    }

    int total_chars = 0;
    for (i = 0; i < n_words; i++)
        total_chars += word_lengths[i];

    int total_spaces = LINE_WIDTH - total_chars;
    int space_between = n_words > 1 ? total_spaces / (n_words - 1) : total_spaces;
    int extra_spaces = n_words > 1 ? total_spaces % (n_words - 1) : 0;

    out[0] = '\0';
    for (i = 0; i < n_words; i++)
    {
        strcat(out, words[i]);
        if (i < n_words - 1)
        {
            int s = space_between + (extra_spaces-- > 0 ? 1 : 0);
            for (j = 0; j < s; j++)
                strcat(out, " ");
        }
    }
}

// Основная функция для форматирования текста
static void process_line(FILE *fout, char *buffer)
{
    size_t len = strlen(buffer);
    size_t start = 0;

    while (len - start > LINE_WIDTH)
    {
        size_t end = start + LINE_WIDTH;

        while (end > start && !isspace((unsigned char)buffer[end - 1]))
            end--;

        if (end == start)
            end = start + LINE_WIDTH;

        char line[LINE_WIDTH + 1];
        strncpy(line, buffer + start, end - start);
        line[end - start] = '\0';

        char justified[LINE_WIDTH + 1];
        justify_line(line, justified);

        fprintf(fout, "%s\n", justified);
        start = end;
        while (isspace((unsigned char)buffer[start]))
            start++;
    }

    if (start < len)
        fprintf(fout, "%s\n", buffer + start);
}