/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntactic_analysis.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/19 19:26:19 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/08/23 16:29:48 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	valid_syntax(t_asm *asm_obj)
{
	static int		state;
	static t_token	*token;

	token = asm_obj->token_head;
	// if (state == START) // commented out for compilation, START not defined
	if (state == TRUE)	// fake line for compilation
	{
		if (token)
		;
	}
	return (FALSE);
}
