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
	if (token->type == COMMENT_TYPE)
		return (TRUE);
	else if (token->type == COMMAND_TYPE)
		//
		return (FALSE);
}
