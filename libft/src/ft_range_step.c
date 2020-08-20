/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_range_step.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/11 19:34:43 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/16 19:00:16 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_range_step(int min, int max, int step)
{
	int *range;
	int i;
	int	len;

	if (min >= max)
		return (NULL);
	len = (max - min) / step;
	range = (int *)malloc(sizeof(int) * len);
	i = 0;
	while (i < len)
	{
		range[i] = min + (i * step);
		i++;
	}
	return (range);
}
