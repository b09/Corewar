/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/17 16:22:38 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	valid argv strings will be:
**		./corewar batman.cor -dump -n 1 ant-man.cor iron_man.cor
**	and from project pdf:
**		> ./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...
*/

static void		input_validation(int argc, char **argv, t_arena *arena)
{
	int			i;
	int			len;

	i = 1;
	len = 0;
	arena->dump = -1;
	while (i < argc)
	{
		len = ft_strlen(argv[i]);
		if (len > 4 && ft_strequ(".cor", &argv[i][len - 4]))
			validate_champs(argv[i], arena);
		else if ((len == 2 && ft_strequ("-n", argv[i])) ||
				(len == 5 && ft_strequ("-dump", argv[i])))
			validate_flag(argv, arena, &i, len);
		else
			print_error(arena, INVALID_ARG);
		++i;
	}
	validate_ids(arena);
}

/*
**	Malloc for champs
*/

static void		allocate_for_champs(t_champ **all_champs)
{
	int			i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		all_champs[i] = (t_champ*)ft_memalloc(sizeof(t_champ));
		++i;
	}
	all_champs[i] = NULL;
}

int				main(int argc, char **argv)
{
	t_arena		arena;
	t_champ		**all_champs;
	t_func		arrpointer[16];

	if (argc < 2)
	{
		ft_printf("%s", FEW_ARGS);
		exit(1);
	}
	ft_bzero(&arena, sizeof(arena));
	all_champs = (t_champ **)ft_memalloc(sizeof(t_champ*) * (MAX_PLAYERS + 1));
	allocate_for_champs(all_champs);
	arena.champs = all_champs;
	input_validation(argc, argv, &arena);
	intro_champs(&arena);
	initialize_arena(&arena);
	battle(&arena, arrpointer, NULL);
	return (0);
}
