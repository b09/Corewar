/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vm.h                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/06 19:25:46 by macbook       ########   odam.nl         */
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

# define C_RED					"\x1b[31m"
# define C_GREEN				"\x1b[32m"
# define C_YELLOW				"\x1b[33m"
# define C_BLUE					"\x1b[34m"
# define C_MAGENTA				"\x1b[35m"
# define C_CYAN					"\x1b[36m"
# define C_RESET				"\x1b[0m"

/*
** op.h header provided as attachment for Corewar project
*/

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE
# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3
# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				4096
# define IDX_MOD				512
# define HEXDUMP_WIDTH			32
# define EXEC_CODE_MAX_SIZE		682
# define CHAMP_MINIMUM_SIZE		2192
# define N_OPCODES				16
# define N_LABEL_CHARS			38
# define REG_NUMBER				16
# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10
# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8
# define PROG_NAME_LENGTH		128
# define COMMENT_LENGTH			2048
# define COREWAR_EXEC_MAGIC		0xea83f3
# define MAGIC_BACKWARDS		0xf383ea00

/*
**		ERROR MACROS
*/

# define FEW_ARGS				"Too few arguments provided\n"
# define INVALID_ARG			"Wrong type of argument provided\n"
# define SAME_N_VALUE			"Error: Multiple -n have same value or value to\
								large\n"
# define MULTIPLE_N				"Error, -n or -dump already provided\n"
# define INVALID_N				"Invalid argument provided to -n\n"
# define INVALID_DUMP			"Invalid argument provided to -dump\n"
# define INV_ARG_N_DUMP			"Argument is not a number\n"
# define TOO_BIG_OR_SML			"File is either too big or small\n"
# define BAD_BINARY				"Binary is not formatted correctly\n"
# define TOO_MANY_CHAMPS		"Too many champs\n"

typedef struct					s_champ
{
	int							fd;
	unsigned char				*orig_file;
	int							file_size;
	unsigned char				*name;
	unsigned char				*comment;
	unsigned char				*exec_size;
	int							real_exec_size;
	unsigned char				*exec_code;
	char						*file_name;
	int							id;
	size_t						n_provided;
}								t_champ;

typedef struct					s_arena
{
	t_champ						**champs;
	int							dump;
	int							n_flag;
	int							num_champs;
	unsigned char				*field;
	int							num_cursors;
	int							cycles;
	int							cycles_to_die;
	struct s_cursor				*cursor_head;
	int							wait_cycle_arr[16];
	int							latest_champ_alive;
}								t_arena;

typedef struct					s_cursor
{
	int							id;
	bool						carry;
	int							opcode;
	int							last_live;
	int							wait_cycle;
	int							position;
	int							jump;
	int							registry[16];
	struct s_cursor				*next;
}								t_cursor;

typedef void			(*t_func)(t_cursor *, t_arena *arena);

/*
**		print_funcs.c
*/

void		print_champs(t_arena *arena);
int			print_error(char *str);
void		intro_champs(t_arena *arena);
void		print_hexdump(t_arena *arena);
void		print_arena_and_cursors(t_arena *arena);




/*
**		input_validation.c
*/

void		get_champ_file(t_champ *champ);
void		validate_champs(char *input, t_arena *arena);
void		validate_flag(char **argv, t_arena *arena, int *argc, int len);
void		grab_n_ids(t_champ *n_ids[4], int n_index, t_champ **champs,\
				int num_champs);
void		validate_ids(t_arena *arena);

/*
**		initialize_arena.c
*/

void		initialize_arena(t_arena *arena);
void		battle(t_arena *arena);

/*
**		operations.c
*/

void		op_live(t_cursor *cursor, t_arena *arena);
void		op_ld(t_cursor *cursor, t_arena *arena);
void		op_st(t_cursor *cursor, t_arena *arena);
void		op_add(t_cursor *cursor, t_arena *arena);
void		op_sub(t_cursor *cursor, t_arena *arena);
void		op_and(t_cursor *cursor, t_arena *arena);
void		op_or(t_cursor *cursor, t_arena *arena);
void		op_xor(t_cursor *cursor, t_arena *arena);
void		op_zjmp(t_cursor *cursor, t_arena *arena);
void		op_ldi(t_cursor *cursor, t_arena *arena);
void		op_sti(t_cursor *cursor, t_arena *arena);
void		op_fork(t_cursor *cursor, t_arena *arena);
void		op_lld(t_cursor *cursor, t_arena *arena);
void		op_lldi(t_cursor *cursor, t_arena *arena);
void		op_lfork(t_cursor *cursor, t_arena *arena);
void		op_aff(t_cursor *cursor, t_arena *arena);


#endif
