#include "monty.h"


/**
 * set_op_tok_error - Setting the last element of op_toks to be an error code.
 * @error_code: Integer to store as a string.
 */
void set_op_tok_err(int error_code)
{
    char *exit_str = NULL;
    int toks_len = 0, b= 0;
    char **new_toks = NULL;


    toks_len = token_arr_len();
    new_toks = malloc(sizeof(char *) * (toks_len + 2));
    if (!op_toks)
    {
        malloc_err();
        return;
    }
    while (b< toks_len)
    {
        new_toks[b] = op_toks[b];
        b++;
    }
    exit_str = get_num(error_code);
    if (!exit_str)
    {
        free(new_toks);
        malloc_err();
        return;
    }
    new_toks[b++] = exit_str;
    new_toks[b] = NULL;
    free(op_toks);
    op_toks = new_toks;
}