/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/15 15:36:19 by bprado        #+#    #+#                 */
/*   Updated: 2019/01/15 17:21:58 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst > src)
		ft_memrcpy(dst, src, len);
	else if (dst < src)
		ft_memcpy(dst, src, len);
	return (dst);
}
