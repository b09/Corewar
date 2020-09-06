/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   battle.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/06 22:02:26 by macbook       ########   odam.nl         */
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

//		FROM PROJECT PDF
// - Every CYCLE_TO_DIE cycles, the machine needs to make sure that each process
// has executed at least one live since the last check. A process that does not
// abide by this rule will be killed immediately
// - If during one of those checkups we notice that there has been at least one
// NBR_LIVE execution of live since the latest check up, we will decrease
// CYCLE_TO_DIE of CYCLE_DELTA units. 
// - The game is over when all processes are dead.
// - The winner is the last player to be reported alive. The machine will then
// show “Player X (champion_name) won”, where X is the player’s number and cham-
// pion_name is its name. For example: “Player 2 (rainbowdash) won”.
// - If CYCLE_TO_DIE wasn’t decreased since MAX_CHECKS checkups, decrease it.

void			battle(t_arena *arena)
{
	t_func		arrpointer[16];
	t_cursor	*cursor;

	populate_operation_array(arrpointer);
	while(42)
	{
		if (arena->cycles == arena->dump)
			print_hexdump(arena);
		cursor = arena->cursor_head;
		while(cursor)
		{
			cursor->wait_cycle -= cursor->wait_cycle ? cursor->wait_cycle : 0;
			if (cursor->wait_cycle == 0)
				arrpointer[cursor->opcode - 1](cursor, arena);
			// go to next byte location in arena
			// set cursor->opcode
			cursor->wait_cycle = arena->wait_cycle_arr[cursor->opcode - 1];
		}
		(arena->cycles_to_die)++;
		(arena->cycles)++;
	}
}