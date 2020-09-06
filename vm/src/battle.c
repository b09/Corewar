/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   battle.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/06 19:25:46 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		populate_func_array(t_func arrpointer[128])
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

void			battle(t_arena *arena)
{
	// int			i;
	t_func		arrpointer[16];
	t_cursor	*cursor;

	populate_func_array(arrpointer);
	while(42)
	{
		if (arena->cycles == arena->dump)
			print_hexdump(arena);
		// i = 0;
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