/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlldel.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl...>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/26 16:01:20 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/06/26 16:01:20 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlldel(t_dll **alst, void (*del)(void *, size_t))
{
	t_dll	*nxt;
	t_dll	*cur;

	cur = *alst;
	while (cur != NULL)
	{
		nxt = cur->next;
		ft_dlldelone(&cur, del);
		cur = nxt;
	}
	*alst = NULL;
}
