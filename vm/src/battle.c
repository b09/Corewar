/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   battle.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/07 17:19:17 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		populate_operation_array(t_func arrpointer[128])
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

void		cull_cursor(t_arena *arena)
{
	
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

void			battle(t_arena *arena)
{
	t_func		arrpointer[16];
	t_cursor	*cursor;

	populate_operation_array(arrpointer);
	while(42)
	{
		arena->cycles == arena->dump && print_hexdump(arena);
		if (arena->cycles_to_die == arena->max_cycle_die)
			// loop thru && kill cursors if last_alive is >= max allowed alive
			// decrease max_cycle_die by CYCLE_DELTA(50) if num_lives >= NBR_LIVES
			// or if num_checks == MAX_CHECKS(10)
				// reset num_checks if above true;
			// reset num_lives
		cursor = arena->cursor_head;
		while(cursor)
		{
			cursor->wait_cycle -= cursor->wait_cycle ? 1 : 0;
			if (cursor->wait_cycle == 0)
			{
				arrpointer[cursor->opcode - 1](cursor, arena);
				cursor->position = (cursor->position + cursor->jump) % MEM_SIZE;
				cursor->opcode = arena->field[cursor->position];
				cursor->wait_cycle = arena->wait_cycle_arr[cursor->opcode - 1];
				cursor->jump = 1;
			}
			cursor->next;
		}
		(arena->cycles_to_die)++;
		(arena->cycles)++;
	}
}