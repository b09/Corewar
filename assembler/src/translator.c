/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   translator.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/08/27 15:06:17 by macbook       ########   odam.nl         */
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

/*
**	Writes into the '.cor' file the array of bytes provided by an array of chars
**	(which are not a string as they are not null terminated). The amout of bytes
**	written into the file is specified by a size_t param.
**
**	Params:	
**			int fd		==> file descriptor of file being written into
**			uchar *value==> array of u_chars (not a string as not null
**							terminated) to be written into the file
**			size_t size	==> amount of characters to be written into file
**
**	Return:
**			Void
**
**	Called by:
**			write_string()
**			write_exec_size()
**			create_and_write_file()
*/

static void		write_to_file(int fd, unsigned char *value, size_t size)
{
	int		i;

	while (size)
	{
		--size;
		ft_putchar_fd(value[size], fd);
	}
}

/*
**	Writes the string connected to '.name' and '.comment' into the '.cor' file.
**	After the string, a number of trailing zeroes are added the file which are
**	specified by the param 'null_count'
**
**	Params:	
**			t_asm *asm_obj	==> assembler struct initialized by main()
**			char *str		==> string to be written into the file
**			size_t null_cnt	==> amount of zeros to be written after the string
**
**	Return:
**			Void
**
**	Called by:
**			create_and_write_file()
*/

static void		write_string(t_asm *asm_obj, char *str, size_t null_count)
{
	size_t		size;
	
	size = ft_strlen(str);
	write_to_file(asm_obj->fd, (unsigned char *)str, size);
	while (size < null_count)
	{
		write_to_file(asm_obj->fd, (unsigned char *)"", 1);
		++size;
	}
}

/*
**	Writes into the '.cor' file the magic number that identifies the file
**	format as one being a '.cor' file.
**
**	Params:	
**			t_asm *info	==> assembler struct initialized by main()
**
**	Return:
**			Void
**
**	Called by:
**			create_and_write_file()
*/

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

/*
**	Creates a file with the same name as th inputed assembly file, except with a
**	'.cor' extension instead of the '.s' extension. Calls all the funcs
**	responsible for adding different values to the file.
**
**	Params:	
**			t_asm *info	==> assembler struct initialized by main()
**
**	Notes:
**			write_string() will add the strings related to '.name' and 'comment'
**			and each of the these string require 4 bytes of trailing zeroes,
**			which is why the the last param of write_string() contains the max
**			length for each string plus four bytes.
**
**	Return:
**			int
**
**	Called by:
**			main()
*/

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

