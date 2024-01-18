#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct
{
    int line_num;
    char *command;
    char *number;
} LineInfo;

LineInfo processFile(const char *filename)
{
    LineInfo result = {0, NULL, NULL};

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return result;
    }

    char line[256]; // Adjust the size based on your needs

    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Tokenize the line using '$' as a delimiter
        char *token = strtok(line, " $");
        result.line_num += 1;

        if (token != NULL)
        {
            // First token (push or pall)
            result.command = strdup(token);

            // Second token (number or NULL)
            token = strtok(NULL, "$");
            result.number = (token != NULL) ? strdup(token) : NULL;

            // Process the strings (you can replace the print statements with your logic)
            if (result.number != NULL)
            {
                printf("%d Command: %s, Number: %s\n", result.line_num, result.command, result.number);
            }
            else
            {
                printf("%d Command: %s, Number: NULL\n", result.line_num, result.command);
            }

            fclose(file);
            return result;
        }
    }

    fclose(file);
    return result;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    LineInfo result = processFile(filename);

    // Now you can use the result structure to pass arguments to push and pall functions
    // For example:
    // push(&stack, result.line_num, result);
    // pall(&stack, result.line_num, result);

    // Free the allocated memory
    free(result.command);
    free(result.number);

    return EXIT_SUCCESS;
}
