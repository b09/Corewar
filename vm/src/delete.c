/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   delete.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/18 13:33:25 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		cursor_unlink_del(t_arena *arena, t_cursor *cursor)
{
	if (cursor)
	{
		if (cursor == arena->cursor_head)
		{
			arena->cursor_head = cursor->next;
			if (arena->cursor_head)
				arena->cursor_head->prev = NULL;
		}
		else
		{
			cursor->prev->next = cursor->next;
			if (cursor->next)
				cursor->next->prev = cursor->prev;
		}
		free((void*)cursor);
	}
}

/*
**	1 main
**		t_champ **all_champs
**
**	2 allocate_for_champs
**		t_champ *champ X 5, last is always null
**
**	3 get_champ_file
**		champ->orig_file char *
**
**	4 initialize_arena
**		arena->field char *
**
**	5 create_cursor
**		arena->cursor_head (t_cursor*) linked list
*/

void		free_everything(t_arena *arena)
{
	int		i;
	t_champ	*champ;
	t_champ	*next;

	i = 0;
	if (arena->champs)
	{
		champ = arena->champs[i];
		while (i < 4 && champ)
		{
			++i;
			next = arena->champs[i];
			if (champ->orig_file)
				free((void*)champ->orig_file);
			free((void*)champ);
			champ = next;
		}
		if (arena->champs)
			free((void*)arena->champs);
	}
	if (arena->field)
		free((void*)arena->field);
	while (arena->cursor_head)
		cursor_unlink_del(arena, arena->cursor_head);
	exit(1);
}
