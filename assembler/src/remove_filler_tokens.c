/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntactic_analysis.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 23:54:37 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/08/25 23:55:02 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	Used to remove comments and newlines before the first encoding token
*/

static void remove_leading_nl_and_comm(t_asm *asm_obj)
{
	t_token	current;

	current = asm_obj->token_head;
	while (current->type == COMMENT_TKN || current->type == ENDLINE_TKN)
	{
		asm_obj->token_head = current->next;
		token_del(current);
		current = asm_obj->token_head;
	}
}

/*
**	Removes comments and extra newlines. Leaves 1 newline token per set.
*/

void remove_comments_and_extra_nl(t_asm *asm_obj)
{
	t_token	current;
	t_token	previous;
	int		nl_seen;

	remove_nl_and_comm_before_header(asm_obj);
	current = asm_obj->token_head;
	while (current->next)
	{
		if (current->type == COMMENT_TKN ||
			(nl_seen && current->type == ENDLINE_TKN))
		{
			asm_obj->token_head = current->next;
			token_del(current);
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