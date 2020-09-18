/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntactic_analysis.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/19 19:26:19 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/08/31 16:33:05 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	check_for_duplicate_labels(t_asm *asm_obj)
{
	t_token	*i;
	t_token *j;

	i = asm_obj->token_head;
	while (i)
	{
		while (i && i->type != LABEL_TKN)
			i = i->next;
		if (i)
		{
			j = i->next;
			while (j)
			{
				if (j && j->type == LABEL_TKN && ft_strequ(i->string, j->string))
					return (print_error(SYNTAX_LABEL_DUPLICATE));
				j = j->next;
			}
			i = i->next;
		}
	}
	return (TRUE);
}

/*
**	Called by:	main()
*/

int			valid_syntax(t_asm *asm_obj)
{
	remove_comments_and_extra_nl(asm_obj);
	if (valid_header(asm_obj) == FALSE)
		return (FALSE);
	if (valid_instructions(asm_obj) == FALSE)
		return (FALSE);
	remove_separators_and_nl(asm_obj);
	check_for_duplicate_labels(asm_obj);
	return (TRUE);
}
