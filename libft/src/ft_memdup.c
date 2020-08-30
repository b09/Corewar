/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/23 16:55:42 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/23 17:01:27 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memdup(char const *b, size_t n)
{
	char	*arr;

	arr = (char *)malloc(n);
	if (arr == NULL)
		return (NULL);
	ft_memcpy(arr, b, n);
	return (arr);
}
