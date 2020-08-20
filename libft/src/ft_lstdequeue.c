/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdequeue.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/11 16:28:40 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/02/11 16:28:42 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstdequeue(t_list **alst)
{
	t_list	*node_to_dequeue;

	node_to_dequeue = *alst;
	(*alst) = node_to_dequeue->next;
	return (node_to_dequeue);
}
