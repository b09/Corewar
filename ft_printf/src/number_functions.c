/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   number_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 21:07:04 by bprado         #+#    #+#                */
/*   Updated: 2019/12/04 21:07:56 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	get_base(char format_spc)
{
	char			base;

	base = 0;
	base = format_spc == 'd' ? 10 : base;
	base = format_spc == 'i' ? 10 : base;
	base = format_spc == 'f' ? 10 : base;
	base = format_spc == 'x' ? 16 : base;
	base = format_spc == 'X' ? 16 : base;
	base = format_spc == 'o' ? 8 : base;
	base = format_spc == 'u' ? 10 : base;
	base = format_spc == 'p' ? 16 : base;
	return (base);
}

int		length_of_number(t_pf_object *obj)
{
	long long		original_int;
	int				counter;
	char			base;

	base = get_base(obj->spc);
	counter = 1;
	original_int = obj->val.llong;
	if (original_int < 0)
		original_int = -original_int;
	while ((base > 0) && original_int > (base - 1))
	{
		original_int /= base;
		++counter;
	}

	if ((obj->flags & SIGNED_F) && obj->val.llong < 0)// && (!obj->width || (obj->width && obj->flags & ZERO_F)))
		counter++;

	counter = (!obj->val.llong && obj->flags & PRECISN && !obj->prcs) ? 0 : counter;	// check this statment

	return (counter);
}

int		length_of_unsigned(t_pf_object *obj)
{
	u_int64_t		original_int;
	int						counter;
	unsigned char			base;

	base = get_base(obj->spc);
	counter = 1;
	original_int = obj->val.ll;
	while ((base > 0) && original_int > (base - 1))
	{
		original_int /= base;
		++counter;
	}
	if (obj->flags & HASH_F && obj->spc == 'o' && obj->val.ll != 0)
		counter += 1;
	else if ((obj->flags & HASH_F) && obj->spc != 'o' && obj->val.ll != 0)
		counter += 2; // check this statement
	else if (obj->spc == 'p')
		counter += 2;

	counter = (!obj->val.ll && obj->flags & PRECISN && !obj->prcs) ? 0 : counter;	// check this statement

	return (counter);
}

void	ft_putnbr_signed(long long n, int base, t_pf_object *obj)
{
	char				a;
	long long			i;

	a = 0;
	if (obj->val.ll == 0 && ((obj->flags & PRECISN && obj->prcs == 0) || obj->spc == 'c')) // check this
		return ;
	if (n < 0)
		n = -n;
	i = n;
	if (i > (base - 1))
	{
		ft_putnbr_signed(i / base, base, obj);
		ft_putnbr_signed(i % base, base, obj);
	}
	if (i <= (base - 1) && i < 10)
	{
		a = '0' + i;
		print_character(a, obj);
	}
	else if (i > 9 && i < 16 && base > 10)
	{
		a = obj->spc != 'X' ? 'a' + i - 10 : 'A' + i - 10;
		print_character(a, obj);
	}
}

void	ft_putnbr_unsigned(u_int64_t i, int base, t_pf_object *obj)
{
	unsigned char			a;
	// u_int64_t		i;

	a = 0;
	if (obj->val.ll == 0 && obj->flags & PRECISN && obj->prcs == 0) // check this
		return ;
	// i = n;
	if (i > ((unsigned)base - 1))
	{
		ft_putnbr_unsigned(i / base, base, obj);
		ft_putnbr_unsigned(i % base, base, obj);
	}
	if (i <= ((unsigned)base - 1) && i < 10)
	{
		a = '0' + i;
		print_character(a, obj);
	}
	else if (i > 9 && i < 16 && base > 10)
	{
		a = obj->spc != 'X' ? 'a' + i - 10 : 'A' + i - 10;
		print_character(a, obj);
	}
}
