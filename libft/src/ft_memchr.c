/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/13 18:33:23 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/19 17:13:56 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long	memchr_get_word(int c)
{
	unsigned long	word;

	word = (unsigned char)c;
	word = (word << 8) | word;
	word = (word << 16) | word;
	if (sizeof(word) > 4)
		word = ((word << 16) << 16) | word;
	return (word);
}

static t_magicmask		*memchr_set_magic(void)
{
	t_magicmask	*magic;

	magic = (t_magicmask *)malloc(sizeof(t_magicmask));
	if (magic == NULL)
		return (NULL);
	magic->himagic = 0x80808080L;
	magic->lomagic = 0x01010101L;
	if (sizeof(magic->himagic) > 4)
	{
		magic->himagic = ((magic->himagic << 16) << 16) | magic->himagic;
		magic->lomagic = ((magic->lomagic << 16) << 16) | magic->lomagic;
	}
	return (magic);
}

static void				*memchr_unrolled(\
const unsigned char *c, unsigned char stop_char)
{
	if (c[0] == stop_char)
		return ((void *)(c + 0));
	else if (c[1] == stop_char)
		return ((void *)(c + 1));
	else if (c[2] == stop_char)
		return ((void *)(c + 2));
	else if (c[3] == stop_char)
		return ((void *)(c + 3));
	else if (c[4] == stop_char)
		return ((void *)(c + 4));
	else if (c[5] == stop_char)
		return ((void *)(c + 5));
	else if (c[6] == stop_char)
		return ((void *)(c + 6));
	else if (c[7] == stop_char)
		return ((void *)(c + 7));
	return (NULL);
}

static void				*memchr_unroll_prep(int stop_char, \
	t_magicmask *magic, const unsigned long *longword_ptr, size_t xlen)
{
	unsigned long			stop;
	unsigned long			longword;
	const unsigned char		*c;
	void					*addr;

	stop = memchr_get_word(stop_char);
	while (xlen > 0)
	{
		longword = *longword_ptr;
		longword_ptr++;
		if ((((longword - magic->lomagic) \
			& ~longword & magic->himagic) ^ stop) != 0)
		{
			c = (const unsigned char *)(longword_ptr - 1);
			addr = memchr_unrolled(c, stop_char);
			if (addr != NULL)
			{
				free(magic);
				return (addr);
			}
		}
		xlen--;
	}
	free(magic);
	return (NULL);
}

void					*ft_memchr(const void *s, int c, size_t n)
{
	void				*ret;
	unsigned char		*b;
	const unsigned long	*longword;
	t_magicmask			*magic;

	b = (unsigned char *)s;
	while (((unsigned long)b & (sizeof(*longword) - 1)) != 0 && n > 0)
	{
		if (*b == (unsigned char)c)
			return ((void *)b);
		b++;
		n--;
	}
	longword = (unsigned long *)b;
	magic = memchr_set_magic();
	if (magic == NULL)
		return (NULL);
	ret = memchr_unroll_prep(c, magic, longword, n / sizeof(*longword));
	if (ret != NULL)
		return ((void *)ret);
	b += (n / sizeof(*longword)) * sizeof(*longword);
	return (ft_slow_memchr(b, c, n % sizeof(*longword)));
}
