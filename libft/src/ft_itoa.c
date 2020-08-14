/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 17:46:11 by bprado        #+#    #+#                 */
/*   Updated: 2020/06/07 18:50:53 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_itoa2(char *str, long long holder, int i)
{
	if (holder == 0)
	{
		str[0] = '0';
		return (str);
	}
	while (holder > 0)
	{
		str[i - 1] = ((holder % 10) + '0');
		holder /= 10;
		i--;
	}
	return (str);
}

char			*ft_itoa(long long nbr)
{
	int			i;
	char		*str;
	long long	holder;

	holder = nbr;
	i = 1;
	while (holder > 9 || holder < -9)
	{
		holder /= 10;
		++i;
	}
	if (nbr < 0)
		++i;
	holder = nbr;
	(nbr < 0) ? (holder = -holder) : (nbr);
	str = (char*)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i] = 0;
	if (nbr < 0)
		str[0] = '-';
	return (ft_itoa2(str, holder, i));
}
