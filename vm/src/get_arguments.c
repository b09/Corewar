/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_arguments.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/17 11:28:14 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	returns size of argument based on encoding byte, and position being checked
**	in encoding_byte (the arg_idx) and, if argument is a T_DIR, also based on
**	dir_two.
*/

int					get_arg_size(char encode_byte, int arg_idx, bool dir_is_two)
{
	unsigned char	mask;
	int				shift;

	shift = (6 - (arg_idx * 2));
	mask = 0x03;
	mask <<= shift;
	if ((encode_byte & mask) == (REG_CODE << shift))
		return (1);
	else if (dir_is_two == FALSE && (encode_byte & mask) == (DIR_CODE << shift))
		return (4);
	else if (dir_is_two == TRUE && (encode_byte & mask) == (DIR_CODE << shift))
		return (2);
	else if ((encode_byte & mask) == (IND_CODE << shift))
		return (2);
	return (0);
}

static int			get_val(unsigned char *field, int pos, size_t size)
{
	int				ret;
	int				byte;
	size_t			i;

	ret = 0;
	i = 0;
	while (i < size)
	{
		byte = field[(pos + i) % MEM_SIZE];
		ret |= (byte << (i * 8));
		i++;
	}
	return (switch_endianness(ret, size));
}

/*
**	int pos is current position of cursor
**	pos + 1 is encoding byte
**	pos + 2 is start of arguments
*/

void				populate_arguments(unsigned char *field, int pos,\
					t_args *args, bool dir_is_two)
{
	args->size_1 = get_arg_size(field[(pos + 1) % MEM_SIZE], 0, dir_is_two);
	args->size_2 = get_arg_size(field[(pos + 1) % MEM_SIZE], 1, dir_is_two);
	args->size_3 = get_arg_size(field[(pos + 1) % MEM_SIZE], 2, dir_is_two);
	args->value_1 = get_val(field, pos + 2, args->size_1);
	args->value_2 = get_val(field, pos + 2 + args->size_1, args->size_2);
	args->value_3 = get_val(field,
							pos + 2 + args->size_1 + args->size_2,
							args->size_3);
}

int					check_register_values(t_args *args,
					bool first, bool second, bool third)
{

	if (!args->size_1 ||
		(args->size_1 == 1 && (args->value_1 > 16 || args->value_1 < 1)) ||
		(first && args->size_1 != 1))
		return (FALSE);

	if ((args->size_2 == 1 && (args->value_2 > 16 || args->value_2 < 1)) ||
		(second && args->size_2 != 1))
		return (FALSE);

	if ((args->size_3 && !args->size_2) ||
		(args->size_3 == 1 && (args->value_3 > 16 || args->value_3 < 1)) ||
		(third && args->size_3 != 1))
		return (FALSE);
		
	return (TRUE);
}
