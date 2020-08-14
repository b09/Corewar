/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 17:54:16 by bprado        #+#    #+#                 */
/*   Updated: 2019/01/22 18:11:38 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	char	*c;

	if (!s)
		return (NULL);
	while ((*s == '\t') || (*s == ' ') || (*s == '\n'))
		s++;
	if (!*s)
	{
		c = (char*)malloc((sizeof(char)));
		if (!c)
			return (NULL);
		c[0] = 0;
		return (c);
	}
	i = ft_strlen(s);
	while ((s[i - 1] == '\t') || (s[i - 1] == ' ') || (s[i - 1] == '\n'))
		--i;
	c = (char*)ft_memalloc(sizeof(char) * (i + 1));
	if (!c)
		return (NULL);
	ft_strncpy(c, s, i);
	return (c);
}
