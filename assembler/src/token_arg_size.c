/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_arg_size.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/08/29 13:42:18 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	Finds the definition of label, of which 
**
**	Params:
**			char *str	==> 
**
**	Notes:
**			
**
**	Called by:
**			argument_size()
**
*/

static int		find_label_definition(t_token *lab_arg)
{
	char		*str;
	int			i;
	t_token		*tokens;

	tokens = lab_arg->next;
	i = 0;
	str = lab_arg->type == 44 ? lab_arg->string + 2 : lab_arg->string + 1;
	while (tokens)
	{
		i += tokens->translation_size;
		if (tokens->type == LABEL_TKN && ft_strnequ(str, tokens->string,\
		ft_strlen(str)))
			return (i);
	}
	tokens = lab_arg->prev;
	while (tokens)
	{
		i -= tokens->translation_size;
		if (tokens->type == LABEL_TKN && ft_strnequ(str, tokens->string,\
		ft_strlen(str)))
			return (i);
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
**
**	Params:
**			t_token *instruction ==> instruction token
**			t_token *args	==> token->next of instruction token, assumed to be
**							an argument of the instruction
**			size_t i		==> number of argument for instruction (can be up to
**								three arguments) - 1;
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
		instruction->codage |= 1 << i;
		instruction->translation_size += 1;
		args->bytecode = get_number(args->string);
	}
	else if (args->type == DIRECT_TKN || args->type == DIR_LBL_TKN)
	{
		instruction->codage |= 2 << i;
		if (instruction->t_op->label_is_twobytes == 1)
			instruction->translation_size += 2;
		else
			instruction->translation_size += 4;
		args->bytecode = args->type == DIRECT_TKN ? get_number(args->string): 0;
	}
	else if (args->type == INDIRECT_TKN || args->type == INDIR_LBL_TKN)
	{
		instruction->codage |= 3 << i;
		instruction->translation_size += 2;
		args->bytecode = args->type == INDIRECT_TKN ? get_number(args->string) : 0;
	}
	if (args->type == INDIR_LBL_TKN || args->type == DIR_LBL_TKN)
		args->bytecode = find_label_definition(args);
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

	instruction = asm_obj->instructions_head;
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
				++i;
				argument_size(instruction, args, i * 2);
			}
		}
		instruction = instruction->next;
	}
}

// NOT NEEDED ANYMORE
void			populate_lab_args(t_asm *asm_obj)
{
	t_token		*lab_arg;
	t_token		*token;

	lab_arg = asm_obj->token_head;
	while (lab_arg)
	{
		if ((lab_arg->type == 42 && lab_arg->bytecode == 0)\
		|| (lab_arg->type == 44 && lab_arg->bytecode == 0))
		{
			token = lab_arg;
			lab_arg->bytecode = find_label_definition(token);
			if (lab_arg->bytecode == 0)
				print_error(NO_LABEL_DEFINITION);
		}
		lab_arg = lab_arg->next;
	}
}

// traverse linked list going forwards counting t_token->translation_size
// bytes between label defition and label argument, then populating
// bytecode with the byte count.
// if label defition not found, go in opposite direction and subtract
// byte counnt from position.
// if label definition not found, return ERROR