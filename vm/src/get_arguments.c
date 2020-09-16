/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_arguments.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/16 17:27:27 by macbook       ########   odam.nl         */
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
	int ret;
	int	byte;
	int	i;

	ret = 0;
	i = 0;
	while (i < size)
	{
		byte = field[(pos + i) % MEM_SIZE];
		ret |= (byte << (i * 8));
		i++;
	}
	return (ret);
}

/*
**	int pos is current position of cursor
**	pos + 1 is encoding byte
**	pos + 2 is start of arguments
*/

int					populate_arguments(unsigned char *field, int pos,\
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
	if ((args->size_1 == 1 && (args->value_1 > 15 || args->value_1 < 0)) ||
		(args->size_2 == 1 && (args->value_2 > 15 || args->value_2 < 0)) ||
		(args->size_3 == 1 && (args->value_3 > 15 || args->value_3 < 0)))
		return (FALSE);
	return (TRUE);
}
