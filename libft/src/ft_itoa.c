/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/12 20:07:46 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/25 17:29:06 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	itoa_digits(int n)
{
	int		digits;

	if (n == FT_INT_MIN)
		return (11);
	if (n <= 0)
	{
		digits = 1;
		n *= -1;
	}
	else
		digits = 0;
	while (n > 0)
	{
		digits++;
		n /= 10;
	}
	return (digits);
}

static char	*itoa_fill_str(char *str, int n, int len, int i)
{
	while (n > 0)
	{
		str[len - i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	return (str);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		len;

	len = itoa_digits(n);
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	i = 1;
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		str[len - i] = -(n % 10) + '0';
		n /= -10;
		i++;
	}
	itoa_fill_str(str, n, len, i);
	str[len] = '\0';
	return (str);
}
