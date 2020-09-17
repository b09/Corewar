/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ops_store_funcs.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/18 00:06:02 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_st(t_cursor *cursor, t_arena *arena, t_args *args,
			int position)
{
	if (check_register_values(args, 1, 0, 0) == FALSE)
		return ;
	cursor->jump = 2 + args->size_1 + args->size_2 + args->size_3;
	if (args->size_2 == SIZE_REG)
		cursor->registry[args->value_2 - 1] =
		cursor->registry[args->value_1 - 1];
	else if (args->size_2 == SIZE_IND)
	{
		position = (position + args->value_2) % IDX_MOD;
		int_to_ustr(cursor->registry[args->value_1 - 1],
										arena->field, position, 4);
	}
}

void		op_sti(t_cursor *cursor, t_arena *arena, t_args *args,
			int position)
{
	if (check_register_values(args, 1, 0, 0) == FALSE)
		return ;
	cursor->jump = 2 + args->size_1 + args->size_2 + args->size_3;
	if (args->size_2 != SIZE_IND)
	{
		position = position + args->value_2 +
									args->value_3 % IDX_MOD;
		int_to_ustr(cursor->registry[args->value_1 - 1],
							arena->field, position, 4);
	}
	else
	{
		int_to_ustr(cursor->registry[args->value_1 - 1],
						arena->field, position +
						((args->value_2 + args->value_3) % IDX_MOD), 4);
	}
}

void		op_load_indexes(t_cursor *cursor, t_arena *arena, t_args *args,
			int position)
{
	int		value;

	if (check_register_values(args, 0, 0, 3) == FALSE)
		return ;
	cursor->jump = 2 + args->size_1 + args->size_2 + args->size_3;
	op_helper(args, position, arena, cursor);
	value = args->value_1 + args->value_2;
	if (cursor->opcode == 10)
		value = value % IDX_MOD;
	cursor->registry[args->value_3 - 1] =
		ustr_to_int(arena->field, position + value, 4);
}

void		op_load(t_cursor *cursor, t_arena *arena, t_args *args,
			int position)
{
	if (check_register_values(args, 0, 2, 0) == FALSE)
		return ;
	cursor->jump = 2 + args->size_1 + args->size_2 + args->size_3;
	if (args->size_1 == SIZE_LDIR)
		cursor->registry[args->value_2 - 1] = args->value_1;
	else if (args->size_1 == SIZE_IND)
	{
		if (cursor->opcode == 2)
			args->value_1 = args->value_1 % IDX_MOD;
		position = position + args->value_1;
		position = ustr_to_int(arena->field, position, 4);
		cursor->registry[args->value_2 - 1] = position;
	}
	cursor->carry = cursor->registry[args->value_2 - 1] ? 0 : 1;
}