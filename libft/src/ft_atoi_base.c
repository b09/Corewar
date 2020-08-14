/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: exam <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/05 10:23:36 by exam          #+#    #+#                 */
/*   Updated: 2020/06/07 18:49:00 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check_char(char str, int str_base)
{
	char				*a;
	char				*b;
	int					i;

	a = "0123456789ABCDEF";
	b = "0123456789abcdef";
	i = 0;
	while (a[i] != 0 && a[i] != str && b[i] != str)
		++i;
	i = (i < str_base) ? (i + 1) : 0;
	return (i);
}

static int		add_correct_base(const char *str)
{
	if (*str >= 'a' && *str <= 'f')
		return (*str - 'a' + 10);
	else if (*str >= 'A' && *str <= 'F')
		return (*str - 'A' + 10);
	else if (*str >= 48 && *str <= 57)
		return (*str - 48);
	return (0);
}

int				ft_atoi_base(const char *str, int str_base)
{
	unsigned long		i;
	int					j;

	i = 0;
	j = 1;
	if (!*str || str_base > 16 || str_base < 2)
		return (0);
	while (*str > 0 && *str < 33)
		++str;
	if (*str == '-' && check_char(*(str + 1), str_base))
	{
		j = -1;
		++str;
	}
	while (check_char(*str, str_base) && *str != 0)
	{
		i += (str_base <= 10) ? (*str - 48) : add_correct_base(str);
		i *= str_base;
		++str;
	}
	i /= str_base;
	return (i * j);
}
