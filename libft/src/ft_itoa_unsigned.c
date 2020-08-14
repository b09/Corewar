/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_unsigned.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 18:11:44 by bprado        #+#    #+#                 */
/*   Updated: 2020/06/07 18:51:36 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_itoa2_unsigned(char *str, unsigned long long holder, int i)
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

char			*ft_itoa_unsigned(unsigned long long nbr, char negative)
{
	int					i;
	char				*str;
	unsigned long long	holder;

	holder = nbr;
	i = 1;
	while (holder > 9)
	{
		holder /= 10;
		++i;
	}
	holder = nbr;
	str = (char*)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i] = 0;
	if (negative)
		str[0] = '-';
	return (ft_itoa2_unsigned(str, holder, i));
}
