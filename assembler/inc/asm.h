/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/18 14:14:19 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H

# define ASM_H

# include "libft.h"
# include "ft_printf.h"
# include <fcntl.h>
# include <stdbool.h>

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
# define CHAMP_MAX_SIZE			768
# define COMMENT_CHAR			'#'
# define ALT_COMMENT_CHAR		';'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','
# define REGISTRY_CHAR			'r'
# define COMMAND_CHAR			'.'
# define ENDLINE_CHAR			'\n'
# define STRING_CHAR			'"'
# define N_OPCODES				16
# define N_LABEL_CHARS			38
# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"
# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"
# define REG_NUMBER				16
# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

/*
**			ERROR MACROS
*/

# define SYNTAX_NO_NAME			"Syntax error: expected .name and .comment\n"
# define SYNTAX_NO_NAME_STR		"Syntax error: expected string after .name\n"
# define SYNTAX_NO_CMNT_STR		"Syntax error: expected string after .comment\n"
# define NO_LABEL_DEFINITION	"Syntax error: label not defined\n"
# define NO_END_QUOTE			"Syntax error: No end quote found for string\n"
# define NO_END_QUOTE_NL		"Syntax error: End quote or newline not found\n"
# define SYNTAX_INVALID_ARG		"Syntax error: Invalid argument\n"
# define SYNTAX_MISSING_SEPARATOR "Syntax error: Missing comma\n"
# define SYNTAX_EXPECTED_INSTRUCTION "Syntax error: Expected instruction\n"
# define SYNTAX_EXPECTED_NL		"Syntax error: Missing newline character\n"
# define SYNTAX_CMNT_LONG		"Syntax error: Champion comment is too long\n"
# define SYNTAX_NAME_LONG		"Syntax error: Champion name is too long\n"
# define SYNTAX_HEADER_INVALID	"Syntax error: Header is invalid\n"
# define FILE_TYPE_INVALID		"File type is invalid\n"
# define NUM_ARGS_INVALID		"Use one assembly file at a time.\n"
# define SYNTAX_MISSING_NL		"Syntax error: Missing new line\n"
# define INVALID_TKN_TYPE		"Operation is invalid for some reason\n"
# define BAD_FILE_DESCRIPTOR	"File descriptor returned error\n"
# define SYNTAX_LABEL_DUPLICATE	"Redefinition of label not allowed\n"

/*
**		TOKENS:
**	1-20 intructions
**	20-29 plain text
**	30-39 non action signifiers
**	40-49 arguments
**	50-59 syntax character
**
**		20 COMMENT
**		21 STRING
**
**		30 COMMAND
**		31 LABEL
**
**		40 DIRECT
**		41 REGISTRY
**		42 INDIRECT_LABEL
**		43 INDIRECT
**		44 DIRECT_LABEL
**
**		50 SEPARATOR
**		51 ENDLINE
*/

# define COMMENT_TKN			20
# define STRING_TKN				21
# define COMMAND_TKN			30
# define LABEL_TKN				31
# define DIRECT_TKN				40
# define REGISTRY_TKN			41
# define INDIR_LBL_TKN			42
# define INDIRECT_TKN			43
# define DIR_LBL_TKN			44
# define SEPARATOR_TKN			50
# define ENDLINE_TKN			51

typedef char	t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		128
# define COMMENT_LENGTH			2048
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct					s_header
{
	unsigned int				magic;
	char						prog_name[PROG_NAME_LENGTH + 1];
	unsigned int				prog_size;
	char						comment[COMMENT_LENGTH + 1];
}								t_header;

/*
**			Main Assembler Struct
**	file_name			= name of file provided to asm executable
**	champ_name			= name of champion contained in assebly file
**	champ_comment		= comment of champion contained in assembly file
**	token_head			= head of t_token linked list
**	token_tail			= tail of t_token linked list
*/

typedef struct					s_asm
{
	int							fd;
	char						*file_name;
	char						*champ_name;
	char						*champ_comment;
	struct s_token				*token_head;
	struct s_token				*token_tail;
}								t_asm;

/*
**			Tokenizer
**	string	= raw input string from assembly file provided by gnl()
**	next	= pointer to next token
**	prev	= pointer to previous token
**	type	= unique integer indentifier
**	row		= line number where token string starts
**	col		= character count from start of line to start of token string
**	translation_size = if instruction, size in bytes of instruction with args
**	t_oper	= if instruction, operation struct containing rules for instruction
**	bytecode= value of the string translated to the appropriate int value used
**				final translation of assembly file into bytecode
**	codage	= single byte used as flag to specify the types of arguments an
**				instruction will have, added to translated bytecode for vm
*/

typedef struct					s_token
{
	char						*string;
	struct s_token				*next;
	struct s_token				*prev;
	int							type;
	int							row;
	int							col;
	int							translation_size;
	struct s_op					*t_oper;
	int							bytecode;
	unsigned char				codage;
}								t_token;

/*
**	struct provided as resource, found in project spec
*/

typedef struct					s_op
{
	char						*op_str;
	int							number_of_args;
	char						args[3];
	int							opcode;
	int							cycles;
	char						*description;
	char						encoding;
	char						label_is_twobytes;
}								t_op;

/*
**	tokenizer.c
*/

void							tokenize(char *str, t_asm *info);

/*
**	token_arg_size.c
*/

void							get_argument_size(t_asm *asm_obj);
void							populate_label_size(t_asm *asm_obj);

/*
**	print_functions.c
*/

void							print_asm_obj(t_asm *asm_obj);
int								print_error(char *str);

/*
**	lexical_analysis.c
*/

int								valid_token(t_token *token);

/*
**	lexical_analysis_helpers.c
*/

int								valid_cmd_tkn(char *str);
int								valid_dir_tkn(char *str);
int								valid_reg_tkn(char *str);
int								valid_ilbl_tkn(char *str);
int								valid_ind_tkn(char *str);

/*
**	remove_filler_tokens.c
*/

void							remove_separators_and_nl(t_asm *asm_obj);
void							remove_comments_and_extra_nl(t_asm *asm_obj);

/*
**	syntactic_analysis_header.c
*/

int								valid_header(t_asm *asm_obj);

/*
**	syntactic_analysis_instructions.c
*/

int								valid_instructions(t_asm *asm_obj);
int								is_opcode(int type);

/*
**	syntactic_analysis.c
*/

int								valid_syntax(t_asm *asm_obj);

/*
**	token_del.c
*/

void							token_del(t_token *token);
void							token_unlink_del(t_asm *asm_obj, t_token *tokn);
void							token_lst_del(t_token *head);

/*
**	token_string_functions.c
*/

int								find_end_quote(int fd, char **str, int *row);
char							*get_token_string(char *str, int *col);

/*
**	token_del.c
*/

void							token_del(t_token *token);
void							token_unlink_del(t_asm *asm_obj, t_token *tokn);

/*
**	translator.c
*/

int								little_to_big_endian(int number, size_t size);

/*
**	translation_write_funcs.c
*/

int								create_and_write_file(t_asm *asm_obj);

#endif
