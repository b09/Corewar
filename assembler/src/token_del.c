/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_del.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 16:54:56 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/08/28 16:58:01 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		token_del(t_token *token)
{
	// free(token->token_string);
	// free(token);
	ft_memdel(token->string);
	ft_memdel(token);
}

void		token_unlink_del(t_asm *asm_obj, t_token *token)
{
	if (token == asm_obj->token_head)
		asm_obj->token_head = token->next;
	else
	{
		token->prev->next = token->next;
		if (token->next)
			token->next->prev = token->prev;
	}
	// free(token->token_string);
	// free(token);
	ft_memdel(token->string);
	ft_memdel(token);
}
