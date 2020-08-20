/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sqrt_ceil.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/29 14:48:32 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/03/29 14:48:33 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt_ceil(int nb)
{
	int min;
	int max;
	int c;

	min = 1;
	max = nb;
	if (nb == 1)
		return (1);
	if (nb > 1)
	{
		while (min + 1 != max)
		{
			c = (min + max) / 2;
			if (c * c == nb)
				return (c);
			else if (c * c > nb)
				max = c;
			else if (c * c < nb)
				min = c;
		}
		return (max);
	}
	return (0);
}
