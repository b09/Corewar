/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_slow_memchr.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/26 19:00:49 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/02/26 19:00:50 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_slow_memchr(const void *s, int c, size_t n)
{
	unsigned char	*b;

	b = (unsigned char*)s;
	while (n > 0)
	{
		if (*b == (unsigned char)c)
			return (b);
		b++;
		n--;
	}
	return (NULL);
}
