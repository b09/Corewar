/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_numlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/24 16:15:41 by bprado        #+#    #+#                 */
/*   Updated: 2020/06/24 16:17:24 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_numlen(char *str)
{
	int			i;

	i = 0;
	while (str[i] && (ft_isdigit(str[i]) || (i == 0 && str[i] == '-')))
		++i;
	return (i);
}
