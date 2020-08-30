/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/13 17:21:44 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/22 20:48:01 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	len_src;
	unsigned int	len_dst;
	int				n;

	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	n = ft_min(size - len_dst - 1, len_src);
	if (n > 0)
	{
		ft_memcpy(&dst[len_dst], src, n);
		dst[len_src + len_dst < (unsigned int)size ?\
			len_src + len_dst : size - 1] = '\0';
	}
	return (size <= (unsigned long)len_dst ?
		size + len_src : len_src + len_dst);
}
