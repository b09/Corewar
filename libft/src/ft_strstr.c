/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strstr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 17:53:58 by bprado        #+#    #+#                 */
/*   Updated: 2019/01/20 21:23:02 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;

	if (*needle == 0)
		return ((char*)haystack);
	while (*haystack)
	{
		i = 0;
		while (*needle == *haystack)
		{
			++needle;
			++haystack;
			--i;
			if (*needle == 0)
				return ((char*)&haystack[i]);
		}
		needle += i;
		haystack += (i + 1);
	}
	return (NULL);
}
