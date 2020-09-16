/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vm.h                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/16 22:42:58 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H

# define VM_H

# include "libft.h"
# include "ft_printf.h"
# include <stdbool.h>
# include <fcntl.h>

/*
**	COLORS FOR FT_PRINTF
*/

# define C_RED				"\x1b[31m"
# define C_GREEN			"\x1b[32m"
# define C_YELLOW			"\x1b[33m"
# define C_BLUE				"\x1b[34m"
# define C_MAGENTA			"\x1b[35m"
# define C_CYAN				"\x1b[36m"
# define C_RESET			"\x1b[0m"

/*
** op.h header provided as attachment for Corewar project
*/

# define IND_SIZE			2
# define REG_SIZE			4
# define DIR_SIZE			REG_SIZE
# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3
# define SIZE_REG			1
# define SIZE_IND			2
# define SIZE_SDIR			2
# define SIZE_LDIR			4
# define MAX_ARGS_NUMBER	4
# define MAX_PLAYERS		4
# define MEM_SIZE			4096
# define IDX_MOD			512
# define HEXDUMP_WIDTH		32
# define EXEC_CODE_MAX_SIZE	682
# define CHAMP_MINIMUM_SIZE	2192
# define N_OPCODES			16
# define N_LABEL_CHARS		38
# define REG_NUMBER			16
# define CYCLE_TO_DIE		1536
# define CYCLE_DELTA		50
# define NBR_LIVE			21
# define MAX_CHECKS			10
# define T_REG				1
# define T_DIR				2
# define T_IND				4
# define T_LAB				8
# define PROG_NAME_LENGTH	128
# define COMMENT_LENGTH		2048
# define COREWAR_EXEC_MAGIC	0xea83f3
# define MAGIC_BACKWARDS	0xf383ea00
# define FIRST_ARG			0
# define SECND_ARG			1
# define THIRD_ARG			2
# define SIZE				0
# define VALUE				4

/*
**		ERROR MACROS
*/

# define FEW_ARGS		"usage: ./corewar [-dump N | -n N] ... <champion.cor>\n"
# define INVALID_ARG	"Wrong type of argument provided\n"
# define SAME_N_VALUE	"Error: Multiple -n have same value or value to large\n"
# define MULTIPLE_N		"Error, -n or -dump already provided\n"
# define INVALID_N		"Invalid argument provided to -n\n"
# define INVALID_DUMP	"Invalid argument provided to -dump\n"
# define INV_ARG_N_DUMP	"Argument is not a number\n"
# define TOO_BIG_OR_SML	"File is either too big or small\n"
# define BAD_BINARY		"Binary is not formatted correctly\n"
# define TOO_MANY_CHAMPS	"Too many champs\n"

/*
**	fd				= file descriptor when opening file provided in stdin
**	orig_file		= array of bytes, original raw bytes read from file
**	file_size		= size of bytes of file provided by read()
**	name			= pointer to location in array of bytes where name should be
**	comment			= pointer to location where comment should be
**	exec_size		= pointer to location where exec_size should be
**	real_exec_size	= real size in bytes of the exec_code
**	exec_code		= pointer to location where exec_code should be
**	file_name		= name of file provided
**	id				= id assigned when parsed, possibly reassigned if -n flag
**						provided to it or any other champion
**	n_provided		= if -n flag used, the int value following the -n flag
**	alive			= used to identify if champ is still alive for current
**						corewar CYCLE_TO_DIE cycle
*/

typedef struct		s_champ
{
	int				fd;
	unsigned char	*orig_file;
	int				file_size;
	unsigned char	*name;
	unsigned char	*comment;
	unsigned char	*exec_size;
	int				real_exec_size;
	unsigned char	*exec_code;
	char			*file_name;
	int				id;
	size_t			n_provided;
	bool			alive;
}					t_champ;

/*
**	champs			= array of champs
**	dump			= number of cycles at which game stops and game field is
**					printed to stdout
**	n_flag			= variable used on initialization of champs, not used during
**					battle
**	num_champs		= number of champs
**	field			= array of unsigned char [4096] representing memory from
**					with champs will be loaded and battle
**	num_cursors 	= number of active cursors on the field
**	cycles			= program counter
**	cycles_to_die	= counter, reset to zero at every max_cycles_die, of which
**					all cursors must have reported being alive at least once
**	max_cycles_die	= value representing current max cycles of which a process
**					must report being alive, decreased every num_checks is
**					equal to 10, or when the number of 'lives' that have been
**					reported is >= 21 (NBR_LIVE)
**	num_checks		= counter for number of times max_cycles_die == cycles_to_di
**	num_lives		= total number of 'live' operations that have been done
**					during a max_cycle_die cycle
**	cursor_head		= pointer to first cursor, which is a linked list of cursors
**	wait_cycle_arr	= array of values representing the wait times that each
**					operation costs, placed at the index - 1 for each opcode
**	last_champ_alive= most recent cursors to perform live on a memory cell
**					containing some champion's id. (if no id, oh well)
*/

