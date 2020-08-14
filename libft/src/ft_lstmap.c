/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/04 16:51:28 by bprado        #+#    #+#                 */
/*   Updated: 2019/02/04 16:51:29 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*ptr;

	if (lst)
	{
		ptr = (t_list *)malloc(sizeof(*ptr));
		if (!ptr)
			return (NULL);
		ptr = f(lst);
		ptr->next = ft_lstmap(lst->next, f);
		return (ptr);
	}
	return (NULL);
}
