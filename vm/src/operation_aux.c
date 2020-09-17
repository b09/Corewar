/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operation_aux.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/09 22:34:22 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/09/17 07:48:23 by macbook       ########   odam.nl         */
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
	int				check;

	res = 0;
	i = 0;
	ft_printf("func:%s line %d\n", __func__, __LINE__); //delete
	ft_printf("position: %d, size: %d\n", position, size);
	while (i < size)
	{
		current_byte = field[pos_mem_size(position + i)];
		shift = (((size - 1) * 8) - (i * 8));
		res |= (unsigned int)current_byte << shift;
		i++;
	}
	//ft_printf("res: %d after switch: %d\n", res, switch_endianness(res, size));
	return (res);
}

void				int_to_ustr(int value, unsigned char *field,\
					int position, int size)
{
	unsigned char	current_byte;
	unsigned int	mask;
	int				shift;
	int				i;

	i = 0;
	// value = switch_endianness(value, size);
	while (i < size)
	{
		shift = (((size - 1) * 8) - (i * 8));
		mask = 0xFF << shift;
		current_byte = (unsigned char)((value & mask) >> shift);
		field[pos_mem_size(position + i)] = current_byte;
		++i;
	}
}

int					tind_value(int position, unsigned char *ind_str)
{
	return ((position + *(int*)ind_str) % IDX_MOD);
}
