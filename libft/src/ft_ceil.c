/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ceil.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 18:50:29 by bprado        #+#    #+#                 */
/*   Updated: 2020/06/25 18:50:44 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double			ft_ceil(double num)
{
	long long	temp;

	temp = (long long)num;
	if (temp == num || num < 0)
		return (temp);
	else
		return (temp + 1);
}
