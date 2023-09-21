#include "monty.h"
#include <string.h>

/**
 * init_stack - Initializes a stack_t stack with beginning
 *              stack and ending queue nodes.
 * @stack: A pointer to an unitialized stack_t stack.
 * Return: If an error occurs - EXIT_FAILURE.
 *         Otherwise - EXIT_SUCCESS.
 */
int init_stack(stack_t **stack)
{
	stack_t *s;

	s = malloc(sizeof(stack_t));
	if (s == NULL)
		return (malloc_err());

	s->n = STACK;
	s->prev = NULL;
	s->next = NULL;

	*stack = s;

	return (EXIT_SUCCESS);
}

/**
 * check_mode - Checks if a stack_t linked list is in stack or queue mode.
 * @stack: A pointer to the top (stack) or bottom (queue)
 *         of a stack_t linked list.
 * Return: If the stack_t is in stack mode - STACK (0).
 *         If the stack_t is in queue mode - QUEUE (1).
 *         Otherwise - 2.
 */
int check_mode(stack_t *stack)
{
	if (stack->n == STACK)
		return (STACK);
	else if (stack->n == QUEUE)
		return (QUEUE);
	return (2);
}

/**
 * set_tok_err - Sets last element of op_toks to be an error code.
 * @err_code: Integer to store as a string in op_toks.
 */
void set_tok_err(int err_code)
{
	int toks_len = 0, i = 0;
	char *exit_str = NULL;
	char **new_toks = NULL;

	toks_len = tok_arr_len();
	new_toks = malloc(sizeof(char *) * (toks_len + 2));
	if (!op_toks)
	{
		malloc_err();
		return;
	}
	while (i < toks_len)
	{
		new_toks[i] = op_toks[i];
		i++;
	}
	exit_str = catch_int(err_code);
	if (!exit_str)
	{
		free(new_toks);
		malloc_err();
		return;
	}
	new_toks[i++] = exit_str;
	new_toks[i] = NULL;
	free(op_toks);
	op_toks = new_toks;
}

/**
 * free_stack - Frees a stack_t stack.
 * @stack: A pointer to the top (stack) or
 *         bottom (queue) of a stack_t.
 */
void free_stack(stack_t **stack)
{
	stack_t *tmp = *stack;

	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
}

