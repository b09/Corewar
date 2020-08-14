/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr_int.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/08 14:09:43 by bprado        #+#    #+#                 */
/*   Updated: 2019/12/11 22:00:04 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t		ft_strrchr_int(const char *s, int c)
{
	ssize_t		i;
	ssize_t		x;

	i = 0;
	x = -1;
	while (s[i] != 0)
	{
		if (s[i] == (unsigned char)c)
			x = i;
		i++;
	}
	if (c == 0 && s[i] == 0)
		x = i;
	return (x);
}
