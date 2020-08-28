/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntactic_analysis_header.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/26 17:53:23 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/08/27 17:02:04 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				valid_instructions(t_asm *asm_obj)
{
	return (1);
}

static void		remove_separators_and_nl(t_asm *asm_obj)
{
	t_token		*current;
	t_token		*next;

	current = asm_obj->token_head;
	while (current)
	{
		next = current->next;
		if (current->type == SEPARATOR_TKN || current->type == ENDLINE_TKN)
			token_unlink_del(asm_obj, current);
		current = next;
	}
}

static int		valid_name_cmd(t_asm *asm_obj)
{
	t_token		*current;
	t_token		*next;
	size_t		len;

	current = asm_obj->token_head;
	if (current->next->type != STRING_TKN)
	{
		// ft_printf("Syntax error: expected string after .name in header.\n");
		// return (FALSE);
		return (print_error(SYNTAX_NO_NAME_STR));
	}
	asm_obj->name_cmd_string = ft_strdup(current->next->string);
	next = current->next->next->next;
	while (current != next)
	{
		token_unlink_del(asm_obj, current);
		current = asm_obj->token_head;
	}
	len = ft_strlen(asm_obj->name_cmd_string);
	return (len > 0 && len <= PROG_NAME_LENGTH ? TRUE : FALSE);
}

static int		valid_comment_cmd(t_asm *asm_obj)
{
	t_token		*current;
	t_token		*next;
	size_t		len;

	current = asm_obj->token_head;
	if (current->next->type != STRING_TKN)
	{
		// ft_printf("Syntax error: expected string after .comment in header.\n");
		// return (FALSE);
		return (print_error(SYNTAX_NO_CMNT_STR));
	}
	asm_obj->comment_cmd_string = ft_strdup(current->next->string);
	next = current->next->next->next;
	while (current != next)
	{
		token_unlink_del(asm_obj, current);
		current = asm_obj->token_head;
	}
	len = ft_strlen(asm_obj->comment_cmd_string);
	return (len > 0 && len <= PROG_NAME_LENGTH ? TRUE : FALSE);
}

/*
**	Makes sure the header is formatted properly,
**	removes header tokens from linked list,
**	stores header strings in asm_obj.
**
**	Header is formatted properly if it has .name and .comment in any order,
**	both with their properly formatted strings.
*/

int				valid_header(t_asm *asm_obj)
{
	t_token		*current;

	current = asm_obj->token_head;
	if (current->type != COMMAND_TKN)
	{
		// ft_printf("Syntax error: expected .name and .comment in header.\n");
		// return (FALSE);
		return (print_error(SYNTAX_NO_NAME));
	}
	else if (ft_strequ(current->string, NAME_CMD_STRING))
	{
		valid_name_cmd(asm_obj);
		current = asm_obj->token_head;
		if (ft_strequ(current->string, COMMENT_CMD_STRING))
			return (valid_comment_cmd(asm_obj));
	}
	else if (ft_strequ(current->string, COMMENT_CMD_STRING))
	{
		valid_comment_cmd(asm_obj);
		current = asm_obj->token_head;
		if (ft_strequ(current->string, NAME_CMD_STRING))
			return (valid_name_cmd(asm_obj));
	}
	return (FALSE);
}
