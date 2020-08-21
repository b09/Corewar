/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/18 15:31:22 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/08/21 12:20:26 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

// static t_hmap   *init_token_hmap(void)
// {
//     t_hmap  *token_hmap;
//
//     token_hmap = hmap_new(N_TOKENS);
//
// }

/*
**  Duplicates substring from start of str to next whitespace.
**  Updates *str, starting position of string after extracting current substring.
**  Also updates start, the index for starting position.
**
**  Params: str, a string starting at the first char of a token.
			start, the index of the starting character for next token.
**  Return: Literal string of a single token.
**	called by:	tokenize()
*/

static char *get_token_string(char *str, int *start)
{
	char    *end;
	char	*token_string;

	// TODO: check that separator character doesn't end up together with previous token
	end = str;
	if (*str != COMMENT_CHAR && *str != ';')
	{
		while (*end && !ft_isspace(*end))
			end++;
	}
	else
	{
		while (*end && *end != '\n')
			end++;
	}
	(*start) = (*start) + (end - str);
	token_string = ft_strndup(str, end - str);
	return (token_string);
}


static int	validate_registry_lexical(char *str)
{


	return (FALSE);
}
/*
**  TOKENS:
**	1-20 intructions
**	20-29 plain text
**	30-39 non action signifiers
**	40-49 arguments
**	50-59 syntax character
**
*/

/*
**	*str argument will only be token string
**		ex: 
**			arriere:	ld	%-5, r5
**				-> [arrieere:][ld][%-5][,][r5][\n]
**
**
**	called by:	tokenize()
*/

static int  get_type(char *str)
{
    if (*str == COMMENT_CHAR || *str == ';')
        return (COMMENT_TKN);
    else if (*str == COMMAND_CHAR)
        return (COMMAND_TKN);
    else if (*str == DIRECT_CHAR)
        return (DIRECT_TKN);
	else if (*str == REGISTRY_CHAR)
        return (REGISTRY_TKN);
    else if (*str == LABEL_CHAR)
        return (INDIRECT_LABEL_TKN);
	else if (*str == '-' || ft_isdigit(*str))
        return (INDIRECT_TKN);
	else if (ft_strchr(LABEL_CHARS, *str))
	{
		if (str[ft_strlen(str) - 1] == ':')
        	return (LABEL_TKN);
		return (get_opcode(str));
	}
    else if (*str == SEPARATOR_CHAR)
        return (SEPARATOR_TKN);
	else if (*str == '\n')
        return (ENDLINE_TKN);
	else if (*str == '"')
        return (STRING_TKN);
	return (-1);
}

/*
**  Tokenizes one line of asm.
**
**  Params: str, a single line from the source retrieved using gnl.
**                  expected to be sequential.
**  Return:
**
**	called by:	read_file()
**
*/

void	tokenize(char *str, t_asm *info)
{
	static int      row;
	static t_token	*tail;
	int             col;
	t_token         *token;

	if (!row)
		row = 1;
	while (str)
	{
		while (*str != '\n' && ft_isspace(*str))
		{
			col++;
			str++;
		}
		token = (t_token *)ft_memalloc(sizeof(t_token));
		token->row = row;
		token->col = col;
		token->string = get_token_string(&str, &col);
		token->type = get_type(token->string);
		if (info->token_head == NULL)
			info->token_head = token;
		else
			tail->next = token;
		tail = token;
	}
	row++;
}
