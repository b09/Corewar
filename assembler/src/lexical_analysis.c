/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexical_analysis.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/19 13:56:19 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/08/24 19:57:17 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		valid_cmd_tkn(char *str)
{
	if (!ft_strequ(str, NAME_CMD_STRING) &&
		!ft_strequ(str, COMMENT_CMD_STRING))
		return (FALSE);
	return (TRUE);
}

static int		valid_dir_tkn(char *str)
{
	if (*str != DIRECT_CHAR)
		return (FALSE);
	str++;
	if (*str == ':')
	{
		while (str)
		{
			if (!ft_strchr(LABEL_CHARS, *str))
				return (FALSE);
			str++;
		}
	}
	else
	{
		if (*str == '-')
			str++;
		if (*str == '\0')
			return (FALSE);
		while (ft_isdigit(*str))
			str++;
		if (*str != '\0')
			return (FALSE);
	}
	return (TRUE);
}

static int		valid_reg_tkn(char *str)
{
	if (*str != LABEL_CHAR)
		return (FALSE);
	str++;
	if (ft_atoi(str) == 0 || ft_atoi(str) > 99)
		return (FALSE);
	if (!ft_isdigit(str[0]))
		return (FALSE);
	if (ft_strlen(str) == 2 && !ft_isdigit(str[1]))
		return (FALSE);
	return (TRUE);
}

static int		valid_ilbl_tkn(char *str)
{
	if (*str != LABEL_CHAR)
		return (FALSE);
	str++;
	while (str)
	{
		if (!ft_strchr(LABEL_CHARS, *str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

static int		valid_ind_tkn(char *str)
{
	if (*str == '-')
		str++;
	if (*str == '\0')
		return (FALSE);
	while (ft_isdigit(*str))
		str++;
	if (*str != '\0')
		return (FALSE);
	return (TRUE);
}

static int		valid_lbl_tkn(char *str)
{
	while (ft_strchr(LABEL_CHARS, *str))
		str++;
	if (*str != LABEL_CHAR || ft_strlen(str) != 1)
		return (FALSE);
	return (TRUE);
}

static int		valid_sep_tkn(char *str)
{
	if (*str != SEPARATOR_CHAR || ft_strlen(str) != 1)
		return (FALSE);
	return (TRUE);
}

static int		valid_nl_tkn(char *str)
{
	if (*str != ENDLINE_CHAR || ft_strlen(str) != 1)
		return (FALSE);
	return (TRUE);
}

static int		valid_str_tkn(char *str)
{
	if (*str != STRING_CHAR || str[ft_strlen(str) - 1] != STRING_CHAR)
		return (FALSE);
	str++;
	while (*str != '"')
		str++;
	if (ft_strchr(str, '"') < str + (ft_strlen(str) - 1))
		return (FALSE);
	return (TRUE);
}

int				valid_token(t_token *token)
{
	if (token->type == COMMENT_TKN)
		return (TRUE);
	else if (token->type == COMMAND_TKN)
		return (valid_cmd_tkn(token->string));
	else if (token->type == DIRECT_TKN)
		return (valid_dir_tkn(token->string));
	else if (token->type == REGISTRY_TKN)
		return (valid_reg_tkn(token->string));
	else if (token->type == INDIRECT_LABEL_TKN)
		return (valid_ilbl_tkn(token->string));
	else if (token->type == INDIRECT_TKN)
		return (valid_ind_tkn(token->string));
	else if (token->type == LABEL_TKN)
		return (valid_lbl_tkn(token->string));
	else if (token->type == SEPARATOR_TKN)
		return (valid_sep_tkn(token->string));
	else if (token->type == ENDLINE_TKN)
		return (valid_nl_tkn(token->string));
	else if (token->type == STRING_TKN)
		return (valid_str_tkn(token->string));
	else if (token->type >= 1 && token->type <= 16)
		return (TRUE);
	return (FALSE);		// bprado, added line to ensure some return
}
