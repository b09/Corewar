/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_funcs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/03 17:47:05 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		print_champs(t_arena *arena)
{
	int			i;
	t_champ 	**champs;
	t_champ 	*champ;

	ft_printf("*** %s() ***\n", __func__);
	i = 0;
	// while (arena->champs[i])
	// {
		champs = arena->champs;
		champ = champs[0];
		ft_printf("id:%p\n", champ);
		ft_printf("id:%d\n", champ->id);
		ft_printf("name:%s\n", champ->name);
		ft_printf("comment:%s\n", champ->comment);
		ft_printf("exec_size:%s\n", champ->exec_size);
		ft_printf("file_name:%s\n", champ->file_name);
		ft_printf("file_size:%s\n\n", champ->file_size);
		++i;
	// }
}