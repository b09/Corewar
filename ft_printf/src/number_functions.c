/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   number_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 21:07:04 by bprado        #+#    #+#                 */
/*   Updated: 2019/12/14 17:28:02 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				length_of_number(t_pf_sect *s)
{
	long long		original_int;
	int				counter;
	char			base;

	base = get_base(s->spc);
	counter = 1;
	original_int = s->v.llong;
	if (original_int < 0)
		original_int = -original_int;
	while ((base > 0) && original_int > (base - 1))
	{
		original_int /= base;
		++counter;
	}
	if ((s->fl & SIGNED_F) && s->v.llong < 0)
		counter++;
	counter = (!s->v.llong && s->fl & PRECISN && !s->prcs) ? 0 : counter;
	return (counter);
}

int				length_of_unsigned(t_pf_sect *s)
{
	u_int64_t		original_int;
	int				counter;
	u_int8_t		base;

	base = get_base(s->spc);
	counter = 1;
	original_int = s->v.ull;
	while ((base > 0) && original_int > (base - 1))
	{
		original_int /= base;
		++counter;
	}
	if ((s->fl & HASH) && s->spc != 'o' && s->v.ull != 0 && s->spc != 'u')
		counter += 2;
	else if (s->spc == 'p')
		counter += 2;
	counter = (!s->v.ull && s->fl & PRECISN && !s->prcs) ? 0 : counter;
	if (s->fl & HASH && s->spc == 'o' && s->v.ull != 0)
		counter += 1;
	else if (s->fl & HASH && s->spc == 'o' && s->v.ull == 0)
		counter = 1;
	return (counter);
}

void			ft_putnbr_signed(long long n, int base, t_pf_sect *s)
{
	char			a;
	int64_t			i;

	a = 0;
	if ((s->v.llong == 0 && ((s->fl & PRECISN && s->prcs == 0) ||
	s->spc == 'c')) || (s->v.llong == -9223372036854775807 - 1))
		return (putnbr_signed_exception(s));
	if (n < 0)
		n = -n;
	i = n;
	if (i > (base - 1))
	{
		ft_putnbr_signed(i / base, base, s);
		ft_putnbr_signed(i % base, base, s);
	}
	if (i <= (base - 1) && i < 10)
	{
		a = '0' + i;
		print_character(a, s);
	}
	else if (i > 9 && i < 16 && base > 10)
	{
		a = s->spc != 'X' ? 'a' + i - 10 : 'A' + i - 10;
		print_character(a, s);
	}
}

void			ft_putnbr_unsigned(u_int64_t i, int base, t_pf_sect *s)
{
	u_int8_t		a;

	a = 0;
	if (s->v.ull == 0 && s->prcs == 0 && (((s->fl & PRECISN) &&
		(s->spc != 'o' || (s->spc == 'o' && !(s->fl & HASH)))) ||
		((s->spc == 'x' || s->spc == 'X') && s->fl & HASH)))
		return ;
	if (i > ((unsigned)base - 1))
	{
		ft_putnbr_unsigned(i / base, base, s);
		ft_putnbr_unsigned(i % base, base, s);
	}
	if (i <= ((unsigned)base - 1) && i < 10)
	{
		a = '0' + i;
		print_character(a, s);
	}
	else if (i > 9 && i < 16 && base > 10)
	{
		a = s->spc != 'X' ? 'a' + i - 10 : 'A' + i - 10;
		print_character(a, s);
	}
}

int				length_of_float(t_pf_sect *s)
{
	int				i;
	long double		original_float;

	i = 0;
	if (((s->v.sh[4] & NZERO) == NZERO) && s->v.llong == 0)
		i = 2 + (s->prcs ? s->prcs + 1 : 0);
	i = ((s->v.sh[4] & NINF) == NINF && s->v.llong == (1L << 63)) ? 4 : i;
	i = ((s->v.sh[4] & INF) == INF && s->v.llong == (1L << 63)) ? 3 : i;
	i = ((s->v.sh[4] & INF) == INF && s->v.llong != 0) ? 3 : i;
	if (i)
		return (i);
	i = 2;
	original_float = s->v.lngd;
	i += s->fl & PRECISN ? s->prcs : 6;
	i = s->fl & PRECISN && !s->prcs ? 1 : i;
	if (original_float < 0)
		original_float = -original_float;
	while (original_float > 9)
	{
		original_float /= 10;
		++i;
	}
	i += s->v.lngd < 0 ? 1 : 0;
	i += s->fl & (HASH | PLUS) || (s->fl & SPACE && s->v.lngd > 0) ? 1 : 0;
	return (i);
}
