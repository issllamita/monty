#include "monty.h"

/**
 * pop_err - Prints pop error messages for empty stacks.
 * @line_number: Line number in script where error occured.
 * Return: (EXIT_FAILURE) always.
 */
int pop_err(unsigned int line_number)
{
	fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
	return (EXIT_FAILURE);
}

/**
 * pint_err - Prints pint error messages for empty stacks.
 * @line_number: Line number in Monty bytecodes file where error occurred.
 *
 * Return: (EXIT_FAILURE) always.
 */
int pint_err(unsigned int line_number)
{
	fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
	return (EXIT_FAILURE);
}

/**
 * div_err - Prints division error messages for division by 0.
 * @line_number: Line number in Monty bytecodes file where error occurred.
 * Return: (EXIT_FAILURE) always.
 */
int div_err(unsigned int line_number)
{
	fprintf(stderr, "L%u: division by zero\n", line_number);
	return (EXIT_FAILURE);
}

/**
 * pchar_err - Prints pchar error messages for empty stacks
 *               empty stacks and non-character values.
 * @line_number: Line number in Monty bytecodes file where error occurred.
 * @flag: The corresponding error message to print.
 * Return: (EXIT_FAILURE) always.
 */
int pchar_err(unsigned int line_number, char *flag)
{
	fprintf(stderr, "L%u: can't pchar, %s\n", line_number, flag);
	return (EXIT_FAILURE);
}

/**
 * brief_stack_err - Prints monty math function error messages
 *                     for stacks/queues smaller than two nodes.
 * @line_number: Line number in Monty bytecodes file where error occurred.
 * @opr: Operation where the error occurred.
 *
 * Return: (EXIT_FAILURE) always.
 */
int brief_stack_err(unsigned int line_number, char *opr)
{
	fprintf(stderr, "L%u: can't %s, stack too short\n", line_number, opr);
	return (EXIT_FAILURE);
}
