/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsplit.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 17:53:45 by bprado        #+#    #+#                 */
/*   Updated: 2019/01/25 17:04:53 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**make_array(char const *s, char c, char **ary)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while ((*s != 0) || (s[i] != 0))
	{
		if (*s == c)
			++s;
		while (*s != c && *s != 0)
		{
			++s;
			++i;
			if ((*s == c) || (*s == 0))
			{
				ary[j] = (char*)malloc(sizeof(char) * i + 1);
				ary[j] = ft_strncpy(ary[j], &s[-i], i);
				ary[j][i] = 0;
				++j;
			}
		}
		i = 0;
	}
	return (ary);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**ary;

	if (!s)
		return (NULL);
	ary = (char**)malloc(sizeof(char*) * ft_wordcnt(s, c) + 1);
	if (ary == NULL)
		return (NULL);
	ary[ft_wordcnt(s, c)] = 0;
	ary = make_array(s, c, ary);
	return (ary);
}
