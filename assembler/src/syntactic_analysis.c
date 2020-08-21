/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexical_analysis.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/19 19:26:19 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/08/21 19:26:29 by fmiceli     ########   odam.nl           */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	valid_syntax(t_asm *asm_obj)
{
	static int		state;
	static t_token	*token = asm_obj->token_head;

	if (state == START)
	{
		if (token)
	}
	return (FALSE);
}
