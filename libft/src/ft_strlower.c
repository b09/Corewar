/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlower.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/13 19:25:29 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/16 19:01:42 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strlower(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] - 'A' + 'a';
		i++;
	}
	return (str);
}
