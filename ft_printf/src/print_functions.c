/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 14:07:25 by bprado        #+#    #+#                 */
/*   Updated: 2019/12/14 18:01:43 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			print_sign(t_pf_sect *s)
{
	if (s->spc != 'c')
	{
		if (((s->fl & PLUS || s->fl & SIGNED_F) &&
					!(s->fl & SPACE)) || s->v.llong < 0)
		{
			if ((long long)s->v.llong >= 0 && s->fl & PLUS)
				print_character('+', s);
			else if ((long long)s->v.llong < 0)
				print_character('-', s);
		}
		else if (s->fl & SPACE)
			print_character(' ', s);
		s->fl |= PRTSIGN;
	}
}

void			sign_float(t_pf_sect *s)
{
	if (s->fl ^ FLOATEXCP && ((s->fl & PLUS && !(s->fl & SPACE))
											|| s->v.lngd < 0))
	{
		if (s->v.lngd >= 0 && s->fl & PLUS)
			print_character('+', s);
		else if (s->v.lngd < 0)
			print_character('-', s);
	}
	else if (s->fl & SPACE)
		print_character(' ', s);
}

void			print_hash_flag(t_pf_sect *s)
{
	if ((s->v.ull != 0 && s->fl & HASH) || s->spc == 'p')
	{
		if (s->spc == 'x' || s->spc == 'p')
		{
			print_character('0', s);
			print_character('x', s);
		}
		else if (s->spc == 'X')
		{
			print_character('0', s);
			print_character('X', s);
		}
		else if (s->spc == 'o')
			print_character('0', s);
	}
	s->fl |= PRTSIGN;
}

static void		print_padding2(t_pf_sect *s, int padd, char character)
{
	if (s->v.ull != 0)
	{
		padd += s->spc == 'p' && character == ' ' &&
									padd >= 0 && s->prcs >= s->len ? -2 : 0;
		padd += s->spc == 'p' && character == '0' &&
									padd >= 0 && s->prcs >= s->len ? 2 : 0;
		padd += s->spc == 'x' && character == ' ' && (s->fl & HASH) &&
									padd >= 0 && 1 + s->prcs >= s->len ? -2 : 0;
		padd += s->spc == 'x' && character == '0' && (s->fl & HASH) &&
									padd >= 0 && s->prcs >= s->len ? 2 : 0;
		padd += s->spc == 'X' && character == ' ' && (s->fl & HASH) &&
									padd >= 0 && 1 + s->prcs >= s->len ? -2 : 0;
		padd += s->spc == 'X' && character == '0' && (s->fl & HASH) &&
									padd >= 0 && s->prcs >= s->len ? 2 : 0;
	}
	while (padd > 0)
	{
		print_character(character, s);
		padd--;
	}
}

void			print_padding(t_pf_sect *s, int length, char chr, char flip)
{
	int		padd;

	padd = 0;
	if (flip)
	{
		if ((s->prcs + 1 == s->len && s->fl & HASH && (s->spc == 'x' ||
															s->spc == 'X')))
			length -= 2;
		padd = s->prcs - length;
		if (s->fl & SIGNED_F && s->v.llong < 0)
			++padd;
		padd = s->spc == 'c' && s->v.ull == 0 ? 0 : padd;
	}
	else
	{
		padd = s->width - length;
		if (s->fl & SIGNED_F && ((s->v.llong >= 0 && s->fl & 0x18) ||
		(chr == ' ' && s->v.llong < 0 && s->prcs >= s->len)))
			--padd;
	}
	print_padding2(s, padd, chr);
}
