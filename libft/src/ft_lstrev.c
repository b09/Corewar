/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstrev.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 09:16:00 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/09/18 13:40:05 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstrev(t_list **alst)
{
	t_list	*curr;
	t_list	*tmp;

	if (!alst || !(*alst))
		return (NULL);
	curr = ft_lstdequeue(alst);
	curr->next = NULL;
	while (*alst)
	{
		tmp = ft_lstdequeue(alst);
		tmp->next = curr;
		curr = tmp;
	}
	return (curr);
}
