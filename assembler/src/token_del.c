/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_del.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 16:54:56 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/09/18 10:56:28 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	token_del(t_token *token)
{
	free((void*)token->string);
	free((void*)token->t_oper);
	free((void*)token);
}

void	token_unlink_del(t_asm *asm_obj, t_token *token)
{
	if (token == asm_obj->token_head)
	{
		asm_obj->token_head = token->next;
		if (asm_obj->token_head)
			asm_obj->token_head->prev = NULL;
	}
	else
	{
		token->prev->next = token->next;
		if (token->next)
			token->next->prev = token->prev;
	}
	token_del(token);
}

void	token_lst_del(t_token *head)
{
	t_token *current;
	t_token *next;

	current = head;
	while (current)
	{
		next = current->next;
		token_del(current);
		current = next;
	}
}
