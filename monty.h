#ifndef __MONTY_H__
#define __MONTY_H__

#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define STACK 0
#define QUEUE 1
#define DELIMS " \n\t\a\b"

extern char **op_toks;

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

extern char **op_toks;

/*.................... exec_monty.c...................... */

int exec_monty(FILE *script_fd);
void free_toks(void);
unsigned int tok_arr_len(void);
int is_empty_line(char *line, char *delims);
char **strtow(char *str, char *delims);

/*...................... prim_inter_f1.c................. */

int init_stack(stack_t **stack);
int check_mode(stack_t *stack);
void setop_tok_err(int err_code);
void free_stack(stack_t **stack);
char *get_int(int n);

/*...................... op_code1.c...................... */

void _push(stack_t **stack, unsigned int line_number);
void _pop(stack_t **stack, unsigned int line_number);
void _pall(stack_t **stack, unsigned int line_number);
void _swap(stack_t **stack, unsigned int line_number);
void _pint(stack_t **stack, unsigned int line_number);

/*........................ op_code2.c.................... */

void _add(stack_t **stack, unsigned int line_number);
void _sub(stack_t **stack, unsigned int line_number);
void _mul(stack_t **stack, unsigned int line_number);
void _div(stack_t **stack, unsigned int line_number);
void _mod(stack_t **stack, unsigned int line_number);

/*........................ op_code3.c.................... */

void _pchar(stack_t **stack, unsigned int line_number);
void _pstr(stack_t **stack, unsigned int line_number);
void _nop(stack_t **stack, unsigned int line_number);

/*......................... op_code4.c................... */

void _rotl(stack_t **stack, unsigned int line_number);
void _rotr(stack_t **stack, unsigned int line_number);
void _stack(stack_t **stack, unsigned int line_number);
void _queue(stack_t **stack, unsigned int line_number);

/*......................... op_err1.c.................... */

int usg_err(void);
int noint_err(unsigned int line_number);
int malc_err(void);
int fl_open_err(char *filename);
int unkn_opc_err(char *opcode, unsigned int line_number);

/*......................... op_err2.c.................... */

int pop_err(unsigned int line_number);
int pint_err(unsigned int line_number);
int div_err(unsigned int line_number);
int pchar_err(unsigned int line_number, char *message);
int brief_stack_err(unsigned int line_number, char *op);

#endif /* __MONTY_H__ */
