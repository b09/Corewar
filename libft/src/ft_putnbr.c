/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 17:49:06 by bprado        #+#    #+#                 */
/*   Updated: 2019/07/09 19:27:52 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(long long n)
{
	char			a;
	long long		i;

	if (n < 0)
	{
		n = -n;
		write(1, "-", 1);
	}
	i = n;
	if (i > 9)
	{
		ft_putnbr(i / 10);
		ft_putnbr(i % 10);
	}
	if (i <= 9)
	{
		a = '0' + i;
		write(1, &a, 1);
	}
}
