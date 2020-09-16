/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_validation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/16 18:08:10 by macbook       ########   odam.nl         */
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

void			get_champ_file(t_champ *champ)
{
	char		buf[EXEC_CODE_MAX_SIZE + CHAMP_MINIMUM_SIZE + 1];
	int			i;
	int			num;

	i = read(champ->fd, &buf, EXEC_CODE_MAX_SIZE + CHAMP_MINIMUM_SIZE + 1);
	if (i == 2857 || i < CHAMP_MINIMUM_SIZE || i == -1)
		print_error(TOO_BIG_OR_SML);
	champ->orig_file = (unsigned char*)ft_memdup(buf, i);
	champ->file_size = i;
	champ->name = &champ->orig_file[4];
	champ->exec_size = &champ->orig_file[8 + PROG_NAME_LENGTH];
	champ->comment = &champ->orig_file[12 + PROG_NAME_LENGTH];
	champ->exec_code = &champ->orig_file[CHAMP_MINIMUM_SIZE];
	champ->alive = TRUE;
	num = COREWAR_EXEC_MAGIC;
	i = ft_memcmp_rev((void*)champ->orig_file, (void*)&num, 4);
	num = 0;
	i |= ft_memcmp((void*)&num, (void*)champ->exec_size - 4, 4) |\
		ft_memcmp((void*)&num, (void*)champ->exec_code - 4, 4);
	num = champ->file_size - CHAMP_MINIMUM_SIZE;
	i |= ft_memcmp_rev((void*)champ->exec_size, (void*)&num, 4);
	(i || !champ->name[0]) && print_error(BAD_BINARY);
	champ->real_exec_size = num;
}

/*
**	if arena->n_flag != 0, current champ will hold that value, and will be
**	checked later to see if valid compared to what other champs have received
*/

void			validate_champs(char *input, t_arena *arena)
{
	t_champ		*champ;

	arena->num_champs++;
	champ = arena->champs[arena->num_champs - 1];
	champ->id = arena->num_champs;
	champ->n_provided = arena->n_flag;
	arena->n_flag = 0;
	champ->file_name = input;
	champ->fd = open(input, O_RDONLY);
	if (champ->fd < 0 || arena->num_champs == MAX_PLAYERS + 1)
		print_error(TOO_MANY_CHAMPS);
	get_champ_file(champ);
}

/*
**	if *argv == -s || -dump, then ++(*argv) should be a digit for both cases
*/

void			validate_flag(char **argv, t_arena *arena, int *argc, int len)
{
	size_t		index;

	index = 0;
	++(*argc);
	while (ft_isdigit(argv[*argc][index]))
		++index;
	if (index != ft_strlen(argv[*argc]) | index > 9)
		print_error(INV_ARG_N_DUMP);
	if (len == 5 && arena->dump == 0)
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
}

/*
**	popupulates n_ids[4] with address of champ at the index provided by
**	champ->n_provided - 1. If there is already an address in n_ids at that index
**	then multiple champs have the same n_provided index, which is an error.
**	for the remaining indeces in n_ids[4] which are zero, func() populates
**	the remaining champ address (which did not have an n_provided) at the first
**	available indeces.
*/

void			grab_n_ids(t_champ *n_ids[4], int n_index, t_champ **champs,\
				int num_champs)
{
	int			i;

	i = 0;
	while (i < num_champs)
	{
		if (champs[i]->n_provided && (champs[i]->n_provided - 1) < 4 &&
		n_ids[champs[i]->n_provided - 1] == NULL)
			n_ids[champs[i]->n_provided - 1] = champs[i];
		else if (champs[i]->n_provided != 0)
			print_error(SAME_N_VALUE);
		++i;
	}
	i = 0;
	while (i < num_champs)
	{
		if (champs[i]->n_provided == 0)
		{
			while (n_index < 4 && n_ids[n_index])
				++n_index;
			n_ids[n_index] = champs[i];
		}
		++i;
	}
}

/*
**	grab all n_ids
**	ensure none are more than champs
**	ensure all are unique
**	assign according to placement of champs
*/

void			validate_ids(t_arena *arena)
{
	t_champ		*n_ids[4];
	int			i;
	t_champ		*champs;

	i = 0;
	ft_bzero(&n_ids, sizeof(n_ids));
	grab_n_ids(n_ids, 0, arena->champs, arena->num_champs);
	while (i < arena->num_champs)
	{
		champs = n_ids[i];
		champs->id = i + 1;
		arena->champs[i] = champs;
		++i;
	}
}
