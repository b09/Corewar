/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_funcs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/08/27 13:06:20 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	Debub function, prints values of t_asm *obj members and linked list of tokns
**
**  Params:	
**			t_asm *obj	==> main assembler struct
**
*/

void			print_asm_obj(t_asm *asm_obj)
{
	t_token		*tokens;
	int			token_number;

	token_number = 0;
	tokens = asm_obj->token_head;
	ft_printf("file_name: [%s]", asm_obj->file_name);
	while (tokens != asm_obj->token_tail && token_number < 200)
	{
		ft_printf("Token %d\n", token_number++);
		ft_printf("t string: ["C_BLUE"%7s"C_RESET"]\t", tokens->type != 51 ?\
													tokens->string : "\\n");
		ft_printf("t type: %-5d ", tokens->type);
		ft_printf("position:[%d:%d]\n\n", tokens->row, tokens->col);
		tokens = tokens->next;
	}
}

int				print_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(0);
}