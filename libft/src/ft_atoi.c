/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 17:45:12 by bprado        #+#    #+#                 */
/*   Updated: 2020/06/07 18:45:38 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	long long int	i;
	int				j;

	i = 0;
	j = 1;
	while ((*str > 0) && (*str < 33) && (*str != 27))
		++str;
	if ((*str == 43) || (*str == 45))
	{
		if (*str == 45)
		{
			j = -j;
		}
		++str;
	}
	while ((*str > 47) && (*str < 58))
	{
		i = (i * 10) + (*str - 48);
		++str;
	}
	return ((int)i * j);
}
