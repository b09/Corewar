/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_arguments.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/09 18:59:47 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	returns size of argument based on encoding byte, and position being checked
**	in encoding_byte (the offset) and, if argument is a T_DIR, also based on
**	dir_two.
*/

char		read_encoding_byte(char encoding_byte, int offset, bool dir_two)
{
	if(encoding_byte == REG_CODE)// bitwise)
		return (SIZE_REG);
	if(encoding_byte == DIR_CODE && dir_two)// bitwise)
		return (SIZE_SDIR);
	if(encoding_byte == DIR_CODE && dir_two == 0)// bitwise)
		return (SIZE_LDIR);
	if(encoding_byte == IND_CODE)// bitwise)
		return (SIZE_IND);
	return (0);
}

/*
**	args == 3 x unsigned char [5]
**	first character of each array will be size of argument
**	following bytes will be populated with content of field based on size
**	provided in first byte. if args[i] is for a registry, and its int value in
**	the next byte is too big or small for a registry, value will be zero.
**	ensures that T_REG is whithin 0...15, if not, returns bytes to jump in
**	negative
*/

int			populate_arguments(unsigned char *field, int position,\
			unsigned char **args, bool dir_is_two)
{
	int		i;
	int		error;

	i = 0;
	error = 1;
	while (i < 3)
	{
		args[i][0] = read_encoding_byte(field[position % MEM_SIZE], i,\
												dir_is_two);
		++i;
	}
	i = 0;
	position++;
	while(i < 3)
	{
		ft_memcpy((void*)args[i][1], field[position % MEM_SIZE], args[i][0]);
		if (args[i][0] == REG_SIZE && (args[i][1] < 0 || args[i][1] > 15))
			error = -1;
		position += args[i][0];
		i++;
	}
	return (position * error);
}
