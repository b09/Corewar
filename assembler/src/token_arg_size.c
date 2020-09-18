/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_arg_size.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/14 13:46:35 by macbook       ########   odam.nl         */
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
**			Before func() traverses the linked list seeking the label definition
**			it must first start counting token_translation_size from the
**			the beginning of the instruction line in which it was called. If
**			instruction line is as follows:
**	ins line -- [block1, size = 1][block2, size = 2][block3 (lab_arg), size = 4]
**			then it must start counting from block1
**
**	Called by:
**			argument_size()
*/

static int		find_label_definition(t_token *lab_arg, t_token *tokens, int i,\
				char *str)
{
	while (tokens && is_opcode(tokens->type) == FALSE)
		tokens = tokens->prev;
	while (tokens)
	{
		i += tokens->translation_size;
		if (tokens->type == LABEL_TKN && ft_strnequ(str, tokens->string,\
		ft_max(ft_strlen(str), ft_strlen(tokens->string) - 1)))
			return (i);
		tokens = tokens->next;
	}
	tokens = lab_arg;
	while (tokens && is_opcode(tokens->type) == FALSE)
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
*/

static int		get_number(char *str)
{
	while (*str && !ft_isdigit(*str) && *str != '-')
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
*/

static void		argument_size(t_token *instruction, t_token *arg, size_t i)
{
	if (arg->type == REGISTRY_TKN)
	{
		instruction->codage |= 1 << (6 - (i * 2));
		arg->translation_size = 1;
		arg->bytecode = get_number(arg->string);
	}
	else if (arg->type == DIRECT_TKN || arg->type == DIR_LBL_TKN)
	{
		instruction->codage |= 2 << (6 - (i * 2));
		if (instruction->t_oper->label_is_twobytes == 1)
			arg->translation_size = 2;
		else
			arg->translation_size = 4;
		arg->bytecode = arg->type == DIRECT_TKN ? get_number(arg->string) : 0;
	}
	else if (arg->type == INDIRECT_TKN || arg->type == INDIR_LBL_TKN)
	{
		instruction->codage |= 3 << (6 - (i * 2));
		arg->translation_size = 2;
		arg->bytecode = arg->type == 43 ? get_number(arg->string) : 0;
	}
}

/*
**	Iterates through all tokens, populating t_token->bycode member with correct
**	int value based on token being an instruction or argument.
**
**	Params:
**			t_asm *info	==> assembler struct initialized by main()
**
**	Called by:
**			main ()
*/

void			get_argument_size(t_asm *asm_obj)
{
	t_token		*args;
	t_token		*instruction;
	int			i;

	instruction = asm_obj->token_head;
	while (instruction)
	{
		if (instruction->t_oper)
		{
			i = 0;
			args = NULL;
			instruction->bytecode = instruction->type;
			while (i < instruction->t_oper->number_of_args)
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

/*
**	Iterates through all tokens, populating t_token->bycode member with correct
**	int value based on token being an indirect label or a direct label.
**
**	Params:
**			t_asm *info	==> assembler struct initialized by main()
**
**	Called by:
**			main ()
*/

void			populate_label_size(t_asm *asm_obj)
{
	t_token		*tokens;

	tokens = asm_obj->token_head;
	while (tokens)
	{
		if (tokens->type == INDIR_LBL_TKN || tokens->type == DIR_LBL_TKN)
			tokens->bytecode = find_label_definition(tokens, tokens, 0,\
			tokens->type == 44 ? tokens->string + 2 : tokens->string + 1);
		tokens = tokens->next;
	}
}
