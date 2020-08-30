/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntactic_analysis_instructions.c                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 16:51:58 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/08/30 16:58:30 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			is_opcode(int type)
{
	if (type < 20)
		return (TRUE);
	return (FALSE);
}

/*
**	Validates that labels are on their own lines, updates current token to check
**
**	Input: address of current token to check.
**
**	Return: True or False
*/

static int	skip_labels(t_token **token)
{
	t_token	*current;

	current = *token;
	while (current->type == LABEL_TKN)
	{
		if (current->next && current->next->type == ENDLINE_TKN)
			current = current->next->next;
		else
			return (print_error(SYNTAX_EXPECTED_NL));
	}
	*token = current;
	return (TRUE);
}

/*
**	Validates that the type of current argument is allowed
**	for instruction's opcode.
**
**	Input:	ins,	token that contains current instruction.
**			i,		index for current argument to check.
**
**	Return: True or False
*/

static int	valid_arg(t_token *ins, int i)
{
	t_token *arg;
	int		j;

	j = 0;
	arg = ins->next;
	while (j != i)
	{
		j++;
		arg = arg->next->next;
	}
	if (arg->type == REGISTRY_TKN && ins->t_op->args[i] & T_REG)
		return (TRUE);
	else if ((arg->type == DIRECT_TKN || arg->type == DIR_LBL_TKN) &&
		ins->t_op->args[i] & T_DIR)
		return (TRUE);
	else if ((arg->type == INDIRECT_TKN || arg->type == INDIR_LBL_TKN) &&
		ins->t_op->args[i] & T_IND)
		return (TRUE);
	return (FALSE);
}

/*
**	Validates number of arguments for specific opcode,
**	calls valid_arg() on each argument, checks separation by SEPARATOR_CHAR's.
**
**	Updates *token to point to next token to check after this instruction line
**	was validated.
**
**	Input: address of token containing opcode.
**
**	Return: True or False
*/

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

/*
**	Makes sure instructions are syntactically correct.
**	Also allowes any amount of labels to precede an instruction.
**	Instruction lines are formatted correctly if;
**
**	1. They start with an opcode.
**	2. They have the correct amount of arguments for that opcode.
**	3. The arguments are of types allowed by that opcode.
**	4. Arguments are seperated by SEPARATOR_CHAR's
**	5. Each opcode and label are at the start of a line.
**
**	Input: asm_obj
**
**	Return: True or False
**
**	Called by: valid_syntax()
*/

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
