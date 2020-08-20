/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/13 14:18:24 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/16 19:27:45 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	len_src;

	len_src = ft_strlen(src);
	ft_memcpy(dst, src, ft_min(len_src + 1, len));
	if (len_src < len)
		ft_bzero(&dst[len_src], len - len_src);
	return (dst);
}
