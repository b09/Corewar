/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memalloc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/20 16:24:46 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/20 17:01:19 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned char	*arr;

	arr = (unsigned char *)malloc(size);
	if (arr == NULL)
		return (NULL);
	ft_bzero(arr, size);
	return (arr);
}
