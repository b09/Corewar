/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/13 18:26:55 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/25 12:56:00 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*source;
	unsigned char	*dest;

	if (src > dst)
		ft_memcpy(dst, src, len);
	else
	{
		source = (unsigned char *)src;
		dest = (unsigned char *)dst;
		while (len > 0)
		{
			dest[len - 1] = source[len - 1];
			len--;
		}
	}
	return (dst);
}
