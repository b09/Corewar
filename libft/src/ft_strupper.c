/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_toupper.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/05 15:52:31 by bprado        #+#    #+#                 */
/*   Updated: 2019/02/05 15:52:34 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strupper(const char *str)
{
	int		i;
	char	*a;

	i = 0;
	a = ft_strdup(str);
	while (str[i] != 0)
	{
		a[i] = ft_toupper(str[i]);
		++i;
	}
	a[i] = 0;
	return (a);
}
