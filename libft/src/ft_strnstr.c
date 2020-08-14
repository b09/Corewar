/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 17:53:29 by bprado        #+#    #+#                 */
/*   Updated: 2019/01/18 20:39:15 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	i;

	if (*needle == 0)
		return ((char*)haystack);
	while (*haystack != 0 && len)
	{
		i = 0;
		while (*needle == *haystack && len)
		{
			++needle;
			++haystack;
			--i;
			--len;
			if (*needle == 0 && (len || len == 0))
				return ((char*)&haystack[i]);
		}
		if (len <= 1)
			return (NULL);
		len += (i - 1);
		needle += i;
		haystack += (i + 1);
	}
	return (NULL);
}
