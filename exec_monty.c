#include "monty.h"
#include <string.h>

int exec_monty(FILE *op_cipher);
unsigned int tok_arr_len(void);
int empty_line(char *line, char *delims);
void (*catch_opc_fn(char *opcode))(stack_t**, unsigned int);
void free_toks(void);

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

	while (getline(&line, &len, op_cipher) != -1)
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
		op_func = catch_opc_fn(op_toks[0]);
		if (op_func == NULL)
		{
			free_stack(&stack);
			exit_status = unknown_opc_err(op_toks[0], line_number);
			free_toks();
			break;
		}
		prev_tok_len = tok_arr_len();
		op_func(&stack, line_number);
		if (tok_arr_len() != prev_tok_len)
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
 * catch_opc_fn - Matches an opcode with its corresponding function.
 * @opcode: The opcode to match.
 *
 * Return: A pointer to the corresponding function.
 */
void (*catch_opc_fn(char *opcode))(stack_t**, unsigned int)
{
	instruction_t op_funcs[] = {
		{"push", _push},
		{"pall", _pall},
		{"pint", _pint},
		{"pop", _pop},
		{"swap", _swap},
		{"add", _add},
		{"nop", _nop},
		{"sub", _sub},
		{"div", _div},
		{"mul", _mul},
		{"mod", _mod},
		{"pchar", _pchar},
		{"pstr", _pstr},
		{"rotl", _rotl},
		{"rotr", _rotr},
		{"stack", _stack},
		{"queue", _queue},
		{NULL, NULL}
	};
	int i;

	for (i = 0; op_funcs[i].opcode; i++)
	{
		if (strcmp(opcode, op_funcs[i].opcode) == 0)
			return (op_funcs[i].f);
	}

	return (NULL);
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
