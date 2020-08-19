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

int	valid_token(t_token *token)
{
	if (token->type == COMMENT_TKN)
		;
	else if (token->type == COMMAND_TKN)
		return (FALSE);
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
	return (TRUE);
}
