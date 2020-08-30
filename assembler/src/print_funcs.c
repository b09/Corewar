/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_funcs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/08/30 20:50:58 by macbook       ########   odam.nl         */
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
	t_op		*op;
	int			token_number;

	token_number = 0;
	tokens = asm_obj->token_head;
	ft_printf("file_name: [%s]", asm_obj->file_name);
	while (tokens != asm_obj->token_tail && token_number < 40)
	{
		ft_printf("Token %d\n", token_number++);
		ft_printf("t string: ["C_BLUE"%7s"C_RESET"]\t", tokens->type != 51 ?\
													tokens->string : "\\n");
		ft_printf("t type: %-5d ", tokens->type);
		ft_printf("position:[%d:%d] ", tokens->row, tokens->col);
		ft_printf("t type: %-5d ", tokens->translation_size);
		if (tokens->t_op)
		{
			ft_printf(C_CYAN"op_str:%s ", tokens->t_op->op_str);
			ft_printf("# args:%d ", tokens->t_op->number_of_args);
			ft_printf("args[0]:%d ", tokens->t_op->args[0]);
			ft_printf("opcode:%d ", tokens->t_op->opcode);
			ft_printf("cycles:%d ", tokens->t_op->cycles);
			ft_printf("descript:%s ", tokens->t_op->description);
			ft_printf("encoding:%d ", tokens->t_op->encoding);
			ft_printf("label_2_byt:%d"C_RESET, tokens->t_op->label_is_twobytes);
		}
		ft_printf("\n\n");
		tokens = tokens->next;
	}
}

int				print_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(0);
}