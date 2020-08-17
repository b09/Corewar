/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/08/14 15:48:34 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	file_valid(int argc, char **argv, t_info info)
{
	char 	*name;
	int		name_len;
	int		fd;

	if (argc != 2)
		return (-1);
	name = argv[1];
	name_len = ft_strlen(name);
	if (name_len <= 2 || name[name_len - 2] != '.' || name[name_len - 1] != 's')
		return (-1);
	info->file_name = ft_memdup(name, name_len - 1);
	info->file_name[name_len - 1] = '\0';
	fd = open(name, O_RDONLY);
	return (fd);
}

int	main(int argc, char **argv)
{
	// char *str = "Assembler main";
	// ft_printf("%s\n", str);
	fd = file_valid(argc, argv, info);
	if (fd == -1)
		return (1);
	lexicon_valid();
	syntax_valid();
	instructions_valid();
	params_valid();
	parse_assembly();
	return (0);
}
