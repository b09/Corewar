/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/13 17:52:27 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/19 15:11:43 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void				memcpy_unrolled(unsigned long **dst,\
						unsigned long **src, size_t len)
{
	while (len > 0)
	{
		(*dst)[0] = (*src)[0];
		(*dst)[1] = (*src)[1];
		(*dst)[2] = (*src)[2];
		(*dst)[3] = (*src)[3];
		*dst += 4;
		*src += 4;
		len--;
	}
}

static unsigned long	memcpy_wordcpy(\
	unsigned long **dst, unsigned long **src, size_t n)
{
	size_t	temp_len;

	temp_len = n / (sizeof(unsigned long) * 4);
	n %= sizeof(unsigned long) * 4;
	memcpy_unrolled(dst, src, temp_len);
	temp_len = n / (sizeof(unsigned long));
	while (temp_len > 0)
	{
		(*dst)[0] = (*src)[0];
		(*dst)++;
		(*src)++;
		temp_len--;
	}
	n %= sizeof(unsigned long);
	return (n);
}

void					*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dest;
	unsigned char	*source;

	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (n >= sizeof(unsigned long) * 4)
	{
		while (((unsigned long)source & (sizeof(unsigned long) - 1)) != 0)
		{
			*dest = *source;
			dest++;
			source++;
			n--;
		}
		n = memcpy_wordcpy((unsigned long **)&dest, \
							(unsigned long **)&source, n);
	}
	while (n > 0)
	{
		*dest = *source;
		dest++;
		source++;
		n--;
	}
	return (dst);
}
