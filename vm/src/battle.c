/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   battle.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/19 16:58:19 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	array of function pointers to the operations allowed for use in championship
*/

static void			populate_operation_array(t_func arrpointer[16])
{
	arrpointer[0] = op_live;
	arrpointer[1] = op_load;
	arrpointer[2] = op_st;
	arrpointer[3] = op_math;
	arrpointer[4] = op_math;
	arrpointer[5] = op_math;
	arrpointer[6] = op_math;
	arrpointer[7] = op_math;
	arrpointer[8] = op_forks_jump;
	arrpointer[9] = op_load_indexes;
	arrpointer[10] = op_sti;
	arrpointer[11] = op_forks_jump;
	arrpointer[12] = op_load;
	arrpointer[13] = op_load_indexes;
	arrpointer[14] = op_forks_jump;
	arrpointer[15] = op_aff;
}

/*
**	iterates through all cursors, checking if the difference between the
**	cursor's last 'live' operation was more than max_cycle_die's ago.
**	unlinks all cursors where above statement is true.
**	arena->num_checks = -1; because num_check will increase to zero later on
*/

static void			check_cursors(t_arena *arena, t_cursor *cursor)
{
	if (cursor == NULL)
		print_winner(arena);
	while (cursor)
	{
		if ((arena->cycles - arena->max_cycle_die) >= cursor->last_live)
		{
			cursor_unlink_del(arena, cursor);
			cursor = arena->cursor_head;
			if (cursor == NULL)
				print_winner(arena);
		}
		else
			cursor = cursor->next;
	}
	if (arena->num_checks >= MAX_CHECKS || arena->num_lives >= NBR_LIVE)
	{
		arena->max_cycle_die -= CYCLE_DELTA;
		if (arena->max_cycle_die < 0)
			print_winner(arena);
		arena->num_checks = -1;
	}
	arena->cycles_to_die = 0;
	arena->num_lives = 0;
	arena->num_checks++;
}

static void			execute_operation(t_arena *arena, t_cursor *cursor,\
					t_func arrpointer[16])
{
	t_args			args;
	int				num;

	num = (cursor->opcode == 11 || cursor->opcode == 14 ||
		cursor->opcode == 10) ? 1 : 0;
	if (cursor->opcode >= 1 && cursor->opcode <= 16)
	{
		ft_printf("id: %d op: %d\n", cursor->id, cursor->opcode);
		populate_argmnts(arena->field, cursor->position % MEM_SIZE, &args, num);
		arrpointer[cursor->opcode - 1](cursor, arena,
										&args, cursor->position % MEM_SIZE);
	}
	cursor->position = pos_mem_size(cursor->position + cursor->jump);
	cursor->opcode = arena->field[cursor->position];
	if (cursor->opcode >= 1 && cursor->opcode <= 16)
		cursor->wait_cycle = arena->wait_cycle_arr[cursor->opcode - 1];
	else
		cursor->wait_cycle = 0;
	cursor->jump = 1;
}

/*
**	each cursor will have an operation which will cost a number of cycles to do.
**	if the number of cycles completed is sufficient, execute the operation.
**
**		FROM PROJECT PDF
** - Every CYCLE_TO_DIE cycles, the machine needs to make sure that each process
** has executed at least one live since the last check. A process that does not
** abide by this rule will be killed immediately
** - If during one of those checkups we notice that there has been at least one
** NBR_LIVE execution of live since the latest check up, we will decrease
** CYCLE_TO_DIE of CYCLE_DELTA units.
** - If CYCLE_TO_DIE wasn’t decreased since MAX_CHECKS checkups, decrease it.
** - The game is over when all processes are dead.
** - The winner is the last player to be reported alive. The machine will then
** show “Player X (champion_name) won”, where X is the player’s number and cham-
** pion_name is its name. For example: “Player 2 (rainbowdash) won”.
*/

void				battle(t_arena *arena, t_func arrpointer[16],\
					t_cursor *cursor)
{
	populate_operation_array(arrpointer);
	while (42)
	{
		if (arena->cycles == arena->dump)
			print_hexdump(arena, 0);
		if (arena->cycles_to_die >= arena->max_cycle_die)
			check_cursors(arena, arena->cursor_head);
		cursor = arena->cursor_head;
		while (cursor)
		{
			cursor->wait_cycle -= cursor->wait_cycle ? 1 : 0;
			if (cursor->wait_cycle == 0)
				execute_operation(arena, cursor, arrpointer);
			cursor = cursor->next;
		}
		(arena->cycles_to_die)++;
		(arena->cycles)++;
	}
}
