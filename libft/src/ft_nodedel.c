/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_nodedel.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl...>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/20 18:37:32 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/06/20 18:40:14 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_nodedel(void *p, size_t n)
{
	ft_memdel(&p);
	(void)n;
}
