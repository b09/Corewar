/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 16:23:41 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/02/02 16:29:36 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dst;
	int		len;

	len = ft_strlen(src);
	dst = ft_memdup(src, len + 1);
	if (dst == NULL)
		return (NULL);
	dst[len] = '\0';
	return (dst);
}
