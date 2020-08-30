/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/20 18:47:24 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/25 18:31:22 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	strtrim_get_start(char const *s, int stop)
{
	int	start;

	start = 0;
	while (start < stop \
		&& (s[start] == ' ' || s[start] == '\n' || s[start] == '\t'))
		start++;
	return (start);
}

static int	strtrim_get_stop(char const *s, int start, int stop)
{
	while (stop >= start \
		&& (s[stop] == ' ' || s[stop] == '\n' || s[stop] == '\t'))
		stop--;
	return (stop);
}

char		*ft_strtrim(char const *s)
{
	int		i;
	int		stop;
	int		start;
	char	*str;
	char	*src;

	stop = ft_strlen(s) - 1;
	start = strtrim_get_start(s, stop);
	stop = strtrim_get_stop(s, start, stop);
	if (stop == 0 || s[start] == '\0')
		return ((char *)ft_memalloc(1));
	str = (char *)malloc(stop - start + 2);
	if (str == NULL)
		return (NULL);
	i = 0;
	src = (char *)&s[start];
	stop -= start;
	while (i <= stop)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
