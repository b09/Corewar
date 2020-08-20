/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlldequeue.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl...>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/26 16:06:56 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/06/26 16:06:56 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dll	*ft_dlldequeue(t_dll **alst)
{
	t_dll	*node;

	node = *alst;
	(*alst) = node->next;
	return (node);
}
