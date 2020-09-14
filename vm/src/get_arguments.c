/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_arguments.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/14 16:11:55 by macbook       ########   odam.nl         */
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
	if (encode_byte & mask == REG_CODE << shift)
		return (1);
	else if (dir_is_two == FALSE && encode_byte & mask == (DIR_CODE << shift))
		return (4);
	return (2);
}

/*
**	args == 3 x unsigned char [5]
**	first character of each array will be size of argument
**	following bytes will be populated with content of field based on size
**	provided in first byte. if args[i] is for a registry, and its int value in
**	the next byte is too big or small for a registry, value will be zero.
**	ensures that T_REG is whithin 0...15, if not, returns bytes to jump in
**	negative.
**	index of field in get_arg_size(field[(pos + 1)]) is the position of the
**	encoding byte. later, int 'pos' is incremented by two (one byte for the op
**	and one byte for encoding).
**
**	the following loop exists for the below reasons:
**
**	while (x < args[i][SIZE])
**		args[i][x + 1] = field[(pos + x) % MEM_SIZE];
**		x++;
**
**	it exists, instead of using memcpy, because each byte needs to be modulo'd,
**	as memcpy will just take the starting address, and continue copying from
**	start address to size_t end bytes, without caring for the modulo.
*/

int					populate_arguments(unsigned char *field, int pos,\
					unsigned char **args, bool dir_is_two)
{
	int				i;
	int				x;

	i = 0;
	while (i < 3)
	{
		args[i][0] = get_arg_size(field[(pos + 1) % MEM_SIZE], i, dir_is_two);
		++i;
	}
	i = 0;
	pos += 2;
	while (i < 3)
	{
		x = 0;
		while (x < args[i][SIZE])
		{
			args[i][4 - x] = field[(pos + x) % MEM_SIZE];
			x++;
		}
		if (args[i][0] == REG_SIZE && (args[i][4] < 0 || args[i][4] > 15))
			return (0);
		pos += args[i][0];
		i++;
	}
	return (1);
}
