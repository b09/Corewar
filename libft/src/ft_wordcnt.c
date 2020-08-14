/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_wordcnt.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/03 20:32:28 by bprado        #+#    #+#                 */
/*   Updated: 2019/02/03 20:33:27 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_wordcnt(char const *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	if (s[i] != 0)
		j = 1;
	while (s[i] != 0)
	{
		++i;
		if (((s[i] == c) && (s[i - 1] != c) && (s[i + 1] != 0)))
			++j;
	}
	if ((s[ft_strlen(s) - 1] == c) && (s[ft_strlen(s) - 2] == c))
		--j;
	return (j);
}
