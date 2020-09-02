/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/02 13:13:43 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
	read arguments
	check if -n
*/

void			input_validation(int argc, char **argv)
{
	if (argc < 3)
		exit(); // do something
	
}


int				main(int argc, char **argv)
{
	t_arena		arena;
	t_champs	champs;

	if (argc < 3)
		exit(1);
	input_validation(argc, argv);
	char *str = argv[1]; // fake line to compile
	str = "Corewar/VM main";
	ft_printf("%s\n", str);
	return (0);
}