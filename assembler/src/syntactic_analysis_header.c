/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntactic_analysis_header.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/26 17:53:23 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/08/30 19:23:27 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	del_cmd_str_and_nl(t_asm *asm_obj, t_token **token)
{
	t_token	*token_cmd;
	t_token	*token_str;
	t_token	*token_nl;

	token_cmd = *token;
	token_str = token_cmd->next;
	token_nl = token_str->next;
	if (token_nl == NULL)
		print_error(SYNTAX_MISSING_NL)
	*token = token_nl->next;
	token_unlink_del(asm_obj, token_cmd);
	token_unlink_del(asm_obj, token_str);
	token_unlink_del(asm_obj, token_nl);
}

/*
**	Checks name_command token for validity.
**	name_command is valid when followed by a string that can be size
**	of 1 up to PROG_NAME_LENGTH, which is currently set to 128.
**
**	Input: asm_obj
**
**	Return: True or False
**	Called by:	valid_header()
*/

static int	valid_name_cmd(t_asm *asm_obj)
{
	t_token		*current;
	t_token		*next;
	size_t		len;

	current = asm_obj->token_head;
	if (current->next->type != STRING_TKN)
		return (print_error(SYNTAX_NO_NAME_STR));
	asm_obj->champ_name = ft_strdup(current->next->string);
	del_cmd_str_and_nl(asm_obj, &current);
	if (ft_strlen(asm_obj->champ_comment) > PROG_NAME_LENGTH)
		print_error(SYNTAX_NAME_LONG);
	return (TRUE);
}

/*
**	Checks comment_command token for validity.
**	comment_command is valid when followed by a string that can be size
**	of 0 up to COMMENT_LENGTH, which is currently set to 2048.
**
**	Input: asm_obj
**
**	Return: True or False
**	Called by:	valid_header()
*/

static int	valid_comment_cmd(t_asm *asm_obj)
{
	t_token		*current;
	t_token		*next;

	current = asm_obj->token_head;
	if (current->next->type != STRING_TKN)
		return (print_error(SYNTAX_NO_CMNT_STR));
	asm_obj->champ_comment = ft_strdup(current->next->string);
	del_cmd_str_and_nl(asm_obj, &current);
	if (ft_strlen(asm_obj->champ_comment) > COMMENT_LENGTH)
		print_error(SYNTAX_CMNT_LONG);
	return (TRUE);
}

/*
**	Makes sure the header is formatted properly,
**	removes header tokens from linked list,
**	stores header strings in asm_obj.
**
**	Header is formatted properly if it has .name and .comment in any order,
**	both with their properly formatted strings.
**
**	Input: asm_obj
**
**	Return: True or False
**
**	Called by: valid_syntax()
*/

int			valid_header(t_asm *asm_obj)
{
	t_token		*current;

	current = asm_obj->token_head;
	if (current->type != COMMAND_TKN)
		return (print_error(SYNTAX_NO_NAME));
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
	return (print_error(SYNTAX_HEADER_INVALID));
}
