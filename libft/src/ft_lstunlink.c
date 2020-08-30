/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstunlink.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/13 20:41:10 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/02/13 20:41:14 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstunlink(t_list **head_node, t_list *to_unlink)
{
	t_list	*previous;

	if (*head_node == to_unlink)
		return (ft_lstdequeue(head_node));
	previous = *head_node;
	while (previous->next != to_unlink)
		previous = previous->next;
	previous->next = to_unlink->next;
	return (to_unlink);
}
