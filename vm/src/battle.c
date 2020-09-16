/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   battle.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/16 17:44:58 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	array of function pointers to the operations allowed for use in championship
*/

static void			populate_operation_array(t_func arrpointer[16])
{
	arrpointer[0] = op_live;
	arrpointer[1] = op_ld;
	arrpointer[2] = op_st;
	arrpointer[3] = op_add;
	arrpointer[4] = op_sub;
	arrpointer[5] = op_and;
	arrpointer[6] = op_or;
	arrpointer[7] = op_xor;
	arrpointer[8] = op_zjmp;
	arrpointer[9] = op_ldi;
	arrpointer[10] = op_sti;
	arrpointer[11] = op_fork;
	arrpointer[12] = op_lld;
	arrpointer[13] = op_lldi;
	arrpointer[14] = op_lfork;
	arrpointer[15] = op_aff;
}

/*
**	iterates through all cursors, checking if the difference between the
**	cursor's last 'live' operation was more than max_cycle_die's ago.
**	unlinks all cursors where above statement is true.
**
*/

static void			check_cursors(t_arena *arena)
{
	t_cursor		*cursor;

	cursor = arena->cursor_head;
	while (cursor)
	{
		if ((arena->cycles - arena->max_cycle_die) >= cursor->last_live)
		{
			cursor_unlink_del(arena, cursor);
			cursor = arena->cursor_head;
			if (cursor == NULL)
				print_winner(arena); // finish writting func
		}
		else
			cursor = cursor->next;
	}
	if (arena->num_checks >= MAX_CHECKS || arena->num_lives >= NBR_LIVE)
	{
		arena->max_cycle_die -= CYCLE_DELTA;
		arena->num_checks = 0;
		return ;
	}
	ft_bzero(arena->alive_champs_arr, sizeof(int) * 4);
	arena->cycles_to_die = 0;
	arena->num_lives = 0;
	arena->num_checks++;
}

static int		is_opcode(int opcode)
{
	if (opcode >= 1 && opcode <= 16)
		return (TRUE);
	return (FALSE);
}

static void			execute_operation(t_arena *arena, t_cursor *cursor,\
					t_func arrpointer[16])
{
	t_args	args;

	ft_printf("func:%s line:%d opcode: %d\n", __func__, __LINE__, cursor->opcode);
	if (is_opcode(cursor->opcode))
		arrpointer[cursor->opcode - 1](cursor, arena, &args,\
				cursor->position % MEM_SIZE);
}

/*
**	each cursor will have an operation which will cost a number of cycles to do.
**	if the number of cycles completed is sufficient, execute the operation.
**
*/

//		FROM PROJECT PDF
// - Every CYCLE_TO_DIE cycles, the machine needs to make sure that each process
// has executed at least one live since the last check. A process that does not
// abide by this rule will be killed immediately
// - If during one of those checkups we notice that there has been at least one
// NBR_LIVE execution of live since the latest check up, we will decrease
// CYCLE_TO_DIE of CYCLE_DELTA units.
// - If CYCLE_TO_DIE wasn’t decreased since MAX_CHECKS checkups, decrease it.
// - The game is over when all processes are dead.
// - The winner is the last player to be reported alive. The machine will then
// show “Player X (champion_name) won”, where X is the player’s number and cham-
// pion_name is its name. For example: “Player 2 (rainbowdash) won”.

void				battle(t_arena *arena, t_func arrpointer[16],\
					t_cursor *cursor)
{
	t_func			arrpointer1[16];
	int				i;//delete

	i = 0; //delte

	populate_operation_array(arrpointer1);
	while (42)
	{
		if (arena->cycles_to_die == arena->max_cycle_die)
			check_cursors(arena);
		cursor = arena->cursor_head;
		while (cursor)
		{
			cursor->wait_cycle -= cursor->wait_cycle ? 1 : 0;
			if (cursor->wait_cycle == 0)
			{
				// ft_printf("****** cursor id: %d *******\n", cursor->id);
				// ft_printf("opcode:%d\n", cursor->opcode);
				// ft_printf("cursor pos:%x\n\n", arena->field[cursor->position % MEM_SIZE]);
				// i++; // delete



				execute_operation(arena, cursor, arrpointer1);
				cursor->position = (cursor->position + cursor->jump) % MEM_SIZE;
				cursor->opcode = arena->field[cursor->position];
				cursor->wait_cycle = is_opcode(cursor->opcode) ? arena->wait_cycle_arr[cursor->opcode - 1] : 0;
				cursor->jump = 1;
			}
			cursor = cursor->next;
			// i++; // delete
			if (i == 50) // delte
				exit(1); // delete



		}
		(arena->cycles_to_die)++;
		(arena->cycles)++;
	}
}
