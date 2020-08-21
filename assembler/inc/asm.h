/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/08/21 12:59:08 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H

# define ASM_H

# include "libft.h"
# include "ft_printf.h"
# include <fcntl.h> //for open
# include <stdbool.h>


# define C_RED		"\x1b[31m"
# define C_GREEN	"\x1b[32m"
# define C_YELLOW	"\x1b[33m"
# define C_BLUE		"\x1b[34m"
# define C_MAGENTA	"\x1b[35m"
# define C_CYAN		"\x1b[36m"
# define C_RESET	"\x1b[0m"

/*
** op.h header provided as attachment for Corewar project
*/

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
#define MEM_SIZE				4096
#define IDX_MOD					512
#define CHAMP_MAX_SIZE			768

#define COMMENT_CHAR			'#'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','
#define REGISTRY_CHAR			'r'
#define COMMAND_CHAR			'.'
#define ENDLINE_CHAR			'\n'
#define STRING_CHAR				'"'

#define N_OPCODES				16
#define N_LABEL_CHARS			37      // needs a recount
#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

#define REG_NUMBER				16

#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10

/*
**  TOKENS:
**	1-20 intructions
**	20-29 plain text
**	30-39 non action signifiers
**	40-49 arguments
**	50-59 syntax character
**
**		*20 COMMENT
**		21 STRING
**
**		*30 COMMAND
**		31 LABEL
**
**		*40 DIRECT
**		41 REGISTRY
**		42 INDIRECT_LABEL
**		43 INDIRECT
**
**		50 SEPARATOR
**		51 ENDLINE
**
*/

#define COMMENT_TKN			20
#define STRING_TKN			21
#define COMMAND_TKN			30
#define LABEL_TKN			31
#define DIRECT_TKN			40
#define REGISTRY_TKN		41
#define INDIRECT_LABEL_TKN	42
#define INDIRECT_TKN		43
#define SEPARATOR_TKN		50
#define ENDLINE_TKN			51

/*
**
*/

typedef char	t_arg_type;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8

/*
**
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct		header_s
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}					header_t;

/*
**  Bla
*/

typedef struct		s_asm
{
	char            *file_name;
	struct s_token	*token_head;
	struct s_token	*token_tail;
	int				name_cmd_seen;
	int				comment_cmd_seen;
}					t_asm;

/*
**  Tokenizer
**    string = raw input string
**    type = unique integer indentifier
**    start = character count from start of line to start of token string
**    line = line number where token string starts
*/

typedef struct		s_token
{
	char			*string;
	struct s_token	*next;
	int				type;
	int				row;
	int				col;
}					t_token;

typedef struct		s_op
{
	char			*op_str;
	int				number_of_args;
	int				args[3];
	int				opcode;
	int				cycles;
	char			*description;
	char			encoding;
	char			label_is_twobytes;
}					t_op;


void		tokenize(char *str, t_asm *info);
int			valid_token(t_token *token);


#endif
