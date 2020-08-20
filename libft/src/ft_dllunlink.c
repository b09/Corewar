/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dllunlink.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl...>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/26 15:16:50 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/06/26 15:16:51 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dll	*ft_dllunlink(t_dll *node)
{
	(node->previous)->next = node->next;
	(node->next)->previous = node->previous;
	return (node);
}
