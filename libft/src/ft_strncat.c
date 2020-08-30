/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/13 15:10:39 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/16 16:37:56 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	len_s1;

	len_s1 = ft_strlen(s1);
	n = ft_min(ft_strlen(s2), n);
	ft_memcpy(&s1[len_s1], s2, n);
	s1[len_s1 + n] = '\0';
	return (s1);
}
