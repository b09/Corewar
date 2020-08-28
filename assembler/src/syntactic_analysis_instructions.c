/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntactic_analysis_instructions.c                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 16:51:58 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/08/28 16:52:10 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	skip_labels(t_token **token)
{
	t_token	*current;

	current = *token;
	while (current->type == LABEL_TKN)
	{
		if (current->next && current->next->type == ENDLINE_TKN)
			current = current->next->next;
		else
			return (print_error(SYNTAX_EXPECTED_NL_AFTER_LABEL));
	}
	*token = current;
	return (TRUE);
}

int			valid_instructions(t_asm *asm_obj)
{
	t_token	*current;

	current = asm_obj->token_head;
	while (current)
	{
		skip_labels(&current);
		if (!is_opcode(current->type))
			return (print_error(SYNTAX_EXPECTED_INSTRUCTION));
		// DO STUFF TO CHECK ARGUMENTS AND SEPARATORS
		if (current->type != ENDLINE_TKN)
			return (print_error(SYNTAX_EXPECTED_NL));
		current = current->next;
	}
	return (TRUE);
}
