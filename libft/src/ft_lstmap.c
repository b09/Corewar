/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/23 19:22:25 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/25 13:15:58 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*nxt;
	t_list	*map;

	map = f(lst);
	nxt = lst->next;
	if (nxt != NULL)
		map->next = ft_lstmap(nxt, f);
	return (map);
}
