/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   translator.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/08/26 18:58:01 by macbook       ########   odam.nl         */
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

static void		write_string(t_asm *asm_obj, char *str, size_t null_count)
{
	size_t		size;
	
	size = ft_strlen(str);
	write_to_file(asm_obj->fd, str, size);
	while (size < null_count)
	{
		write_to_file(asm_obj->fd, "", 1);
		++size;
	}
}


// static void		write_comment(t_asm *asm_obj, char *str)
// {
// 	size_t		size;
	
// 	size = ft_strlen(str);
// 	write_to_file(asm_obj->fd, str, size);
// 	if (str == asm_obj->champ_name)
// 	{
// 		while (size < COMMENT_LENGTH)
// 		{
// 			write_to_file(asm_obj->fd, "", 1);
// 			++size;
// 		}
// 	}
// }

// static void		write_name(t_asm *asm_obj, char *str)
// {
// 	size_t		size;
	
// 	size = ft_strlen(str);
// 	write_to_file(asm_obj->fd, str, size);
// 	while (size < PROG_NAME_LENGTH + 4) // after name, 4 null bytes must be written, according to cookbook
// 	{
// 		write_to_file(asm_obj->fd, "", 1);
// 		++size;
// 	}
// }

static void		write_exec_size(t_asm *asm_obj)
{
	size_t		size;
	t_token		*tokens;

	size = 0;
	tokens = asm_obj->instructions_head;
	while (tokens)
	{
		++size;
		tokens = tokens->next;
	}
	write_to_file(asm_obj->fd, (unsigned char *)&size, 4);
}

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
	write_string(asm_obj, asm_obj->champ_name, PROG_NAME_LENGTH + 4); // write_name with 4 byte null
	write_string(asm_obj, asm_obj->champ_name, COMMENT_LENGTH + 4); // write comment
	write_exec_size(asm_obj);
	return (1);
}

