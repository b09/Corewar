/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntactic_analysis.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/19 19:26:19 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/08/24 19:57:55 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

// int				valid_syntax(t_asm *asm_obj)
// {
// 	static int		state;
// 	static t_token	*token;
//
// 	token = asm_obj->token_head;
// 	// if (state == START) // commented out for compilation, START not defined
// 	if (state == TRUE)	// fake line for compilation
// 	{
// 		if (token->type == COMMENT_TKN)
// 			state == COMMENT_TKN;
// 		else if (token->type == COMMAND_TKN)
// 		{
// 			if (token->token_string)
// 		}
// 		token = token->next;
// 		return (TRUE);
// 	}
// 	return (FALSE);
// }

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
**	Removes comments and extra newlines. Leaves 1 newline token inbetween others
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
