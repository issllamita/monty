#include "monty.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char **op_toks = NULL;

/**
 * main - entry point for Monty Interpreter
 * @argc: the count of arguments passed to the program
 * @argv: pointer to an array of char pointers to arguments
 * Return: (EXIT_SUCCESS) on success (EXIT_FAILURE) on error
 */
int main(int argc, char **argv)
{
	FILE *op_cipher = NULL;
	int exit_code = EXIT_SUCCESS;

	if (argc != 2)
		return (usg_err());
	op_cipher = fopen(argv[1], "r");
	if (op_cipher == NULL)
		return (fl_open_err(argv[1]));
	exit_code = exec_monty(op_cipher);
	fclose(op_cipher);
	return (exit_code);
}
