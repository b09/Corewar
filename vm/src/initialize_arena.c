/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_arena.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/06 12:46:31 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Cursors are added to the beginning of the list. This means the cursor of the
**	last player (with the biggest id) will be executed first.
**	All registries excepting r1 are initialised with 0. r1 is initialised with
**	the negated player id (r1 = -player_id).
*/

void			initialize_cursors(t_arena *arena)
{
	int			i;
	t_cursor	*cursor;
	t_cursor	*tail;

	i = arena->num_champs;
	while (i)
	{
		cursor = (t_cursor*)ft_memalloc(sizeof(t_cursor));
		ft_bzero(&cursor, sizeof(int) * 16);
		cursor->registry[0] = -1 * i; // player id;
		//		cursor->position example
		// 		4096(MEM_SIZE) / 3 = 1365
		// player1 position 1365 * (1 - 1) = 0
		// player2 position 1365 * (2 - 1) = 1365
		// player3 position 1365 * (3 - 1) = 2730
		cursor->position = (MEM_SIZE / arena->num_champs) * (i - 1);
		if (arena->cursor_head == NULL)
			arena->cursor_head = cursor;
		else
			tail->next = cursor;
		tail = cursor;
		--i;
	}
}

void		initialize_arena(t_arena *arena)
{
	int		i;
	t_champ *champ;

	i = 0;
	champ = NULL;
	arena->field = (unsigned char *)ft_memalloc(MEM_SIZE);
	while (i < arena->num_champs)
	{
		champ = arena->champs[i];
		ft_memcpy(&arena->field[MEM_SIZE / arena->num_champs * i],\
		champ->exec_code, champ->real_exec_size);
		++i;
	}
	initialize_cursors(arena);
}

void		battle(t_arena *arena)
{
	int		i;

	while(42)
	{
		i = 0;
		while(i < arena->num_cursors)
		{
			// do something with cursors;
			++i;
		}
		(arena->cycles)++;
	}
}