typedef struct		s_arena
{
	t_champ			**champs;
	int				dump;
	int				n_flag;
	int				num_champs;
	unsigned char	*field;
	int				num_cursors;
	int				cycles;
	int				cycles_to_die;
	int				max_cycle_die;
	int				num_checks;
	int				num_lives;
	struct s_cursor	*cursor_head;
	int				wait_cycle_arr[16];
	int				last_champ_alive;
}					t_arena;

/*
**	id			= unique id
**	carry		= flag changed by some operations
**	opcode		= operation needing to complete
**	last_live	= cycle number in which cursor last performed 'live' operation
**	wait_cycle	= amount of cycles to wait before execution of operatino
**	position	= address in memory
**	jump		= amout of bytes cursor must jump for next operation
**	registry	= array of registries used by cursor
**	next		= link to next cursor
*/
typedef struct		s_cursor
{
	int				id;
	bool			carry;
	int				opcode;
	int				last_live;
	int				wait_cycle;
	int				position;
	int				jump;
	int				registry[16];
	struct s_cursor	*next;
	struct s_cursor	*prev;
}					t_cursor;

typedef struct		s_args
{
	int				value_1;
	int				value_2;
	int				value_3;
	char			size_1;
	char			size_2;
	char			size_3;
}					t_args;

typedef void	(*t_func)
			(t_cursor *, t_arena *arena, t_args *args, int position);

/*
**		print_funcs.c
*/

void				print_champs
			(t_arena *arena);
void				print_winner
			(t_arena *arena);
int					print_error
			(t_arena *arena, char *str);
void				intro_champs
			(t_arena *arena);
int					print_hexdump
			(t_arena *arena, bool execute_anyway);
void				print_arena_and_cursors
			(t_arena *arena);
void				print_cursor
			(t_cursor *cursor);

/*
**		input_validation.c
*/

void				get_champ_file
			(t_arena *arena, t_champ *champ);
void				validate_champs
			(char *input, t_arena *arena);
void				validate_flag
			(char **argv, t_arena *arena, int *argc, int len);
int					grab_n_ids
			(t_champ *n_ids[4], int n_index, t_champ **champs, int num_champs);
void				validate_ids
			(t_arena *arena);

/*
**		initialize_arena.c
*/

void				initialize_arena
			(t_arena *arena);
void				create_cursor
			(t_arena *arena, int i);

/*
**		battle.c
*/

void				battle
			(t_arena *arena, t_func *arrpointer, t_cursor *cursor);

/*
**		operations.c
*/

void				op_live
			(t_cursor *cursor, t_arena *arena, t_args *args, int position);
void				op_ld
			(t_cursor *cursor, t_arena *arena, t_args *args, int position);
void				op_st
			(t_cursor *cursor, t_arena *arena, t_args *args, int position);
void				op_add
			(t_cursor *cursor, t_arena *arena, t_args *args, int position);
void				op_sub
			(t_cursor *cursor, t_arena *arena, t_args *args, int position);
void				op_and
			(t_cursor *cursor, t_arena *arena, t_args *args, int position);
void				op_or
			(t_cursor *cursor, t_arena *arena, t_args *args, int position);
void				op_xor
			(t_cursor *cursor, t_arena *arena, t_args *args, int position);
void				op_zjmp
			(t_cursor *cursor, t_arena *arena, t_args *args, int position);
void				op_ldi
			(t_cursor *cursor, t_arena *arena, t_args *args, int position);
void				op_sti
			(t_cursor *cursor, t_arena *arena, t_args *args, int position);
void				op_fork
			(t_cursor *cursor, t_arena *arena, t_args *args, int position);
void				op_lld
			(t_cursor *cursor, t_arena *arena, t_args *args, int position);
void				op_lldi
			(t_cursor *cursor, t_arena *arena, t_args *args, int position);
void				op_lfork
			(t_cursor *cursor, t_arena *arena, t_args *args, int position);
void				op_aff
			(t_cursor *cursor, t_arena *arena, t_args *args, int position);

/*
**		delete.c
*/

void				cursor_unlink_del
			(t_arena *arena, t_cursor *cursor);
void				free_everything
			(t_arena *arena);

/*
**		get_arguments.c
*/

void				populate_arguments
			(unsigned char *field, int pos, t_args *args, bool dir_is_two);
int					get_arg_size
			(char encode_byte, int arg_idx, bool dir_is_two);
int					check_register_values
			(t_args *args);

/*
**		operation_aux.c
*/

int					switch_endianness
			(int n, size_t size);
int					ustr_to_int
			(unsigned char *field, int position, int size);
void				int_to_ustr
			(int value, unsigned char *field, int position, int size);

#endif
