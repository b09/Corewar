/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   delete.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/07 20:09:03 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	cursor_unlink_del(t_arena *arena, t_cursor *cursor)
{
	if (cursor == arena->cursor_head)
	{
		arena->cursor_head = cursor->next;
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

void	token_lst_del(t_cursor *head)
{
	t_cursor *current;
	t_cursor *next;

	current = head;
	while (current)
	{
		next = current->next;
		free((void*)current);
		current = next;
	}
}
