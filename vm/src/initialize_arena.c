/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_arena.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/06 21:58:58 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	BELOW NOTES TAKEN FROM COOKBOOK:
**	Cursors are added to the beginning of the list. This means the cursor of the
**	last player (with the biggest id) will be executed first.
**	All registries excepting r1 are initialised with 0. r1 is initialised with
**	the negated player id (r1 = -player_id).
*/

static void		initialize_cursors(t_arena *arena)
{
	int			i;
	t_cursor	*cursor;
	t_cursor	*tail;

	i = arena->num_champs;
	while (i)
	{
		cursor = (t_cursor*)ft_memalloc(sizeof(t_cursor));
		ft_bzero(cursor, sizeof(int) * 16);
		cursor->registry[0] = -1 * i;
		cursor->position = (MEM_SIZE / arena->num_champs) * (i - 1);
		if (arena->cursor_head == NULL)
			arena->cursor_head = cursor;
		else
			tail->next = cursor;
		tail = cursor;
		--i;
	}
}

static void		cursor_wait_cycle(int *wait_cycle_arr)
{
	wait_cycle_arr[0] = 10;
	wait_cycle_arr[1] = 5;
	wait_cycle_arr[2] = 5;
	wait_cycle_arr[3] = 10;
	wait_cycle_arr[4] = 10;
	wait_cycle_arr[5] = 6;
	wait_cycle_arr[6] = 6;
	wait_cycle_arr[7] = 6;
	wait_cycle_arr[8] = 20;
	wait_cycle_arr[9] = 25;
	wait_cycle_arr[10] = 25;
	wait_cycle_arr[11] = 800;
	wait_cycle_arr[12] = 10;
	wait_cycle_arr[13] = 50;
	wait_cycle_arr[14] = 1000;
	wait_cycle_arr[15] = 2;
}

void			initialize_arena(t_arena *arena)
{
	int			i;
	t_champ 	*champ;

	i = 0;
	champ = NULL;
	arena->field = (unsigned char *)ft_memalloc(MEM_SIZE);
	cursor_wait_cycle(arena->wait_cycle_arr);
	while (i < arena->num_champs)
	{
		champ = arena->champs[i];
		ft_memcpy(&arena->field[MEM_SIZE / arena->num_champs * i],\
		champ->exec_code, champ->real_exec_size);
		++i;
	}
	initialize_cursors(arena);
	arena->latest_champ_alive = arena->cursor_head->id;
	arena->max_checks = CYCLE_TO_DIE;
	arena->num_cursors = arena->num_champs;
}
