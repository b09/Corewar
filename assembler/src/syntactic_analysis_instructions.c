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

static int	valid_arg(t_token *ins, int i)
{
	t_token *arg;
	int		j;

	j = 0;
	arg = ins->next;
	while (j != i)
	{
		j++
		arg = arg->next->next;
	}
	if (arg->type == REGISTRY_TKN && ins->t_op->args[i] & T_REG)
		return (TRUE);
	else if ((arg->type == DIRECT_TKN || arg->type == DIRECT_LABEL_TKN) &&
		ins->t_op->args[i] & T_DIR)
		return (TRUE);
	else if ((arg->type == INDIRECT_TKN || arg->type == INDIRECT_LABEL_TKN) &&
		ins->t_op->args[i] & T_IND)
		return (TRUE);
	return (FALSE);
}

static int	validate_args(t_token **token)
{
	t_token *ins;
	t_token *current;
	int		i;

	ins = *token;
	current = ins->next;;
	i = 0;
	while (i < ins->t_op->number_of_args)
	{
		if (valid_arg(ins, i) == FALSE)
			return (print_error(SYNTAX_INVALID_ARG));
		i++;
		current = current->next;
		if (i < ins->t_op->number_of_args)
		{
			if (current->type != SEPARATOR_TKN)
				return (print_error(SYNTAX_MISSING_SEPARATOR));
			current = current->next;
		}
	}
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
		validate_args(&current);
		if (current->type != ENDLINE_TKN)
			return (print_error(SYNTAX_EXPECTED_NL));
		current = current->next;
	}
	return (TRUE);
}
