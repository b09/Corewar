/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 15:14:06 by bprado        #+#    #+#                 */
/*   Updated: 2019/01/29 16:58:50 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;

	i = 0;
	while (dst[i] && i < size)
		++i;
	j = i;
	if (!size)
		return (i + ft_strlen(src));
	while ((src[i - j] != 0) && ((size - 1) > i))
	{
		dst[i] = src[i - j];
		++i;
	}
	if (j < size)
		dst[i] = 0;
	return (j + ft_strlen(src));
}
