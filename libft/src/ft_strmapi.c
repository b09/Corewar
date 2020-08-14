/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 17:52:13 by bprado        #+#    #+#                 */
/*   Updated: 2019/01/25 18:08:03 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*a;

	i = 0;
	if (!s || !f)
		return (NULL);
	a = (char*)malloc(ft_strlen(s) + 1);
	if (!a)
		return (NULL);
	while (s[i] != 0)
	{
		a[i] = f(i, s[i]);
		++i;
	}
	a[i] = 0;
	return (a);
}
