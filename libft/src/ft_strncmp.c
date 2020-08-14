/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 17:52:21 by bprado        #+#    #+#                 */
/*   Updated: 2019/01/20 17:53:17 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!n)
		return (0);
	while (n && (*s1 == *s2) && *s1 && *s2)
	{
		--n;
		++s1;
		++s2;
		if (!n)
		{
			--s1;
			--s2;
			return (*(unsigned char*)s1 - *(unsigned char*)s2);
		}
	}
	return (*(unsigned char*)s1 - *(unsigned char*)s2);
}
