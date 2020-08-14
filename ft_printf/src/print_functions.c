/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 14:07:25 by bprado         #+#    #+#                */
/*   Updated: 2019/12/06 16:29:21 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_sign(t_pf_object *obj)
{
	if (obj->spc != 'c')
	{
		if (((obj->flags & PLUS_F || obj->flags & SIGNED_F) &&
					!(obj->flags & SPACE_F)) || obj->val.llong < 0)
		{
			if ((long long)obj->val.ll >= 0 && obj->flags & PLUS_F)
				print_character('+', obj);
			else if ((long long)obj->val.ll < 0)
				print_character('-', obj);
		}
		else if (obj->flags & SPACE_F)
			print_character(' ', obj);
		obj->flags |= PRTSIGN;
	}
}

void	print_sign_float(t_pf_object *obj)
{
	if (((obj->flags & PLUS_F) && !(obj->flags & SPACE_F)) || obj->val.lngdbl < 0)
	{
		if (obj->val.lngdbl >= 0 && obj->flags & PLUS_F)
			print_character('+', obj);
		else if (obj->val.lngdbl < 0)
			print_character('-', obj);
	}
	else if (obj->flags & SPACE_F)
		print_character(' ', obj);
}

void	print_hash_flag(t_pf_object *obj)
{
	// pointers do print 0x0 for 0 conversions
	// if PRTSIGN used here, make sure pointers don't cause that to be turned on
	// if (obj->val.ll != 0 && (obj->flags & HASH_F || obj->spc == 'p'))
	if ((obj->val.ll != 0 && obj->flags & HASH_F) || obj->spc == 'p')
	{
		if (obj->spc == 'o')
			print_character('0', obj);
		if (obj->spc == 'x' || obj->spc == 'p')
		{
			print_character('0', obj);
			print_character('x', obj);
		}
		else if (obj->spc == 'X')
		{
			print_character('0', obj);
			print_character('X', obj);
		}
	}
	obj->flags |= PRTSIGN;
}

void	print_padding(t_pf_object *obj, int length, char character, char flip)
{
	int		padd;

	padd = 0;
	if (flip)
	{		
		padd = obj->prcs - length;
		// if ((obj->flags & PLUS_F && obj->flags & SIGNED_F) || (obj->flags & SIGNED_F && obj->val.llong < 0))
		if (obj->flags & SIGNED_F && obj->val.llong < 0)
			++padd;
		padd = obj->spc == 'c' && obj->val.ll == 0 ? 0 : padd;
	}
	else
	{
		padd = obj->width - length;

		// if (obj->flags & SIGNED_F && character == ' ' && !(obj->flags & MINUS_F) && (obj->flags & PLUS_F || obj->flags & SPACE_F || obj->val.llong < 0))
		// if ((obj->flags & SIGNED_F && character == ' ') && (obj->val.llong < 0 || (obj->val.llong >= 0 && obj->flags & 0x810))) //0x810 PRECISN & PLUS
	
		// if ((obj->flags & SIGNED_F && character == ' ' && obj->prcs) && (obj->val.llong < 0 || (obj->val.llong >= 0 && obj->flags & 0x18))) //0x18 SPACE & PLUS
		// if ((obj->flags & SIGNED_F && character == ' ') && (obj->val.llong < 0 || (obj->val.llong >= 0 && obj->flags & 0x18)))
		// if ((obj->flags & SIGNED_F && character == ' ') && ((obj->val.llong >= 0 && obj->flags & 0x18) || (obj->val.llong < 0 && obj->flags & ZERO_F)))
		if ((obj->flags & SIGNED_F && character == ' ') && ((obj->val.llong >= 0 && obj->flags & 0x18) || (obj->val.llong < 0 && obj->prcs >= obj->i)))// && obj->flags & ZERO_F)))
			--padd;
		else if (obj->flags & SIGNED_F && character == '0' && obj->flags & PLUS_F && obj->val.llong >= 0)
			--padd;
	}
	padd += obj->spc == 'p' && character == ' ' && obj->prcs > obj->i ? -2 : 0;
	padd += obj->spc == 'p' && character == '0' && obj->prcs > obj->i ? 2 : 0;
	while (padd > 0)
	{
		print_character(character, obj);
		padd--;
	}
}

void	print_string(t_pf_object *obj)
{
	char 		*str;

	str = "(null)";
	if (obj->spc == 's')
	{
		if (obj->val.ptr == 0)
		{
			while (*str)
				print_character(*str++, obj);
			return ;
		}
		if (obj->flags & PRECISN)
		{
			while (*(char*)obj->val.ptr && obj->prcs-- > 0)
				print_character(*(char*)obj->val.ptr++, obj);
		}
		else
		{
			while (*(char*)obj->val.ptr)
				print_character(*(char*)obj->val.ptr++, obj);
		}
	}
	else
	{
		while (*(char*)obj->val.ptr)
			print_character(*(char*)obj->val.ptr++, obj);
	}
	
}


