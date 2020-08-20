/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlldelone.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl...>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/26 16:03:23 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/06/26 16:03:24 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlldelone(t_dll **alst, void (*del)(void *, size_t))
{
	t_dll	*lst;

	lst = *alst;
	del(lst->content, lst->content_size);
	free(lst);
	*alst = NULL;
}
