/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstappend.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/23 19:38:30 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/24 12:32:32 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstappend(t_list **alst, t_list *new)
{
	t_list	*current;

	current = *alst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}
