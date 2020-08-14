/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 14:46:53 by bprado        #+#    #+#                 */
/*   Updated: 2019/01/16 14:56:53 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (s1[i] != 0)
		++i;
	while ((s2[j] != 0) && (n > 0))
	{
		s1[i] = s2[j];
		i++;
		j++;
		n--;
	}
	s1[i] = 0;
	return (s1);
}
