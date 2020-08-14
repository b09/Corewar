/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   float_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 21:04:47 by bprado         #+#    #+#                */
/*   Updated: 2019/12/07 01:12:59 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		length_of_float(t_pf_object *obj)
{
	int				counter;
	long double		original_float;

	// include decimal in length and a single character
	counter = 0;
	if (((obj->val.shdbl[4] & NZERO) == NZERO) && obj->val.llong == 0)
		counter = 2 + obj->prcs;
	counter = ((obj->val.shdbl[4] & NINF) == NINF) && obj->val.llong == 0 ? 4 : counter;
	counter = ((obj->val.shdbl[4] & INF) == INF) && obj->val.llong == 0 ? 3 : counter;
	counter = ((obj->val.shdbl[4] & INF) == INF) && obj->val.llong > 0 ? 3 : counter;
	if (counter)
		return (counter);
	counter = 2;
	original_float = obj->val.lngdbl;
	counter += obj->flags & PRECISN ? obj->prcs : 6;
	
	if (original_float < 0)
		original_float = -original_float;
	while (original_float > 9)
	{
		original_float /= 10;
		++counter;
	}
	counter += obj->val.lngdbl < 0 ? 1 : 0;
	return (counter);
}

// create function to print character strings -inf, inf, nan, -0
// function works
int		float_exception(t_pf_object *obj)
{
	char 		*str1;
	char 		*str2;
	char 		*str3;
	char 		*str4;

	str1 = "-0";
	str2 = "-inf";
	str3 = "inf";
	str4 = "nan";

	if ((obj->val.shdbl[4] & NZERO) == NZERO && obj->val.llong == 0)
		obj->val.ptr = str1; 	// 	-0 negative zero
	else if ((obj->val.shdbl[4] & NINF) == NINF && obj->val.llong == 0)
		obj->val.ptr = str2;
	else if ((obj->val.shdbl[4] & INF) == INF && obj->val.llong == 0)
		obj->val.ptr = str3;
	else if ((obj->val.shdbl[4] & INF) == INF && obj->val.llong > 0)
		obj->val.ptr = str4;
	else
		return (0);
	print_string(obj);
	return (1);
}

/*
	character array
	assign front part of float to array
	add decimal point
	interate though number
 */

// void	putfloat(t_pf_object *obj)
// {
// 	u_int64_t		ret;
// 	u_int64_t		ret2;
// 	long double		copy;
// 	int				i;
// 	int				zeroes;

// 	i = obj->prcs <= 20 ? obj->prcs : 20;
// 	if (float_exception(obj))
// 		return ;
// 	copy = obj->val.lngdbl < 0 ? -obj->val.lngdbl : obj->val.lngdbl;
// 	ret = (u_int64_t)copy;
// 	copy = copy - ret;
// 	ret2 = 0;
// 	zeroes = 0;
// 	while (i + 1)
// 	{
// 		copy *= 10.0;
// 		ret2 = (ret2 * 10) + copy;
// 		if (!ret2)
// 			++zeroes;
// 		copy = copy - (((u_int64_t)copy % 10));
// 		--i;
// 	}
// 	ret2 += (ret2 % 10) > 4 ? 10 : 0;
// 	ret2 /= 10;
// 	i = obj->prcs <= 20 ? obj->prcs : 20;
// 	(ret2 > length_of_unsigned ? ft_putnbr_unsigned(ret + 1, get_base(obj->spc), obj) : ft_putnbr_unsigned(ret, get_base(obj->spc), obj);
// 	if (obj->prcs)
// 	{
// 		print_character('.', obj);
// 		while (zeroes && obj->prcs)
// 		{
// 			print_character('0', obj);
// 			--zeroes;
// 			--obj->prcs;
// 		}
// 		ret2 ? ft_putnbr_unsigned(ret2, get_base(obj->spc), obj) : 0;
// 	}

// 	// unsinged long long can handle 18 * 10^19 digits. if the final digit needs to be rounded
// 	// and it has an upward cascade effect on the previous digits (.12399999 becomes .124000)
// 	// i cannot directly print the digits. an uns long long can hold 
// }

static void		round_float(char *entire_float)
{
	int		str_i;

	str_i = ft_strchr_int(entire_float, 0) - 1;
	printf("str_i in round: %d\n", str_i);
	entire_float[str_i] = 0;
	str_i--;
	if (entire_float[str_i] != '9')
		++entire_float[str_i];
	else
	{
		while (entire_float[str_i] == '9' && str_i)
		{
			entire_float[str_i] = (entire_float[str_i] != '.') ? '0' : '.';
			str_i--;
			if (entire_float[str_i] != '9' && entire_float[str_i] != '.')
				++entire_float[str_i];
			else if (entire_float[str_i] == '.')
			{
				--str_i;
				if (entire_float[str_i] != '9')
				{
					++entire_float[str_i];
					break ;
				}
			}

		}

	}
}

static char		*string_for_float(t_pf_object *obj)
{
	char			*entire_float;
	char			*num_no_dec;
	char			*decimalstr;
	long double		copy;
	int				i;

	i = obj->prcs + 3 ; // including null character and decimal character, and first character of decimal
	decimalstr = ft_memalloc(i);
	ft_memset(decimalstr, 'a', i - 1); // to use string function must populate malloced content with non NULL chars
	decimalstr[0] = '.';
	copy = obj->val.lngdbl < 0 ? -obj->val.lngdbl : obj->val.lngdbl;
	num_no_dec = ft_itoa_unsigned(copy, 0);
	entire_float = ft_strjoin(num_no_dec, decimalstr); // strjoin will not work on null characters
	ft_memdel((void*)&num_no_dec);
	ft_memdel((void*)&decimalstr);
	return (entire_float);
}

void	putfloat(t_pf_object *obj, int i, int str_i)
{
	long double		copy;
	char			*entire_float;

	if (float_exception(obj))
		return ;
	copy = obj->val.lngdbl < 0 ? -obj->val.lngdbl : obj->val.lngdbl;
	entire_float = string_for_float(obj);
	str_i = ft_strchr_int(entire_float, 'a'); // what is the function that know how many characters to print?
	++str_i;
	while (i) // i is still precision plus two (dec and null char), reuse for precision plus one
	{
		copy *= 10.0;
		entire_float[str_i] = ((int64_t)copy % 10) + '0';;
		--i;
		++str_i;
	}
	--str_i;
	if ((entire_float[str_i] - '0') % 10 > 4)
		round_float(entire_float);
	else
		entire_float[str_i] = 0;
	entire_float[obj->prcs] = 0;
	obj->val.ptr = entire_float;
	print_string(obj);
	ft_memdel((void*)&entire_float);
}
		