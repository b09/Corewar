/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strequ.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 17:50:42 by bprado        #+#    #+#                 */
/*   Updated: 2019/01/21 18:02:53 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	int i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	if ((s1[i] == s2[i]) && (s1[i] == 0))
		return (1);
	while (s1[i] == s2[i] && (s1[i] != 0))
	{
		++i;
		if ((s1[i] == s2[i]) && (s1[i] == 0))
			return (1);
	}
	return (0);
}
