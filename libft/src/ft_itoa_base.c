/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: exam <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/19 13:03:20 by exam          #+#    #+#                 */
/*   Updated: 2019/03/19 13:03:21 by exam          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_size(int value, int base)
{
	int	size;

	size = value < 0 && base == 10 ? 2 : 1;
	if (value == 0)
		size++;
	while (value)
	{
		value /= base;
		size++;
	}
	return (size);
}

static char		*populate_str(char *dst, int value, int base, int index)
{
	int	mod;

	while (value)
	{
		mod = value % base;
		dst[index] = mod < 10 ? mod + '0' : mod - 10 + 'A';
		index--;
		value /= base;
	}
	return (dst);
}

char			*ft_itoa_base(int value, int base)
{
	char	*result;
	int		mod;
	int		i;

	i = get_size(value, base);
	result = (char *)malloc(sizeof(char) * i);
	result[i - 1] = '\0';
	i -= 2;
	if (value < 0)
	{
		if (base == 10)
			result[0] = '-';
		mod = -(value % base);
		result[i] = mod < 10 ? mod + '0' : mod - 10 + 'A';
		i--;
		value /= -base;
	}
	else if (value == 0)
		result[0] = '0';
	result = populate_str(result, value, base, i);
	return (result);
}
