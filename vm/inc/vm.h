/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vm.h                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/03 17:36:28 by macbook       ########   odam.nl         */
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

typedef struct					s_champ
{
	int							fd;
	unsigned char				*orig_file;
	int							file_size;
	unsigned char				*name;
	unsigned char				*comment;
	unsigned char				*exec_size;
	unsigned char				*exec_code;
	char						*file_name;
	int							id;
}								t_champ;

typedef struct					s_arena
{
	struct s_champ				**champs;
	int							num_champs;
}								t_arena;

/*
**		print_funcs.c
*/

void		print_champs(t_arena *arena);


#endif
