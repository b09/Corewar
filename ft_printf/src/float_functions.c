/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   float_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 21:04:47 by bprado        #+#    #+#                 */
/*   Updated: 2019/12/14 17:58:31 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			float_exception(t_pf_sect *s)
{
	char			*str1;
	char			*str2;
	char			*str3;
	char			*str4;
	long double		temp;

	str1 = "-0";
	str2 = "-inf";
	str3 = "inf";
	str4 = "nan";
	temp = s->v.lngd;
	if ((s->v.sh[4] & NZERO) == NZERO && s->v.llong == 0)
		s->v.ptr = str1;
	else if ((s->v.sh[4] & NINF) == NINF && s->v.llong == (1L << 63))
		s->v.ptr = str2;
	else if ((s->v.sh[4] & INF) == INF && s->v.llong == (1L << 63))
		s->v.ptr = str3;
	else if ((s->v.sh[4] & INF) == INF && s->v.llong != 0)
		s->v.ptr = str4;
	else
		return (0);
	print_string(s);
	s->v.lngd = temp;
	s->fl |= FLOATEXCP;
	return (1);
}

static void			round_float(char *str, int i)
{
	if (str[i] != '9' && str[i] != '.')
		++str[i];
	else
	{
		while (i > -1 && (str[i] == '9' || str[i] == '.'))
		{
			str[i] = (str[i] != '.') ? '0' : '.';
			i--;
			if (str[i] != '9' && str[i] != '.')
			{
				++str[i];
				break ;
			}
			else if (str[i] == '.')
			{
				--i;
				if (str[i] != '9')
				{
					++str[i];
					break ;
				}
			}
		}
	}
}

static char			*string_for_float(t_pf_sect *s, char flip, char *decimalstr)
{
	char			*entire_float;
	char			*num_no_dec;
	long double		copy;
	int				i;

	if (flip)
	{
		i = s->prcs + 3;
		decimalstr = ft_memalloc(i);
		ft_memset(decimalstr, 'a', i - 1);
		decimalstr[0] = '.';
		copy = s->v.lngd < 0 ? -s->v.lngd : s->v.lngd;
		num_no_dec = ft_itoa_unsigned(copy, 0);
		entire_float = ft_strjoin(num_no_dec, decimalstr);
		free(num_no_dec);
	}
	else
		entire_float = ft_strjoin("1", decimalstr);
	free(decimalstr);
	return (entire_float);
}

static void			putfloat2(t_pf_sect *s, int j, int str_i)
{
	if ((s->temp[str_i] - '0') % 10 > 4)
	{
		s->temp[str_i] = 0;
		str_i--;
		round_float(s->temp, str_i);
	}
	else
		s->temp[str_i] = 0;
	if (s->temp[0] == '0' && j != '0')
		s->v.ptr = string_for_float(s, 0, s->temp);
	else
		s->v.ptr = s->temp;
	j = ft_strchr_int((char*)s->v.ptr, '.');
	((char*)s->v.ptr)[j + (s->prcs ? s->prcs + 1 : 0)] = 0;
	print_string(s);
	if ((s->fl & HASH) && s->prcs == 0)
		print_character('.', s);
	free(s->v.ptr);
}

void				putfloat(t_pf_sect *s, int prcs, int str_i)
{
	long double		copy;
	int				j;

	if (float_exception(s))
		return ;
	copy = s->v.lngd < 0 ? -s->v.lngd : s->v.lngd;
	s->temp = string_for_float(s, 1, s->temp2);
	j = s->temp[0];
	str_i = ft_strchr_int(s->temp, 'a');
	while (prcs)
	{
		copy *= 10.0;
		s->temp[str_i] = ((int64_t)copy % 10) + '0';
		copy -= (int64_t)copy;
		--prcs;
		++str_i;
	}
	--str_i;
	putfloat2(s, j, str_i);
}
