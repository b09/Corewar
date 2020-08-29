/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   translator.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/08/29 20:36:41 by macbook       ########   odam.nl         */
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
