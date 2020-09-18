/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ops_half_two.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/18 17:50:49 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_forks_jump(t_cursor *cursor, t_arena *arena, t_args *args,
			int pos)
{
	int		val;

	(void)args;
	if (cursor->opcode == 9)
	{
		val = 3;
		if (cursor->carry)
			val = ustr_to_int(arena->field, (pos + 1) % MEM_SIZE, 2);
		cursor->jump = val % IDX_MOD;
		return ;
	}
	cursor->jump = 3;
	create_cursor(arena, cursor->id, FALSE);
	val = ustr_to_int(arena->field, pos + 1, 2);
	if (cursor->opcode == 15)
		arena->cursor_head->position = ((pos + val) % MEM_SIZE);
	else
		arena->cursor_head->position = ((pos + (val % IDX_MOD)) % MEM_SIZE);
	arena->num_cursors++;
}

void		op_math(t_cursor *cursor, t_arena *arena, t_args *args,
			int position)
{
	if ((cursor->opcode > 5 && check_register_values(args, 0, 0, 3) == FALSE) ||
		(cursor->opcode <= 5 && check_register_values(args, 1, 2, 3) == FALSE))
		return ;
	cursor->jump = 2 + args->size_1 + args->size_2 + args->size_3;
	op_helper(args, position, arena, cursor);
	if (cursor->opcode == 4)
		cursor->registry[args->value_3 - 1] = args->value_1 + args->value_2;
	else if (cursor->opcode == 5)
		cursor->registry[args->value_3 - 1] = args->value_1 - args->value_2;
	else if (cursor->opcode == 6)
		cursor->registry[args->value_3 - 1] = args->value_1 & args->value_2;
	else if (cursor->opcode == 7)
		cursor->registry[args->value_3 - 1] = args->value_1 | args->value_2;
	else if (cursor->opcode == 8)
		cursor->registry[args->value_3 - 1] = args->value_1 ^ args->value_2;
	cursor->carry = cursor->registry[args->value_3 - 1] == 0 ? TRUE : FALSE;
}

void		op_live(t_cursor *cursor, t_arena *arena, t_args *args,
			int position)
{
	int		value;

	(void)args;
	value = ustr_to_int(arena->field, position + 1, 4);
	cursor->last_live = arena->cycles;
	cursor->jump = 5;
	arena->num_lives++;
	if (value > 0 && value <= arena->num_champs &&
		value + cursor->registry[0] == 0)
	{
		ft_printf("A process shows that player %d (%s) is alive.\n",
		value, arena->champs[value - 1]->name);
		arena->last_champ_alive = cursor->registry[0] * -1;
	}
}

void		op_aff(t_cursor *cursor, t_arena *arena, t_args *args,
			int position)
{
	(void)position;
	(void)arena;
	if (check_register_values(args, 1, 0, 0) == FALSE)
		return ;
	cursor->jump = 2 + args->size_1 + args->size_2 + args->size_3;
	ft_printf("%c", cursor->registry[args->value_1 - 1] % 256);
}
