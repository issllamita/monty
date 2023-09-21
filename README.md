# C - Stacks, Queues - LIFO, FIFO

## Introducion :snake:

This is a Monty Bytecodes Interpreter wirtten in the C language and is compliant with `ISO90`, `ISO99`, & `ISO11`. This interpreter is designed to read Mont

y bytecodes files with any extension (though .m is recommended) and execute the contained opcodes.

## Key Features:

1. Stack (LIFO) and Queue (FIFO) Modes

The interpreter supports both stack and queue execution modes, allowing you to switch between them as needed within your script.

2. Opcode Execution

Monty programs consist of a series of opcodes, each representing a specific operation. These opcodes control the program's flow and perform various tasks, s

uch as arithmetic operations, conditional branching, and input/output operations.

## The monty program:

- Usage: **monty file**

	* where **file** is the path to the file containing Monty byte code

- If the user does not give any file or more than one argument to your program, print the error message **USAGE: monty file**, followed by a new line, and exit with the status **EXIT_FAILURE**

- If, for any reason, it’s not possible to open the file, print the error message **Error: Can't open file <file>**, followed by a new line, and exit with the status **EXIT_FAILURE**

	* where <file> is the name of the file

- If the file contains an invalid instruction, print the error message L<line_number>: unknown instruction <opcode>, followed by a new line, and exit with the status **EXIT_FAILURE**

	* where is the line number where the instruction appears.
	* Line numbers always start at 1

- The monty program runs the bytecodes line by line and stop if either:

	* it executed properly every line of the file
	* it finds an error in the file
	* an error occured

- If you can’t malloc anymore, print the error message Error: malloc failed, followed by a new line, and exit with status **EXIT_FAILURE**.
You have to use malloc and free and are not allowed to use any other function from man malloc (realloc, calloc, …)

## AUTHORS :black_nib:

* **Mrifag Islam** <mrifagislam@gmail.com>
* **leissini** <layssini15@gmail.com>
