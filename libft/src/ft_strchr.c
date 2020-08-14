/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 17:49:51 by bprado        #+#    #+#                 */
/*   Updated: 2019/11/14 15:22:30 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != 0)
	{
		if (*s == (unsigned char)c)
			return ((char*)s);
		s++;
	}
	if (c == 0)
		return ((char*)s);
	return (NULL);
}
