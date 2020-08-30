/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dllappend.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl...>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/26 15:13:21 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/06/26 15:13:22 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dllappend(t_dll **alst, t_dll *new)
{
	t_dll	*current;

	current = *alst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	new->previous = current;
}
