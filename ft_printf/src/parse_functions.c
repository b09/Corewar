/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/03 19:16:18 by bprado         #+#    #+#                */
/*   Updated: 2019/12/04 21:21:36 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_length(t_pf_object *obj)
{
	union_output i;

	i.ll = 0;
	if (ft_strchr("cdi", obj->spc))
	{
		// specifier 'c' must be properly tested
		i.llong = obj->flags & LL_F ? va_arg(obj->ap, long long) : i.llong;
		i.llong = obj->flags & L_F ? va_arg(obj->ap, long) : i.llong;
		i.llong = (obj->flags & 0x140) == 0 ? va_arg(obj->ap, int) : i.llong;
		i.llong = obj->flags & H_F ? (short)i.llong : i.llong;
		i.llong = obj->flags & HH_F ? (char)i.llong : i.llong;
		obj->val.llong = i.llong;
	}
	if (ft_strchr("ouxX", obj->spc))
	{
		i.ll = obj->flags & LL_F ? va_arg(obj->ap, u_int64_t) : i.ll;
		i.ll = obj->flags & L_F ? va_arg(obj->ap, unsigned long) : i.ll;
		i.ll = (obj->flags & 0x140) == 0 ? va_arg(obj->ap, unsigned int) : i.ll;
		i.ll = obj->flags & H_F ? (unsigned short)i.ll : i.ll;
		i.ll = obj->flags & HH_F ? (unsigned char)i.ll : i.ll;
		obj->val.ll = i.ll;
	}
}

void	parse_specifier(func_pointer arrpointer[128])
{
	int				i;

	i = 0;
	while (i < 128)
		arrpointer[i++] = print_str;
	arrpointer['s'] = print_str;
	arrpointer['c'] = print_dioupxxc;
	arrpointer['p'] = print_dioupxxc;
	arrpointer['d'] = print_dioupxxc;
	arrpointer['i'] = print_dioupxxc;
	arrpointer['o'] = print_dioupxxc;
	arrpointer['u'] = print_dioupxxc;
	arrpointer['x'] = print_dioupxxc;
	arrpointer['X'] = print_dioupxxc;
	arrpointer['f'] = print_f;
}

void	parse_flags(t_pf_object *obj)
{
	while (ft_strchr_int("#0- +", obj->str[obj->i_str]) != -1)
	{
		obj->flags |= 1 << ft_strchr_int("#0- +", obj->str[obj->i_str]);
		++obj->i_str;
	}
	obj->flags ^= ((obj->flags & 0x6) == 0x6) ? ZERO_F : 0;
	obj->flags ^= ((obj->flags & 0x18) == 0x18) ? SPACE_F : 0;
}

void	parse_width_precision(t_pf_object *obj)
{
	obj->width = ft_atoi(&(obj->str[obj->i_str]));
	obj->width = obj->str[obj->i_str] == '*' ? va_arg(obj->ap, int) : obj->width;
	obj->flags |= obj->width ? WIDTH : 0;
	while (ft_isdigit(obj->str[obj->i_str]))
		++obj->i_str;
	obj->i_str += obj->str[obj->i_str] == '*' ? 1 : 0;
	if (obj->str[obj->i_str] == '.')
	{
		obj->i_str++;
		obj->flags |= PRECISN;
		obj->prcs = ft_atoi(&(obj->str[obj->i_str]));
		obj->prcs = obj->str[obj->i_str] == '*' ? va_arg(obj->ap, int) : obj->prcs;
		while (ft_isdigit(obj->str[obj->i_str]))
			++obj->i_str;
		obj->i_str += obj->str[obj->i_str] == '*' ? 1 : 0;
	}
}

void	parse_general(t_pf_object *obj)
{
	parse_flags(obj);
	parse_width_precision(obj);
	if (obj->str[obj->i_str] == 'l')
		obj->flags |= (obj->str[obj->i_str + 1] == 'l') ? LL_F : L_F;
	if (obj->str[obj->i_str] == 'h')
		obj->flags |= (obj->str[obj->i_str + 1] == 'h') ? HH_F : H_F;
	if (obj->str[obj->i_str] && obj->str[obj->i_str] == 'L')
		obj->flags |= CAP_L_F;
	obj->i_str += obj->flags & 0x180 ? 2 : 0;
	obj->i_str += obj->flags & 0x460 ? 1 : 0;
	obj->spc = obj->str[obj->i_str];
	if (obj->spc == 'i' || obj->spc == 'd')
		obj->flags |= SIGNED_F;
}
