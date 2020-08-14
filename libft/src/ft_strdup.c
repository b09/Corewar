/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/15 17:28:09 by bprado        #+#    #+#                 */
/*   Updated: 2019/01/15 17:38:00 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*c;
	int		i;

	i = 0;
	while (s1[i] != 0)
		++i;
	c = (char*)malloc(i + 1);
	if (!c)
		return (NULL);
	return (ft_strcpy(c, s1));
}
