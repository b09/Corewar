/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_arg_size.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/08/30 19:16:50 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	Finds the token at which the functions's argument is defined. t_token lab_-
**	arg is either a IND_LBL_TKN or a DIR_LBL_TKN. As func() traverses tokens
**	seeking definition, the t_token->translation_size is added for all tokens
**	between label definition and label as argument, which are the amount of
**	bytes which will separate definition from argument in the tranlated byte-
**	code. Token list is searched forwards and backwards, and if definition is
**	not found, error printed and program exited.
**
**	Params:
**			t_token *lab_arg ==> label token used as argument for an instruction
**
**	Notes:
**			if label definition not found, error printed and program exited.
**			When func() traverses the linked list backwards, the instruction
**			string which uses lab_arg as one of its arguments must be skipped
**			when counting token->translation_size bytes, for which the second
**			while loop is used.
**			ex:
**			line 1[instruction size = 1][arg1 size = 2][arg2 size = 4]
**														^^ start counting here
**			line 2[instruction size = 1][arg1 size = 2][arg2 (lab_arg) size = 4]
**										^^ do not start counting here
**
**	Called by:
**			argument_size()
**
*/

static int		find_label_definition(t_token *lab_arg, t_token *tokens, int i,\
				char *str)
{
	str = lab_arg->type == 44 ? lab_arg->string + 2 : lab_arg->string + 1;
	while (tokens)
	{
		i += tokens->translation_size;
		if (tokens->type == LABEL_TKN && ft_strnequ(str, tokens->string,\
		ft_max(ft_strlen(str), ft_strlen(tokens->string) - 1)))
			return (i);
		tokens = tokens->next;
	}
	tokens = lab_arg->prev;
	while (tokens && tokens->type > 19)
		tokens = tokens->prev;
	tokens = tokens->prev;
	i = 0;
	while (tokens)
	{
		i -= tokens->translation_size;
		if (tokens->type == LABEL_TKN && ft_strnequ(str, tokens->string,\
		ft_max(ft_strlen(str), ft_strlen(tokens->string) - 1)))
			return (i);
		tokens = tokens->prev;
	}
	return (print_error(NO_LABEL_DEFINITION));
}

/*
**	Moves the pointer of the string to enable ft_atoi to grab number from string
**	String, which is the t_token->string for an argument token has already been
**	validated and is therefore assumed to contain a valid number.
**
**	Params:
**			char *str	==> token string containing letter chars and int chars
**
**	Called by:
**			argument_size()
**
*/

static int		get_number(char *str)
{
	while (*str && !ft_isdigit(*str))
		++str;
	return (ft_atoi(str));
}

/*
**	Based on token type (of which args will be an argument to an instruction),
**	func() populates t_token->bycode member by ft_atoi'ng the string of the
**	argument token if argument is not a label. In case of argument being a
**	label, bycode is populated with int offset to label definition. Codage byte
**	required for translation which specifies type of argument is also populated.
**	The amount of bytes that each argument will occupy in the bytecode is
**	is determined by t_token->translation_size, which this func() also populates
**
**	Params:
**			t_token *instruction ==> instruction token
**			t_token *args	==> token->next of instruction token, assumed to be
**							an argument of the instruction
**			size_t i		==> number of argument for instruction - 1 (can be
**								up to three arguments);
**
**	Notes:
**			find_label_definition() will print error and exit if label
**			definition not found
**
**	Called by:
**			get_argument_size()
**
*/

static void		argument_size(t_token *instruction, t_token *args, size_t i)
{
	if (args->type == REGISTRY_TKN)
	{
		instruction->codage |= 1 << (i * 2);
		args->translation_size = 1;
		args->bytecode = get_number(args->string);
	}
	else if (args->type == DIRECT_TKN || args->type == DIR_LBL_TKN)
	{
		instruction->codage |= 2 << (i * 2);
		if (instruction->t_op->label_is_twobytes == 1)
			args->translation_size = 2;
		else
			args->translation_size = 4;
		args->bytecode = args->type == DIRECT_TKN ? get_number(args->string): 0;
	}
	else if (args->type == INDIRECT_TKN || args->type == INDIR_LBL_TKN)
	{
		instruction->codage |= 3 << (i * 2);
		args->translation_size = 2;
		args->bytecode = args->type == 43 ? get_number(args->string) : 0;
	}
	if (args->type == INDIR_LBL_TKN || args->type == DIR_LBL_TKN)
		args->bytecode = find_label_definition(args, NULL, 0, NULL);
}

/*
**	Iterates through all tokens, populating t_token->bycode member with correct
**	int value based on token being an instruction or argument.
**
**	Params:
**			t_asm *info	==> assembler struct initialized by main()
**
**	Called by:
**			none
**
*/

void			get_argument_size(t_asm *asm_obj)
{
	t_token		*args;
	t_token		*instruction;
	size_t		i;

	instruction = asm_obj->token_head;
	while (instruction)
	{
		if (instruction->t_op)
		{
			i = 0;
			args = NULL;
			instruction->bytecode = instruction->type;
			while (i < instruction->t_op->number_of_args)
			{
				if (!args)
					args = instruction->next;
				else
					args = args->next;
				argument_size(instruction, args, i);
				++i;
			}
		}
		instruction = instruction->next;
	}
}