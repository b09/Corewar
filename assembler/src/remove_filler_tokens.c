/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_filler_tokens.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 23:54:37 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/08/27 16:57:57 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		token_del(t_token *token)
{
	free(token->token_string);
	free(token);
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
	free(token->token_string);
	free(token);
}

static void		remove_nl_and_comm_before_header(t_asm *asm_obj)
{
	return ;
}



/*
**	Used to remove comments and newlines before the first encoding token
**
**	Called by:	valid_syntax()
*/

static void		remove_leading_nl_and_comm(t_asm *asm_obj)
{
	t_token		*current;

	current = asm_obj->token_head;
	while (current->type == COMMENT_TKN || current->type == ENDLINE_TKN)
	{
		token_unlink_del(current);
		current = asm_obj->token_head;
	}
}

/*
**	Removes comments and extra newlines. Leaves 1 newline token per set.
**
**	Called by:	valid_syntax()
*/

void			remove_comments_and_extra_nl(t_asm *asm_obj)
{
	t_token		*current;
	t_token		*previous;
	int			nl_seen;

	remove_nl_and_comm_before_header(asm_obj);
	current = asm_obj->token_head;
	while (current->next)
	{
		if (current->type == COMMENT_TKN ||
			(nl_seen && current->type == ENDLINE_TKN))
		{
			token_unlink_del(current);
			current = asm_obj->token_head;
		}
		else
		{
			if (current->type == ENDLINE_TKN)
				nl_seen = TRUE;
			else
				nl_seen = FALSE;
			current = current->next;
		}
	}
}
