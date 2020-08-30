/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/11 17:17:03 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/15 16:01:02 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long	memset_get_word(int c)
{
	unsigned long	word;

	word = (unsigned char)c;
	word = (word << 8) | word;
	word = (word << 16) | word;
	if (sizeof(word) > 4)
		word = ((word << 16) << 16) | word;
	return (word);
}

static unsigned char	*memset_unrolled(\
	unsigned long *b, unsigned long word, size_t len)
{
	while (len > 0)
	{
		b[0] = word;
		b[1] = word;
		b[2] = word;
		b[3] = word;
		b += 4;
		len--;
	}
	return ((unsigned char *)b);
}

static unsigned char	*memset_wordset(\
	unsigned char *str, unsigned long word, size_t *len)
{
	size_t	temp_len;

	temp_len = *len / (sizeof(word) * 4);
	str = memset_unrolled((unsigned long *)str, word, temp_len);
	*len %= sizeof(word) * 4;
	temp_len = *len / sizeof(word);
	while (temp_len > 0)
	{
		((unsigned long *)str)[0] = word;
		str += sizeof(word);
		temp_len--;
	}
	*len %= sizeof(word);
	return (str);
}

void					*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	unsigned long	word;

	str = (unsigned char *)b;
	if (len >= sizeof(word) * 4)
	{
		word = memset_get_word(c);
		while (((unsigned long)str & (sizeof(word) - 1)) != 0)
		{
			((unsigned char *)str)[0] = c;
			str++;
			len--;
		}
		str = memset_wordset(str, word, &len);
	}
	while (len > 0)
	{
		((unsigned char *)str)[0] = c;
		str++;
		len--;
	}
	return (b);
}
