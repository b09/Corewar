/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memrcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/06 13:13:24 by bprado        #+#    #+#                 */
/*   Updated: 2019/02/06 13:15:09 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memrcpy(void *dst, const void *src, size_t len)
{
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)dst;
	b = (unsigned char *)src;
	while (len)
	{
		a[len - 1] = b[len - 1];
		--len;
	}
	return (dst);
}
