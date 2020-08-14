/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/14 12:22:58 by bprado        #+#    #+#                 */
/*   Updated: 2019/01/14 16:23:46 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *c, int i, size_t len)
{
	size_t			index;
	unsigned char	*a;

	if (len == 0)
		return (c);
	a = (unsigned char *)c;
	index = 0;
	while (index < len)
	{
		a[index] = (unsigned char)i;
		++index;
	}
	return (c);
}
