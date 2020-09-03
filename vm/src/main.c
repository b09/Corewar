/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/03 17:43:43 by macbook       ########   odam.nl         */
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

static void			get_champ_file(t_champ *champ)
{
	char			buf[EXEC_CODE_MAX_SIZE + CHAMP_MINIMUM_SIZE + 1];
	int				i;
	int				num;

	i = read(champ->fd, &buf, EXEC_CODE_MAX_SIZE + CHAMP_MINIMUM_SIZE + 1);
	if (i == 2857 || i < CHAMP_MINIMUM_SIZE || i == -1)
		ft_printf("File is either too big or small");//print_error(); //do something here
	champ->orig_file = (unsigned char *)ft_memalloc(i);
	ft_memcpy((void *)champ->orig_file, (void*)buf, i);
	champ->file_size = i;
	champ->name = &champ->orig_file[4];
	champ->exec_size = &champ->orig_file[4 + 4 + PROG_NAME_LENGTH];
	champ->comment = &champ->orig_file[4 + 4 + PROG_NAME_LENGTH + 4];
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

static void			validate_champs(char *input, t_arena *arena)
{
	int			len;
	t_champ		*champ;

	ft_printf("*** %s() ***\n", __func__);
	arena->num_champs++;
	champ = arena->champs[arena->num_champs - 1];
	champ->id = arena->num_champs;
	champ->fd = open(input, O_RDONLY);
	if (champ->fd < 0 || arena->num_champs == 5)
		ft_printf("Too many champs\n"); //print_error(); // not define here
	get_champ_file(champ);
}

	// check for flags
static void			validate_flag(char *str, t_arena *arena, int *i)
{
	return ;
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
	// if (argc < 3)
	if (argc < 2) // for testing
		ft_printf("Too few arguments provided\n"); // do something
	while (i < argc)
	{
		len = ft_strlen(argv[i]);
		if (len > 4 && ft_strequ(".cor", &argv[i][len - 4]))
			validate_champs(argv[i], arena);
		else if ((len == 2 && ft_strequ("-n", argv[i])) || (len == 5 &&\
												ft_strequ("-dump", argv[i])))
			validate_flag(argv[i], arena, &i);
		else
			ft_printf("Wrong type of argument provided\n"); //print_error(); // do something
		++i;
	}	
	print_champs(arena);
}

int				main(int argc, char **argv)
{
	t_arena		arena;
	t_champ		champs[5];
	t_champ		*champs_pointer;

	// if (argc < 3)
	if (argc < 2) // for testing
		exit(1);
	ft_bzero(&arena, sizeof(arena));
	ft_bzero(&champs, sizeof(champs));
	champs_pointer = champs;
	arena.champs = &champs_pointer;
	input_validation(argc, argv, &arena);
	return (0);
}