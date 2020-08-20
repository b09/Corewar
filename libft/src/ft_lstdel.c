/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdel.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/24 18:22:53 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/25 17:22:06 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*nxt;
	t_list	*cur;

	cur = *alst;
	while (cur != NULL)
	{
		nxt = cur->next;
		ft_lstdelone(&cur, del);
		cur = nxt;
	}
	*alst = NULL;
}
