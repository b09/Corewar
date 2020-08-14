/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pow.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 21:47:01 by bprado        #+#    #+#                 */
/*   Updated: 2019/12/11 21:49:11 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long double		ft_pow(float nbr, float exp)
{
	float	holder;

	holder = nbr;
	while (exp > 0)
	{
		nbr *= holder;
		--exp;
	}
	return (nbr);
}
