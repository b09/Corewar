/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/13 13:43:49 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/31 13:16:52 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	len_1;
	size_t	len_2;

	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	n = ft_min(n, ft_min(len_1, len_2) + 1);
	return (ft_memcmp(s1, s2, n));
}
