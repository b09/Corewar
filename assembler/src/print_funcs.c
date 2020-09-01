/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_funcs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/01 18:17:45 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	Debub function, prints values of t_asm *obj members and linked list of tokns
**
**  Params:
**			t_asm *obj	==> main assembler struct
*/

void			print_asm_obj(t_asm *asm_obj)
{
	t_token		*tokens;
	int			token_number;

	token_number = 0;
	tokens = asm_obj->token_head;
	// ft_printf("file_name: [%s]", asm_obj->file_name);
	while (tokens != asm_obj->token_tail && token_number < 4000)
	{
		// ft_printf("Token %d\n", token_number++);
		// ft_printf("["C_BLUE"%7s"C_RESET"]", tokens->type != 51 ?\
		// 											tokens->string : "\\n");
		ft_printf("["C_BLUE"%7s"C_RESET"]%d %d\t", tokens->string, tokens->translation_size, tokens->bytecode);
		// ft_printf("t type: %-5d ", tokens->type);
		// ft_printf("position:[%d:%d] ", tokens->row, tokens->col);
		// ft_printf("translation size: %-5d ", tokens->translation_size);
		// if (tokens->t_oper)
		// {
		// 	ft_printf(C_CYAN"op_str:%s ", tokens->t_oper->op_str);
		// 	ft_printf("# args:%d ", tokens->t_oper->number_of_args);
		// 	ft_printf("args[0]:%d ", tokens->t_oper->args[0]);
		// 	ft_printf("opcode:%d ", tokens->t_oper->opcode);
		// 	ft_printf("cycles:%d ", tokens->t_oper->cycles);
		// 	ft_printf("descript:%s ", tokens->t_oper->description);
		// 	ft_printf("encoding:%d ", tokens->t_oper->encoding);
		// 	ft_printf("lbl_2_byt:%d"C_RESET, tokens->t_oper->label_is_twobytes);
		// }
		// ft_printf("\n\n");
		tokens = tokens->next;
	}
}

int				print_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(0);
}
