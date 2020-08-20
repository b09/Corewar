/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/13 17:57:53 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/02/02 16:45:44 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*stop_addres;

	if (n == 0)
		return (NULL);
	stop_addres = (unsigned char *)ft_memchr(src, c, n);
	if (stop_addres != NULL)
	{
		ft_memcpy(dst, src, stop_addres - (unsigned char *)src + 1);
		return (dst + (stop_addres - (unsigned char *)src + 1));
	}
	ft_memcpy(dst, src, n);
	return (NULL);
}
