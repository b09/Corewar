/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_tolower.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/05 15:52:43 by bprado        #+#    #+#                 */
/*   Updated: 2019/02/05 15:52:45 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strlower(const char *str)
{
	int		i;
	char	*a;

	i = 0;
	a = ft_strdup(str);
	while (str[i] != 0)
	{
		a[i] = ft_tolower(str[i]);
		++i;
	}
	a[i] = 0;
	return (a);
}
