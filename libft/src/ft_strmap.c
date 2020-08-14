/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 17:52:03 by bprado        #+#    #+#                 */
/*   Updated: 2019/01/25 18:08:20 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*cpy;

	i = 0;
	if (!s || !f)
		return (NULL);
	cpy = (char*)malloc(ft_strlen(s) + 1);
	if (!cpy)
		return (NULL);
	while (s[i] != 0)
	{
		cpy[i] = f(s[i]);
		++i;
	}
	cpy[i] = 0;
	return (cpy);
}
