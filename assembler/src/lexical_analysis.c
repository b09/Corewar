/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>             +#+                   */
/*                                                   +#+                      */
/*   Created: 2020/08/19 13:56:19 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/08/19 13:56:19 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	valid_cmd_tkn(char *str)
{
	if (!ft_strequ(str, NAME_CMD_STRING) &&
		!ft_strequ(str, COMMENT_CMD_STRING))
		return (FALSE);
	return (TRUE);
}

int	valid_token(t_token *token)
{
	if (token->type == COMMENT_TKN)
		return (TRUE);
	else if (token->type == COMMAND_TKN)
		return (valid_cmd_tkn(token->string));
	else if (token->type == DIRECT_TKN)
		return (FALSE);
	else if (token->type == REGISTRY_TKN)
		return (FALSE);
	else if (token->type == INDIRECT_LABEL_TKN)
		return (FALSE);
	else if (token->type == INDIRECT_TKN)
		return (FALSE);
	else if (token->type == LABEL_TKN)
		return (FALSE);
	else if (token->type == SEPARATOR_TKN)
		return (FALSE);
	else if (token->type == ENDLINE_TKN)
		return (FALSE);
	else if (token->type == STRING_TKN)
		return (FALSE);
	else if (token->type >= 1 && token->type <= 16)
		return (FALSE);
}
