/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_funcs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/05 16:22:29 by macbook       ########   odam.nl         */
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
	while (i < arena->num_champs)
	{
		// champ = arena->champs;
		// // champ = champs[0];
		// ft_printf("addr:%p\n", champ[i]);
		// ft_printf("id:%d\n", champ[i].id);
		// ft_printf("name:%s\n", champ[i].name);
		// ft_printf("comment:%s\n", champ[i].comment);
		// ft_printf("exec_size:%d\n", champ[i].exec_size);
		// ft_printf("file_name:%s\n", champ[i].file_name);
		// ft_printf("file_size:%d\n\n", champ[i].file_size);
		// ++i;
		champ = arena->champs[i];
		// champ = champs[0];
		ft_printf("addr: %p\n", champ);
		ft_printf("id: %d\n", champ->id);
		ft_printf("name: %s\n", champ->name);
		ft_printf("comment: %s\n", champ->comment);
		ft_printf("real_exec_size: %d\n", champ->real_exec_size);
		ft_printf("file_name: %s\n", champ->file_name);
		ft_printf("file_size: %d\n\n", champ->file_size);
		++i;
	}
}

int				print_error(char *str)
{
	ft_printf("%s", str);
	exit(1);
}

void			intro_champs(t_arena *arena)
{
	int			i;
	t_champ		*champ;

	i = 0;
	champ = NULL;
	ft_printf("LLLeetttttt'sss get reaaddyyyyyy to SEGFAUUULLLT!!!!!!\n");
	ft_printf("\tWOohoo!! Yeahhhhhh!! (crowd cheeers)\n\n");
	while (i < arena->num_champs)
	{
		champ = arena->champs[i];
		ft_printf("Player %d, weighing in at %d bytes, \"%s\" (%s)\n", i + 1, \
		champ->real_exec_size, champ->name, champ->comment);
		++i;
	}

}