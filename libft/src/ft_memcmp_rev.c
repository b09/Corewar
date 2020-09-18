/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp_rev.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/03 17:12:54 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_memcmp_rev(const void *s1, const void *s2_will_b_rev,\
																size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2_will_b_rev;
	if (n == 0)
		return (0);
	while (n - 1 > 0 && *str1 == str2[n - 1])
	{
		str1++;
		n--;
	}
	return (*str1 - str2[n - 1]);
}