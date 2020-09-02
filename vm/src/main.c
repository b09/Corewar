/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/02 21:34:00 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
	read arguments
	check if -n
	● argc == 1 -> show usage
● check for flags
● number given for ‘-n’ -flag > CHAMPS_MAX_SIZE -> error
● every file has .cor extension
● more .cor files than CHAMPS_MAX_SIZE -> ”Too many champions”
*/

void			read_champ_file(t_champ *champ)
{
	// check magic number
	// check name
	// check comment
	// check size and stated size (could differ)
}

/*
**	there is a maximum and minimum size that must exist for file
**	file must be:
**	[MAGIC HEADER 4bytes][PROG_NAME_LENGTH][NULL 4bytes][EXEC_SIZE 4 bytes]
**	[COMMENT_LENGTH][NULL 4bytes][EXEC_CODE (0...EXEC_CODE_MAX_SIZE)bytes]
*/

void			get_file(t_champ *champ)
{
	char		buf[EXEC_CODE_MAX_SIZE + CHAMP_MINIMUM_SIZE + 1];
	int			i;

	i = read(champ->fd, &buf, EXEC_CODE_MAX_SIZE + CHAMP_MINIMUM_SIZE + 1);
	if (i == 2857 || i < CHAMP_MINIMUM_SIZE || i == -1)
		print_error(); //do something here
	champ->orig_file = (unsigned char *)ft_memalloc(i);
	champ->file_size = i;
	champ->name = &champ->orig_file[4];
	champ->exec_size = &champ->orig_file[4 + 4 + PROG_NAME_LENGTH];
	champ->comment = &champ->orig_file[4 + 4 + PROG_NAME_LENGTH + 4];
	champ->exec_code = &champ->orig_file[CHAMP_MINIMUM_SIZE];
}

void			validate_champs(char *input, t_arena *arena)
{
	int			len;
	t_champ		*champ;

	champ = arena->champs[arena->num_champs];
	arena->num_champs++;
	champ->fd = open(input, O_RDONLY);
	if (champ->fd < 0)
		print_error(); // not define here
	get_file(champ);
		

	// check that number of champs does not exceed MAX_PLAYERS
	// check that every file ends '.cor'
	// check for flags
	// input champ file into champ struct
	// parse champ file
	return (FALSE);
}

void			validate_flags()
{
	
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
	if (argc < 3)
		exit(1); // do something
	while (i < argc)
	{
		len = ft_strlen(argv[i]);
		if (len > 4 && ft_strequ(".cor", argv[i][len - 4]))
			validate_champs(argv[i], arena);
		else if ((len == 2 && ft_strequ("-n", argv[i])) || (len == 5 &&\
												ft_strequ("-dump", argv[i])))
			validate_flag(argv[i], arena, &i);
		else
			print_error(); // do something
		++i;
	}	
}

int				main(int argc, char **argv)
{
	t_arena		arena;
	t_champ		champs[4];

	if (argc < 3)
		exit(1);
	ft_bzero(&arena, sizeof(arena));
	ft_bzero(&champs, sizeof(champs));
	arena.champs = &champs;
	input_validation(argc, argv, &arena);
	return (0);
}