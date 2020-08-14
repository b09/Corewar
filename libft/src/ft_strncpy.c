/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/15 17:38:18 by bprado        #+#    #+#                 */
/*   Updated: 2019/01/23 21:23:42 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	int i;

	i = 0;
	while ((len) && (src[i] != 0))
	{
		dst[i] = src[i];
		--len;
		++i;
	}
	while (len)
	{
		dst[i] = 0;
		--len;
		++i;
	}
	return (dst);
}
