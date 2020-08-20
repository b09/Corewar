/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/07 21:49:51 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/10 14:27:21 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		strlen_set_magic(\
	unsigned long *himagic, unsigned long *lomagic)
{
	*himagic = 0x80808080L;
	*lomagic = 0x01010101L;
	if (sizeof(*himagic) > 4)
	{
		*himagic = ((*himagic << 16) << 16) | *himagic;
		*lomagic = ((*lomagic << 16) << 16) | *lomagic;
	}
}

static size_t	strlen_unrolled(const char *str, unsigned long himagic,\
				unsigned long lomagic, const unsigned long *longword_ptr)
{
	unsigned long		longword;
	const char			*c;
	int					i;

	while (TRUE)
	{
		longword = *longword_ptr;
		longword_ptr++;
		if (((longword - lomagic) & ~longword & himagic) != 0)
		{
			c = (const char *)(longword_ptr - 1);
			if (c[0] == 0)
				return (c - str);
			else if (c[1] == 0)
				return ((c - str) + 1);
			i = 2;
			while (i < 8)
			{
				if (c[i] == 0)
					return ((c - str) + i);
				i++;
			}
		}
	}
}

size_t			ft_strlen(const char *str)
{
	const char			*c;
	const unsigned long	*longword_ptr;
	unsigned long		longword;
	unsigned long		himagic;
	unsigned long		lomagic;

	c = str;
	while (((unsigned long)c & (sizeof(longword) - 1)) != 0)
	{
		if (*c == '\0')
			return (c - str);
		c++;
	}
	longword_ptr = (unsigned long *)c;
	strlen_set_magic(&himagic, &lomagic);
	return (strlen_unrolled(str, himagic, lomagic, longword_ptr));
}
