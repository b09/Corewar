/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   specifier_functions.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 14:18:01 by bprado         #+#    #+#                */
/*   Updated: 2019/12/07 01:14:32 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


void	print_dioupxxc(t_pf_object *obj)
{
	int		i;

	i = ft_strchr_int("idc", obj->spc);
	if (obj->spc == 'p')
		obj->val.ptr = va_arg(obj->ap, void*);
	else
		parse_length(obj);
	obj->i = i > -1 ? length_of_number(obj) : length_of_unsigned(obj);
	if (obj->flags & MINUS_F)
	{
		if (i > -1 || (obj->flags & HASH_F && obj->spc != 'u') || obj->spc == 'p')
			i > -1 ? print_sign(obj) : print_hash_flag(obj);
		print_padding(obj, obj->i, '0', 1);
		if (obj->spc != 'c')
			i > -1 ? ft_putnbr_signed(obj->val.llong, get_base(obj->spc), obj) :
					ft_putnbr_unsigned(obj->val.ll, get_base(obj->spc), obj);
		else if (obj->spc == 'c')
			print_character(obj->val.llong, obj);
		print_padding(obj, (obj->i > obj->prcs) ? obj->i : obj->prcs, ' ', 0);
	}
	else
		no_minus_flag(obj);
}

void	print_str(t_pf_object *obj)
{
	int			str_length;

	str_length = 0;
	if (obj->spc == 's')
	{
		obj->val.ptr = va_arg(obj->ap, char*);
		if (!obj->val.ptr)
			obj->val.ptr = "(null)";
		str_length = obj->prcs < (int)ft_strlen(obj->val.ptr) && obj->flags & PRECISN ?
										obj->prcs : (int)ft_strlen(obj->val.ptr);
		obj->flags |= STRNG;
	}
	if (obj->flags & MINUS_F)
	{
		obj->spc == 's' ? print_string(obj) : print_character(obj->spc, obj);
		print_padding(obj, obj->spc == 's' ? str_length : 1, ' ', 0);
	}
	else
	{
		print_padding(obj,
			obj->spc == 's' ? str_length : 1,
			(obj->flags & ZERO_F) ? '0' : ' ',
			0);
		obj->spc == 's' ? print_string(obj) : print_character(obj->spc, obj);
	}
}

void	print_f(t_pf_object *obj)
{
	long double	copy;

	// parse_length(obj);
	copy = (obj->flags & CAP_L_F) ? va_arg(obj->ap, long double) : va_arg(obj->ap, double);
	obj->val.lngdbl = copy;
	obj->prcs = !(obj->flags & PRECISN) ? 6 : obj->prcs;
	obj->i = length_of_float(obj);		// must implement correctly, ie. what is the length of a float
	if (obj->flags & MINUS_F)
	{
		print_sign_float(obj);
		putfloat(obj, obj->prcs + 1, 0);
		print_padding(obj, (obj->i > obj->prcs) ? obj->i : obj->prcs, ' ', 0);
	}
	else
	{
		obj->i >= obj->width || obj->prcs >= obj->width || obj->flags & ZERO_F ? print_sign_float(obj) : 0;
		if (obj->width > obj->prcs && obj->flags & PRECISN)
			print_padding(obj, obj->i > obj->prcs ? obj->i : obj->prcs, ' ', 0);
		else
			print_padding(obj, obj->i, obj->flags & ZERO_F ? '0' : ' ', 0);
		!(obj->flags & ZERO_F) && obj->i < obj->width ? print_sign_float(obj) : 0;
		if ((obj->flags & ZERO_F) || obj->width > obj->i)
			print_padding(obj, obj->i, '0', 1);
		putfloat(obj, obj->prcs + 1, 0);
	}
}

void	no_minus_flag(t_pf_object *obj)
{
	int		i;

	i = ft_strchr_int("idc", obj->spc);

	if (obj->i >= obj->width || obj->prcs >= obj->width ||
						(!(obj->flags & PRECISN) && obj->flags & ZERO_F))
		i > -1 ? print_sign(obj) : print_hash_flag(obj);
	if (obj->width > obj->prcs && obj->flags & PRECISN)
		print_padding(obj, obj->i > obj->prcs ? obj->i : obj->prcs, ' ', 0);
	else
		print_padding(obj, obj->i > obj->prcs ? obj->i : obj->prcs,
										obj->flags & ZERO_F ? '0' : ' ', 0);
	if (!(obj->flags & PRTSIGN))
		i > -1 ? print_sign(obj) : print_hash_flag(obj);
	if ((obj->flags & ZERO_F) || obj->prcs > obj->i)
		print_padding(obj, obj->i, obj->spc != 'c' ? '0' : ' ', 1);
	if (obj->spc != 'c')
		i > -1 ? ft_putnbr_signed(obj->val.llong, get_base(obj->spc), obj) :
					ft_putnbr_unsigned(obj->val.ll, get_base(obj->spc), obj);
	else if (obj->spc == 'c')
		print_character(obj->val.ll, obj);
}
