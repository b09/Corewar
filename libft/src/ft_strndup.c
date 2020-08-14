/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strndup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/09 12:43:45 by macbook       #+#    #+#                 */
/*   Updated: 2020/06/07 17:01:11 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(const char *s1, size_t n)
{
	char	*c;
	size_t	i;

	i = 0;
	while (s1[i] != 0)
		++i;
	i = i < n ? i : n;
	c = (char*)ft_memalloc(i + 1);
	if (!c)
		return (NULL);
	return (ft_strncpy(c, s1, n));
}
