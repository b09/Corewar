/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/04 20:00:22 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	there is a maximum and minimum size that must exist for file
**	file must be:
**	[MAGIC HEADER 4bytes][PROG_NAME_LENGTH][NULL 4bytes][EXEC_SIZE 4 bytes]
**	[COMMENT_LENGTH][NULL 4bytes][EXEC_CODE (0...EXEC_CODE_MAX_SIZE)bytes]
**	checks:
**		magic number is correct
**		null bytes are correctly placed
**		exec_size is the same size as counted bytes in binary
**		champ name exists
*/

static void		get_champ_file(t_champ *champ)
{
	char		buf[EXEC_CODE_MAX_SIZE + CHAMP_MINIMUM_SIZE + 1];
	int			i;
	int			num;

	i = read(champ->fd, &buf, EXEC_CODE_MAX_SIZE + CHAMP_MINIMUM_SIZE + 1);
	if (i == 2857 || i < CHAMP_MINIMUM_SIZE || i == -1)
		ft_printf("File is either too big or small");//print_error(); //do something here
	champ->orig_file = (unsigned char *)ft_memalloc(i);
	ft_memcpy((void *)champ->orig_file, (void*)buf, i);
	champ->file_size = i;
	champ->name = &champ->orig_file[4];
	champ->exec_size = &champ->orig_file[8 + PROG_NAME_LENGTH];
	champ->comment = &champ->orig_file[12 + PROG_NAME_LENGTH];
	champ->exec_code = &champ->orig_file[CHAMP_MINIMUM_SIZE];
	num = COREWAR_EXEC_MAGIC;
	i = ft_memcmp_rev((void*)champ->orig_file, (void*)&num, 4);
	num = 0;
	i |= ft_memcmp((void*)&num, (void*)champ->exec_size - 4, 4) |\
		ft_memcmp((void*)&num, (void*)champ->exec_code - 4, 4);
	num = champ->file_size - CHAMP_MINIMUM_SIZE;
	i |= ft_memcmp_rev((void*)champ->exec_size, (void*)&num, 4);
	(i || !champ->name[0]) && ft_printf("binary is not formatted correctly\n"); // print_error();
}

/*
**	if arena->n_flag != 0, current champ will hold that value, and will be
**	checked later to see if valid compared to what other champs have received
*/

static void		validate_champs(char *input, t_arena *arena)
{
	int			len;
	t_champ		*champ;

	arena->num_champs++;
	champ = &arena->champs[arena->num_champs - 1];
	champ->id = arena->num_champs;
	champ->id = arena->n_flag;
	arena->n_flag = 0;
	champ->fd = open(input, O_RDONLY);
	if (champ->fd < 0 || arena->num_champs == MAX_PLAYERS + 1)
		ft_printf("Too many champs\n"); //print_error(); // not define here
	get_champ_file(&arena->champs[arena->num_champs - 1]);
}

/*
**	if *argv == -s || -dump, then ++(*argv) should be a digit for both cases
*/

static void		validate_flag(char **argv, t_arena *arena, int *argc, int len)
{
	int			index;

	index = 0;
	++(*argc);
	while (ft_isdigit(argv[*argc][index]))
		++index;
	if (index == ft_strlen(argv[*argc]) && index < 10)
		print_error(INV_ARG_N_DUMP);
	if (len == 5 && arena->dump == 0) // is '-dump'
	{
		arena->dump = ft_atoi(argv[*argc]);
		arena->dump == 0 && print_error(INVALID_DUMP);
	}
	else if (len == 2 && arena->n_flag == 0)
	{
		arena->n_flag = ft_atoi(argv[*argc]);
		arena->n_flag == 0 && print_error(INVALID_N);
	}
	else
		print_error(MULTIPLE_N);
	return ;
}

/*
**	popupulates n_ids[4] with address of champ at the index provided by
**	champ->n_provided. If there is already an address in n_ids at that index
**	then multiple champs have the same n_provided index, which is an error.
**	for the remaining indeces in n_ids[4] which are zero, func() populates
**	the remaining champ address (which did not have an n_provided) at the first
**	available indeces.
*/
static void		grab_n_ids(t_champ *n_ids[4], t_arena *arena, int n_index)
{
	int			i;
	t_champ		**champs;

	i = 0;
	champs = &arena->champs;
	while (i < arena->num_champs)
	{
		if (champs[i]->n_provided < 4 && n_ids[champs[i]->n_provided] == NULL)
			n_ids[champs[i]->n_provided] = champs[i];
		else
			print_error(SAME_N_VALUE);
		++i;
	}
	i = 0;
	while (i < arena->num_champs)
	{
		if (champs[i]->n_provided == 0)
		{
			while (n_index < 4 && n_ids[n_index])
				++n_index;
			n_ids[n_index] = champs[i];
		}
	}
}


/*
**	grab all n_ids
**	ensure none are more than champs
**	ensure all are unique
**	assign according to placement of champs
*/

static void		validate_ids(t_arena *arena)
{
	t_champ		*n_ids[4];
	int			i;
	t_champ		*champs;

	i = 0;
	ft_bzero(&n_ids, sizeof(n_ids));
	grab_n_ids(n_ids, arena, 0);
	while (i < arena->num_champs)
	{
		champs = n_ids[i];
		champs->id = i;
		++i;
	}
}

/*
**	valid argv strings will be:
**		./corewar batman.cor -dump -n 1 ant-man.cor iron_man.cor
**	and from project pdf:
**		> ./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...
*/

static void		input_validation(int argc, char **argv, t_arena *arena)
{
	int 		i;
	int			len;

	i = 1;
	len = 0;
	while (i < argc)
	{
		len = ft_strlen(argv[i]);
		if (len > 4 && ft_strequ(".cor", &argv[i][len - 4]))
			validate_champs(argv[i], arena);
		else if ((len == 2 && ft_strequ("-n", argv[i])) || (len == 5 &&\
												ft_strequ("-dump", argv[i])))
			validate_flag(argv, arena, &i, len);
		else
			print_error(INVALID_ARG);
		++i;
	}
	// validate_ids(arena);
	print_champs(arena);
}

int				main(int argc, char **argv)
{
	t_arena		arena;
	t_champ		*champs;

	// if (argc < 3)
	if (argc < 2) // for debugging
		print_error(FEW_ARGS);
	ft_bzero(&arena, sizeof(arena));
	champs = (t_champ *)ft_memalloc(sizeof(t_champ) * MAX_PLAYERS + 1);
	arena.champs = champs;
	input_validation(argc, argv, &arena);
	return (0);
}