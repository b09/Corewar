/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_filler_tokens.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 23:54:37 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/08/30 18:37:54 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	Used to remove comments and newlines before the header
**
**	Called by:	valid_syntax()
*/

static void	remove_leading_nl_and_comm(t_asm *asm_obj)
{
	t_token		*current;

	current = asm_obj->token_head;
	while (current->type == COMMENT_TKN || current->type == ENDLINE_TKN)
	{
		token_unlink_del(asm_obj, current);
		current = asm_obj->token_head;
	}
}

/*
**	Removes comments and extra newlines. Leaves 1 newline token per set.
**
**	Called by:	valid_syntax()
*/

void		remove_comments_and_extra_nl(t_asm *asm_obj)
{
	t_token		*current;
	int			nl_seen;

	nl_seen = FALSE;
	remove_leading_nl_and_comm(asm_obj);
	current = asm_obj->token_head;
	while (current)
	{
		if (current->type == COMMENT_TKN ||
			(nl_seen && current->type == ENDLINE_TKN))
		{
			token_unlink_del(asm_obj, current);
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

/*
**	Removes all separator and nl tokens after validating instructions.
**
**	Called by:	valid_syntax()
*/

void		remove_separators_and_nl(t_asm *asm_obj)
{
	t_token		*current;
	t_token		*next;

	current = asm_obj->token_head;
	while (current)
	{
		next = current->next;
		if (current->type == SEPARATOR_TKN || current->type == ENDLINE_TKN)
			token_unlink_del(asm_obj, current);
		current = next;
	}
}
