/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/18 15:31:22 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/08/30 14:05:59 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op	op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

/*
**	Finds correct operation code for assembly intruction defined in *str.
**	Searches in array of t_op structs which list legal instructions
**
**	Params:
**			char *str	==> parsed string provided by get_token_string()
**
**	Return:
**			int - operation code for instruction described in *str
**
**	Called by:
**			get_type()
*/

static int		get_opcode(char *str)
{
	char	i;

	i = 0;

	while (i < N_OPCODES)
	{
		if (ft_strequ(str, op_tab[i].op_str))
			return(op_tab[i].opcode);
		++i;
	}
	return (0);
}

/*
**
**	Params:
**			char *str	==> parsed string provided by get_token_string()
**
**	Notes:
**			Register strings (ex:"r12") are also valid labels, must separate
**
**	Return:
**			int value used as key to identify token type
**
**	Called by:
**			tokenize()
*/

static int		get_type(char *str)
{
	if (*str == COMMENT_CHAR || *str == ';')
		return (COMMENT_TKN);
	else if (*str == COMMAND_CHAR)
		return (COMMAND_TKN);
	else if (*str == DIRECT_CHAR && *(str + 1) != LABEL_CHAR)
		return (DIRECT_TKN);
	else if (*str == DIRECT_CHAR && *(str + 1) == LABEL_CHAR)
		return (DIR_LBL_TKN);
	else if (*str == REGISTRY_CHAR && str[ft_strlen(str) - 1] != ':')
		return (REGISTRY_TKN);
	else if (*str == LABEL_CHAR)
		return (INDIR_LBL_TKN);
	else if (*str == '-' || ft_isdigit(*str))
		return (INDIRECT_TKN);
	else if (ft_strchr(LABEL_CHARS, *str))
		return (str[ft_strlen(str) - 1] == ':' ? LABEL_TKN : get_opcode(str));
	else if (*str == SEPARATOR_CHAR)
		return (SEPARATOR_TKN);
	else if (*str == '\n')
		return (ENDLINE_TKN);
	else if (*str == '"')
		return (STRING_TKN);
	return (-1);
}

/*
**	Creates and populates t_token nodes, links them together into a linked list.
**
**	Params:
**			int row		==> line number in file read by gnl()
**			int *col	==> char count of starting position of token
**			char **str	==> raw string from file, provided by gnl_with_newline()
**			t_asm *info	==> assembler struct initialized by main()
**
**	Called by:
**			tokenize()
**
**	Notes:
**			If token is an instruction, the intruction's struct is copied from
**			the op_tab[17].
**
**		DEBUG
	ft_printf("func: %s len:%d str: [%s] addr:%p\n", __func__, ft_strlen(*str), *str, *str);
*/

static void			create_token(int row, int *col, char **str, t_asm *info)
{
	t_token			*token;
	static t_token	*tail;

	token = (t_token *)ft_memalloc(sizeof(t_token));
	token->row = row;
	token->col = *col;
	token->string = get_token_string(*str, col);
	(*str) += ft_strlen(token->string);
	token->type = get_type(token->string);
	if (token->type < 17)
	{
		token->t_op = (t_op *)ft_memalloc(sizeof(t_op));
		ft_memcpy((void*)token->t_op, (void *)&op_tab[token->type - 1],\
		sizeof(t_op));
		token->translation_size = 1 + token->t_op->encoding;
	}
	if (info->token_head == NULL)
		info->token_head = token;
	else
	{
		tail->next = token;
		token->prev = tail;
	}
	tail = token;
}

/*
**	Tokenizes one line of asm. Creates linked list of token nodes, populates
**	them. Calls gnl_with_newline(), and if the current str has a '"', find_quote
**	will guarantee that there is a closing quote by continueing to call gnl
**	until another closing quote is found
**
**	Params:
**			char *str	==> raw string from file, provided by gnl_with_newline()
**			t_asm *info	==> assembler struct initialized by main()
**
**	Notes:
**			Removes all whitespace PRECENDING token
**
**	Called by:
**			read_file()
**
**		DEBUG
	int		ch;
	while ((ch = getchar()) != '\n' && ch != EOF)
		continue;
*/
void			tokenize(char *str, t_asm *info)
{
	static int		row;
	int				col;

	if (!row)
		row = 1;
	while (gnl_with_newline(info->fd, &str) > 0)
	{
		col = 1;
		if (ft_strchr(str, '"') && find_end_quote(info->fd, &str, &row) == 0)
			print_error(NO_END_QUOTE);
		while (*str)
		{
			while (*str != '\n' && ft_isspace(*str))
			{
				col++;
				str++;
			}
			create_token(row, &col, &str, info);
		}
		// ft_memdel((void*)&str); // MUST DEBUG
		row++;
	}
}
