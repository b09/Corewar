/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_range.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 16:39:59 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/12 14:20:14 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_range(int min, int max)
{
	int	*range;
	int i;
	int len;

	if (min >= max)
		return (NULL);
	len = max - min;
	range = (int *)malloc(sizeof(int) * len);
	i = 0;
	while (i < len)
	{
		range[i] = min + i;
		i++;
	}
	return (range);
}
