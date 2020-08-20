/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/13 13:38:44 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/22 18:27:40 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	len;

	len = ft_strlen(src);
	dst = ft_memcpy(dst, src, len + 1);
	return (dst);
}
