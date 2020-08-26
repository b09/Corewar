/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   translator.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/08/25 20:29:29 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			little_to_big_endian(int number, size_t byte_size)
{
	union u_num
	{
		char char_number[4];
		int int_number;
	}		un;

	un.int_number = number;
	if (byte_size == 4)
	{
		un.char_number[0] ^= un.char_number[3];
		un.char_number[3] ^= un.char_number[0];
		un.char_number[0] ^= un.char_number[3];
		un.char_number[1] ^= un.char_number[2];
		un.char_number[2] ^= un.char_number[1];
		un.char_number[1] ^= un.char_number[2];
	}
	else if (byte_size == 2)
	{
		un.char_number[0] ^= un.char_number[1];
		un.char_number[1] ^= un.char_number[0];
		un.char_number[0] ^= un.char_number[1];
	}
	return (un.int_number);
}

static void		write_to_file(int fd, unsigned char *value, size_t size)
{
	int		i;

	while (size)
	{
		--size;
		ft_putchar_fd(value[size], fd);
	}
}

// static void		write_name(t_asm *asm_obj)
// {
// 	write_to_file(asm_obj->fd, asm_obj);
// }

int			create_and_write_file(t_asm *asm_obj)
{
	int		fd;
	char	*file;
	int		magic_number;

	file = ft_strjoin(asm_obj->file_name, ".cor");
	fd = open(file, O_RDWR | O_APPEND | O_CREAT | O_TRUNC, 0644);
	asm_obj->fd = fd;
	magic_number = COREWAR_EXEC_MAGIC;
	write_to_file(fd, (unsigned char *)&magic_number, 4);
	// write_name();
	return (1);
}

