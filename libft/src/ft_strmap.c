/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/20 16:42:51 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/20 17:06:36 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*map;

	map = (char *)malloc(ft_strlen(s) + 1);
	if (map == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		map[i] = f(s[i]);
		i++;
	}
	map[i] = '\0';
	return (map);
}
