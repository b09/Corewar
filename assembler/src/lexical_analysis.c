/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexical_analysis.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/19 13:56:19 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/08/31 15:13:02 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	A label token must contain only LABEL_CHARS, except for the last character
**	which must be ':'
**
**	Called by:	valid_token()
*/

static int		valid_lbl_tkn(char *str)
{
	while (ft_strchr(LABEL_CHARS, *str))
		str++;
	if (*str != LABEL_CHAR || ft_strlen(str) != 1)
		return (FALSE);
	return (TRUE);
}

/*
**	Checks two types of tokens: SEPARATOR_TKN and ENDLINE_TKN
**	Each token will contain a one character string, either SEPARATOR_CHAR or
**	ENDLINE_CHAR, provided as the second parameter to the func()
**
**	Called by:	valid_token()
*/

static int		valid_character_tkn(char *str, char character)
{
	if (*str != character || ft_strlen(str) != 1)
		return (FALSE);
	return (TRUE);
}

/*
**	A string token must begin and end with the quote character
**
**	Called by:	valid_token()
*/

static int		valid_str_tkn(char *str)
{
	if (*str != STRING_CHAR || str[ft_strlen(str) - 1] != STRING_CHAR)
		return (FALSE);
	str++;
	while (*str && *str != '"')
		str++;
	str++;
	if (*str != '\0')
		return (FALSE);
	return (TRUE);
}

/*
**	Token string must begin "%:" followed by only LABEL_CHARS
**
**	Called by:	valid_token()
*/

static int		valid_dir_lbl_tkn(char *str)
{
	if (*str != DIRECT_CHAR)
		return (FALSE);
	str++;
	if (*str != ':')
		return (FALSE);
	str++;
	while (*str)
	{
		if (!ft_strchr(LABEL_CHARS, *str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

/*
**	Checks token string is a valid based on token's type
**
**	Called by:	lexicon_valid()
*/

int				valid_token(t_token *token)
{
	if (token->type == COMMENT_TKN)
		return (TRUE);
	else if (token->type == COMMAND_TKN)
		return (valid_cmd_tkn(token->string));
	else if (token->type == DIRECT_TKN)
		return (valid_dir_tkn(token->string));
	else if (token->type == DIR_LBL_TKN)
		return (valid_dir_lbl_tkn(token->string));
	else if (token->type == REGISTRY_TKN)
		return (valid_reg_tkn(token->string));
	else if (token->type == INDIR_LBL_TKN)
		return (valid_ilbl_tkn(token->string));
	else if (token->type == INDIRECT_TKN)
		return (valid_ind_tkn(token->string));
	else if (token->type == LABEL_TKN)
		return (valid_lbl_tkn(token->string));
	else if (token->type == SEPARATOR_TKN)
		return (valid_character_tkn(token->string, SEPARATOR_CHAR));
	else if (token->type == ENDLINE_TKN)
		return (valid_character_tkn(token->string, ENDLINE_CHAR));
	else if (token->type == STRING_TKN)
		return (valid_str_tkn(token->string));
	else if (token->type >= 1 && token->type <= 16)
		return (TRUE);
	return (FALSE);
}
