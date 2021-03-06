/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operation_aux.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/09 22:34:22 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/09/19 17:34:26 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int					switch_endianness(int n, size_t size)
{
	int				res;

	res = 0;
	if (size == 1)
		return (n);
	else if (size == 2)
		res = ((n >> 8) | (n << 8)) & 0xFFFF;
	else if (size == 4)
	{
		res |= ((n >> (8 * 3)) & 0x000000FF);
		res |= ((n << (8 * 1)) & 0x00FF0000);
		res |= ((n >> (8 * 1)) & 0x0000FF00);
		res |= ((n << (8 * 3)) & 0xFF000000);
	}
	return (res);
}

int					pos_mem_size(int position)
{
	position = position % MEM_SIZE;
	if (position < 0)
		return (position + MEM_SIZE);
	return (position);
}

int					ustr_to_int(unsigned char *field, int position, int size)
{
	unsigned char	current_byte;
	unsigned int	res;
	int				i;
	int				shift;

	res = 0;
	i = 0;
	while (i < size)
	{
		current_byte = field[pos_mem_size(position + i)];
		shift = (size - 1) - i;
		res |= (unsigned int)current_byte << (shift * 8);
		i++;
	}
	if (size == 2)
		return ((short)res);
	return (res);
}

void				int_to_ustr(int value, unsigned char *field,\
					int position, int size)
{
	int str[4];

	str[0] = (value >> 24) & 255;
	str[1] = (value >> 16) & 255;
	str[2] = (value >> 8) & 255;
	str[3] = value & 255;
	if (size == 2)
	{
		field[pos_mem_size(position + 2)] = str[2];
		field[pos_mem_size(position + 3)] = str[3];
	}
	if (size == 4)
	{
		field[pos_mem_size(position)] = str[0];
		field[pos_mem_size(position + 1)] = str[1];
		field[pos_mem_size(position + 2)] = str[2];
		field[pos_mem_size(position + 3)] = str[3];
	}
}

void				op_helper(t_args *args, int position, t_arena *arena,
					t_cursor *cursor)
{
	int				value1;
	int				value2;

	if (args->size_1 == SIZE_IND)
	{
		position = position + args->value_1 % IDX_MOD;
		value1 = ustr_to_int(arena->field, position, 2);
	}
	else
		value1 = (args->size_1 != 1) ? args->value_1 :
											cursor->registry[args->value_1 - 1];
	if (args->size_2 == SIZE_IND)
	{
		position = position + args->value_2 % IDX_MOD;
		value2 = ustr_to_int(arena->field, position, 2);
	}
	else
		value2 = (args->size_2 != 1) ? args->value_2 :
											cursor->registry[args->value_2 - 1];
	args->value_1 = value1;
	args->value_2 = value2;
}
