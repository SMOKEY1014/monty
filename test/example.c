#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack_s
{
    int n;
    struct stack_s *prev;
    struct stack_s *next;
} stack_t;

typedef void (*instruction_func)(stack_t **stack, unsigned int line_number);

typedef struct instruction_s
{
    char *opcode;
    instruction_func f;
} instruction_t;

void push(stack_t **stack, int value)
{
    stack_t *new_node = malloc(sizeof(stack_t));
    if (new_node == NULL)
    {
        fprintf(stderr, "Error: Unable to allocate memory for stack node\n");
        exit(EXIT_FAILURE);
    }

    new_node->n = value;
    new_node->prev = NULL;
    new_node->next = *stack;

    if (*stack != NULL)
    {
        (*stack)->prev = new_node;
    }

    *stack = new_node;
}

void pall(stack_t **stack, unsigned int line_number)
{
    stack_t *current = *stack;

    printf("pall at line %u: ", line_number);
    while (current != NULL)
    {
        printf("%d ", current->n);
        current = current->next;
    }
    printf("\n");
}

void executeInstruction(instruction_t *instruction, stack_t **stack, unsigned int line_number)
{
    if (instruction->f != NULL)
    {
        instruction->f(stack, line_number);
    }
    else
    {
        fprintf(stderr, "Error: Unknown opcode '%s' at line %u\n", instruction->opcode, line_number);
        exit(EXIT_FAILURE);
    }
}

void readPushValueAndExecute(const char *filename, stack_t **stack)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    char *token;
    unsigned int line_number = 0;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        line_number++;
        token = strtok(line, " $");

        while (token != NULL)
        {
            instruction_t instruction;
            instruction.opcode = token;
            token = strtok(NULL, " $\n");

            if (strcmp(instruction.opcode, "push") == 0)
            {
                instruction.f = (instruction_func)push;
            }
            else if (strcmp(instruction.opcode, "pall") == 0)
            {
                instruction.f = (instruction_func)pall;
            }
            else
            {
                // Handle other opcodes as needed
                fprintf(stderr, "Error: Unknown opcode '%s' at line %u\n", instruction.opcode, line_number);
                exit(EXIT_FAILURE);
            }

            executeInstruction(&instruction, stack, line_number);

            token = strtok(NULL, " $");
        }
    }

    fclose(file);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    stack_t *stack = NULL;
    readPushValueAndExecute(filename, &stack);

    // Now the stack should contain the values from the instructions

    // Free allocated memory for the stack (if needed)
    // Note: You may need a separate function to free the entire stack

    return EXIT_SUCCESS;
}

