#include "monty.h"
#include <string.h>

/**
 * exec_monty - Primary function to execute a Monty bytecodes script.
 * @op_cipher: File descriptor for an open Monty bytecodes script.
 *
 * Return: EXIT_SUCCESS on success, respective error code on failure.
 */
int exec_monty(FILE *op_cipher)
{
	stack_t *stack = NULL;
	char *line = NULL;
	size_t len = 0, exit_status = EXIT_SUCCESS;
	unsigned int line_number = 0, prev_tok_len = 0;
	void (*op_func)(stack_t**, unsigned int);

	if (init_stack(&stack) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	while (getline(&line, &len, script_fd) != -1)
	{
		line_number++;
		op_toks = sepstr(line, DELIMS);
		if (op_toks == NULL)
		{
			if (empty_line(line, DELIMS))
				continue;
			free_stack(&stack);
			return (malloc_err());
		}
		else if (op_toks[0][0] == '#')
		{
			free_toks();
			continue;
		}
		op_func = get_op_func(op_toks[0]);
		if (op_func == NULL)
		{
			free_stack(&stack);
			exit_status = unknown_op_err(op_toks[0], line_number);
			free_toks();
			break;
		}
		prev_tok_len = tok_arr_len();
		op_func(&stack, line_number);
		if (token_arr_len() != prev_tok_len)
		{
			if (op_toks && op_toks[prev_tok_len])
				exit_status = atoi(op_toks[prev_tok_len]);
			else
				exit_status = EXIT_FAILURE;
			free_toks();
			break;
		}
		free_toks();
	}
	free_stack(&stack);

	if (line && *line == 0)
	{
		free(line);
		return (malloc_err());
	}

	free(line);
	return (exit_status);
}

/**
 * tok_arr_len - Gets the length of current op_toks.
 * Return: Length of current op_toks (as int).
 */
unsigned int tok_arr_len(void)
{
	unsigned int toks_len = 0;

	while (op_toks[toks_len])
		toks_len++;
	return (toks_len);
}

/**
 * empty_line - Checks if a line read from getline only contains delimiters.
 * @line: A pointer to the line.
 * @delims: A string of delimiter characters.
 * Return: If the line only contains delimiters - 1.
 *         Otherwise - 0.
 */
int empty_line(char *line, char *delims)
{
	int i, j;

	for (i = 0; line[i]; i++)
	{
		for (j = 0; delims[j]; j++)
		{
			if (line[i] == delims[j])
				break;
		}
		if (delims[j] == '\0')
			return (0);
	}

	return (1);
}

/**
 * free_toks - Frees the global op_toks array of strings.
 */
void free_toks(void)
{
	size_t i = 0;

	if (op_toks == NULL)
		return;

	for (i = 0; op_toks[i]; i++)
		free(op_toks[i]);

	free(op_toks);
}
