/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   specifier_functions.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 14:18:01 by bprado        #+#    #+#                 */
/*   Updated: 2019/12/14 17:32:17 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		no_minus_flag(t_pf_sect *s)
{
	int			i;

	i = ft_strchr_int("idc", s->spc);
	if (s->len >= s->width || s->prcs >= s->width ||
						(!(s->fl & PRECISN) && s->fl & ZERO_F))
		i > -1 ? print_sign(s) : print_hash_flag(s);
	if (s->width > s->prcs && s->fl & PRECISN)
		print_padding(s, s->len > s->prcs ? s->len : s->prcs, ' ', 0);
	else
		print_padding(s, s->len > s->prcs ? s->len : s->prcs,
										s->fl & ZERO_F ? '0' : ' ', 0);
	if (!(s->fl & PRTSIGN))
		i > -1 ? print_sign(s) : print_hash_flag(s);
	if ((s->fl & ZERO_F) || s->prcs >= s->len || (s->prcs + 1 == s->len &&
					s->fl & HASH && (s->spc == 'x' || s->spc == 'X')))
		print_padding(s, s->len, s->spc != 'c' ? '0' : ' ', 1);
	if (s->spc != 'c')
		i > -1 ? ft_putnbr_signed(s->v.llong, get_base(s->spc), s) :
					ft_putnbr_unsigned(s->v.ull, get_base(s->spc), s);
	else if (s->spc == 'c')
		print_character(s->v.ull, s);
}

void			print_dioupxxc(t_pf_sect *s)
{
	int			i;

	i = ft_strchr_int("idc", s->spc);
	if (s->spc == 'p')
		s->v.ptr = va_arg(s->ap, void*);
	else
		parse_length(s);
	s->len = i > -1 ? length_of_number(s) : length_of_unsigned(s);
	if (s->fl & MINUS_F)
	{
		if (i > -1 || (s->fl & HASH && s->spc != 'u') || s->spc == 'p')
			i > -1 ? print_sign(s) : print_hash_flag(s);
		print_padding(s, s->len, '0', 1);
		if (s->spc != 'c')
			i > -1 ? ft_putnbr_signed(s->v.llong, get_base(s->spc), s) :
					ft_putnbr_unsigned(s->v.ull, get_base(s->spc), s);
		else if (s->spc == 'c')
			print_character(s->v.llong, s);
		print_padding(s, (s->len > s->prcs) ? s->len : s->prcs, ' ', 0);
	}
	else
		no_minus_flag(s);
}

void			print_str(t_pf_sect *s)
{
	int			str_length;

	str_length = 0;
	if (s->spc == 's')
	{
		s->v.ptr = va_arg(s->ap, char*);
		if (!s->v.ptr)
			s->v.ptr = "(null)";
		str_length = s->prcs < (int)ft_strlen(s->v.ptr) && s->fl & PRECISN ?
										s->prcs : ft_strlen(s->v.ptr);
		s->fl |= STRNG;
	}
	if (s->fl & MINUS_F)
	{
		s->spc == 's' ? print_string(s) : print_character(s->spc, s);
		print_padding(s, s->spc == 's' ? str_length : 1, ' ', 0);
	}
	else
	{
		print_padding(s,
			s->spc == 's' ? str_length : 1,
			(s->fl & ZERO_F) ? '0' : ' ',
			0);
		s->spc == 's' ? print_string(s) : print_character(s->spc, s);
	}
}

static void		minus_flag_float(t_pf_sect *s)
{
	sign_float(s);
	putfloat(s, s->prcs + 1, 0);
	if ((((s->v.sh[4] & NZERO) == NZERO) && s->v.llong == 0))
	{
		print_character('.', s);
		while (s->prcs)
		{
			ft_printf("%d", 0);
			--s->prcs;
		}
	}
	else
		print_padding(s, (s->len > s->prcs) ? s->len : s->prcs, ' ', 0);
}

void			print_f(t_pf_sect *s)
{
	long double	copy;

	copy = (s->fl & CAP_L_F) ?
					va_arg(s->ap, long double) : va_arg(s->ap, double);
	s->v.lngd = copy;
	s->prcs = !(s->fl & PRECISN) ? 6 : s->prcs;
	s->len = length_of_float(s);
	if (s->fl & MINUS_F)
		minus_flag_float(s);
	else
	{
		s->len >= s->width || s->prcs >= s->width || s->fl & ZERO_F ?
													sign_float(s) : 0;
		if (s->len < s->width && s->fl & PRECISN && !(s->fl & ZERO_F))
			print_padding(s, s->len, ' ', 0);
		else
			print_padding(s, s->len, s->fl & ZERO_F ? '0' : ' ', 0);
		!(s->fl & ZERO_F) && s->len < s->width ? sign_float(s) : 0;
		if ((s->fl & ZERO_F) || s->width > s->len)
			print_padding(s, s->len, '0', 1);
		putfloat(s, s->prcs + 1, 0);
	}
}
