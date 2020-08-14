/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 17:51:21 by bprado        #+#    #+#                 */
/*   Updated: 2019/12/13 18:45:09 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	int		j;
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	s3 = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s3)
		return (NULL);
	j = 0;
	while (*s1)
	{
		s3[j] = *s1;
		j++;
		s1++;
	}
	while (*s2)
	{
		s3[j] = *s2;
		j++;
		s2++;
	}
	s3[j] = 0;
	return (s3);
}
