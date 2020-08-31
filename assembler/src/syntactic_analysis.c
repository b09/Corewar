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

/*
**	Called by:	main()
*/

int		valid_syntax(t_asm *asm_obj)
{
	remove_comments_and_extra_nl(asm_obj);
	if (valid_header(asm_obj) == FALSE)
		return (FALSE);
	if (valid_instructions(asm_obj) == FALSE)
		return (FALSE);
	remove_separators_and_nl(asm_obj);
	return (TRUE);
}
