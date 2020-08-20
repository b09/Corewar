/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/18 15:31:22 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/08/20 17:28:31 by macbook       ########   odam.nl         */
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
*/

static char *get_token_string(char **str, int *start)
{
	char    *end;

	// TODO: check that separator character doesn't end up together with previous token
	end = *str;
	if (**str != COMMENT_CHAR && **str != ';')
	{
		while (!ft_isspace(end))
			end++;
	}
	else
	{
		while (*end != '\n')
			end++;
	}
	(*start) = (*start) + (end - *str);
	token_string = ft_strndup(*str, end - *str);
	return (token_string);
}

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
**		50 SEPERATOR
**		51 ENDLINE
**	
*/

static int	validate_registry_lexical(char *str)
{
	

	return (FALSE);
}

/*
**	*str arg will be only be token string
**		ie: arriere:	ld	%-5, r5
**				-> [arrieere:][ld][%-5][,][r5][\n]
*/

static int  get_type(char *str)
{
    if (*str == COMMENT_CHAR || *str == ';')
        return (COMMENT_TKN);
    else if (*str == COMMAND_CHAR)
        return (COMMAND_TKN);
    else if (*str == DIRECT_CHAR)
        return (DIRECT_TKN);
	else if (*str == REGISTRY_CHAR) // && ft_atoi(str+1) >= 0
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
**  Return: head of list of new tokens, to be appended to the end of
**                  the complete list.
*/

t_token *tokenize(char *str)
{
	static int      line;
	static t_hmap   token_hmap;
	int             start;
	t_token          *head;
	t_token         *token;

	line = 1;
	start = 1;
	// if (token_hmap == NULL)
	//     token_hmap = init_token_hmap();
	while (str)
	{
		while (*str != '\n' && ft_isspace(*str))
		{
			start++;
			str++;
		}
		token = (t_token *)ft_memalloc(sizeof(t_token));
		token->line = line;
		token->start = start;
		token->token_string = get_token_string(&str, &start);
		token->type = get_type(token->token_string);
		ft_lstappend(head, ft_lstnew(token));
	}
	line++;
	return (head);
}
