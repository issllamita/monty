#include "monty.h"

/**
 * _push - Pushes a value to a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: current working line number of a Monty bytecodes file.
 */
void _push(stack_t **stack, unsigned int line_number)
{
	stack_t *temp, *new;
	int j;

	new = malloc(sizeof(stack_t));
	if (new == NULL)
	{
		set_tok_err(malloc_err());
		return;
	}

	if (op_toks[1] == NULL)
	{
		set_tok_err(noint_err(line_number));
		return;
	}

	for (j = 0; op_toks[1][j]; j++)
	{
		if (op_toks[1][j] == '-' && j == 0)
			continue;
		if (op_toks[1][j] < '0' || op_toks[1][j] > '9')
		{
			set_tok_err(noint_err(line_number));
			return;
		}
	}
	new->n = atoi(op_toks[1]);

	if (check_mode(*stack) == STACK)
	{
		temp = (*stack)->next;
		new->prev = *stack;
		new->next = temp;
		if (temp)
			temp->prev = new;
		(*stack)->next = new;
	}
	else
	{
		temp = *stack;
		while (temp->next)
			temp = temp->next;
		new->prev = temp;
		new->next = NULL;
		temp->next = new;
	}
}

/**
 * _pop - Removes the top value element of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: current working line number of a Monty bytecodes file.
 */
void _pop(stack_t **stack, unsigned int line_number)
{
	stack_t *next = NULL;

	if ((*stack)->next == NULL)
	{
		set_tok_err(pop_err(line_number));
		return;
	}

	next = (*stack)->next->next;
	free((*stack)->next);
	if (next)
		next->prev = *stack;
	(*stack)->next = next;
}

/**
 * _pall - Prints the values of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: current working line number of a Monty bytecodes file.
 */
void _pall(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = (*stack)->next;

	while (temp)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}
	(void)line_number;
}

/**
 * _swap - Swaps the top two value elements of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: current working line number of a Monty bytecodes file.
 */
void _swap(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if ((*stack)->next == NULL || (*stack)->next->next == NULL)
	{
		set_tok_err(brief_stack_err(line_number, "swap"));
		return;
	}

	temp = (*stack)->next->next;
	(*stack)->next->next = temp->next;
	(*stack)->next->prev = temp;
	if (temp->next)
		temp->next->prev = (*stack)->next;
	temp->next = (*stack)->next;
	temp->prev = *stack;
	(*stack)->next = temp;
}

/**
 * _pint - Prints the top value of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 */
void _pint(stack_t **stack, unsigned int line_number)
{
	if ((*stack)->next == NULL)
	{
		set_tok_err(pint_err(line_number));
		return;
	}

	printf("%d\n", (*stack)->next->n);
}
