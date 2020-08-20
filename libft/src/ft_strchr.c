/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/19 18:13:03 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/19 18:18:56 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	if (c == '\0')
		return ((char *)&s[len]);
	return (ft_memchr(s, c, len));
}
