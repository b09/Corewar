/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_string_funcs.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/08/24 18:04:28 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	Finds substring in str, returns duplicated substring.
**	*col is the character count in string for when token begins (not index!)
**	*col's incremented value is for the next token, not current token
**	
**	Rules:
**			if *str == '\n', increase *col++, copy '\n'
**			if *str == '"', copy til next '"', *col = length of quoted string
**			if *str == '#' or ';', copy until newline (can there be EOF at end?)
**			if *str is any other character, copy until '\n' || ',' || ft_isspace
**
**	Params:	
**			char *str	==> string starting at the first char of a token.
**			int *col 	==> char count of starting position of token, updated -
**							- for next token
**	Notes:
**			Initial whitespace jumped over before *str arrives to func()
**	
**	Return:
**			Literal string of a single token.
**	
**	Called by:	tokenize()
*/

static char		*get_token_string(char *str, int *col)
{
	int		i;

	i = 0;
	if (ft_strchr("\n,\"*;", *str))
		i++;
	if (*str == '"' || *str == '#' || *str == ';')
	{
		i = ft_strchr_int(&str[i], *str == '"' ? '"' : '\n');
		if (i == -1)
			return (NULL);// handle error
		i += *str == '"' ? 2 : 1;
	}
	else
	{
		while (str[i] && ft_isspace(str[i]) == FALSE && str[i] != ',')
			++i;
	}
	*col += i;
	return (ft_strndup(str, i));
}

/*
**	func() guarantees that there will be a closing quote for every opened quote.
**	If the current line doesn't not contain even pairs of quotes, gnl_newline()
**	will be called, with the new string joining the old string
**	
**	Params:	
**			char **str	==> pointer to raw string from file, provided by 
**							gnl_with_newline().
**			int fd		==> assembler struct initialized by main()
**			int *row	==> current line number (row) in file being read
**
**	Notes:
**			If the new str (populated by gnl()) does contain an '"', the
**			joined_sting (containing the new and old str), will be checked for
**			even pairs of quotes by guarentee_quote_pairs().
**	
**	Return:
**			FALSE (0)= odd pairs of quotes found (no ending quote)
**			TRUE (1) = even pairs of quotes
**	
**	Called by:
**			tokenize()
*/

static int		find_end_quote(int fd, char **str, int *row)
{
	char	*old_string;
	char	*joined_string;

	old_string = *str;
	joined_string = *str;
	if (guarantee_quote_pairs(*str) == TRUE)
		return (TRUE);
	while (gnl_with_newline(fd, str) > 0)
	{
		joined_string = ft_strjoin(old_string, *str);
		// ft_memdel((void*)&old_string); // MUST DEBUG
		old_string = joined_string;
		(*row)++;
		if (ft_strchr_int(*str, '"') && guarantee_quote_pairs(joined_string))
		{
			*str = joined_string;
			return (TRUE);
		}
	}
	*str = joined_string;
	return (FALSE);
}

/*
**	func() checks number of quotes in the str
**	
**	Params:	
**			char *str	==> raw input str from gnl(). str can be long, made from
**							multiple calls to gnl().
**	
**	Return:
**			FALSE (0)= odd pairs of quotes found (no ending quote)
**			TRUE (1) = even pairs of quotes
**	
**	Called by:
**			find_end_quote()
*/

int				guarantee_quote_pairs(char *str)
{
	int		quotes;

	quotes = 0;
	while (*str)
	{
		quotes += (*str == '"') ? 1 : 0;
		++str;
	}
	if (quotes % 2 == 0)
		return (TRUE);
	return (FALSE);
}
