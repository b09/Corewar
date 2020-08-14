/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnequ.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 17:53:10 by bprado        #+#    #+#                 */
/*   Updated: 2019/01/25 17:15:30 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (!s1 || !s2)
		return (0);
	if (n == 0)
		return (1);
	while ((*s1 == *s2) && (n != 0))
	{
		++s1;
		++s2;
		--n;
		if ((*s1 == *s2 && *s1 == 0) || (*(s1 - 1) == *(s2 - 1) && (n == 0)))
			return (1);
	}
	return (0);
}
