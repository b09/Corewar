/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/08/30 22:11:54 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	Checks if file is valid, populates t_asm.
**	Stores file_name and file_content.
**	file_name is needed to name final assembly output, ie <file_name>.cor
**
**	Rules:
**			Only one argument (file name)
**			File name must end ".s"
**
**	Params:
**			char **argv	==> main() args
**			int	argc	==> main() args
**			t_asm info	==> main assembler struct
**
**	Notes:
**			gnl_with_newline() will include '\n' in str
**			file_name copied WITHOUT '.s' extension
**
**	Return:
**			FALSE (0)= invalid file
**			TRUE (1) = valid file
**
**	Called by:	main()
*/

static int		read_file(int argc, char **argv, t_asm *info)
{
	char		*str;
	int			name_len;
	int			fd;

	if (argc != 2)
		return (print_error(NUM_ARGS_INVALID));
	str = argv[1];
	name_len = ft_strlen(str);
	if (name_len <= 2 || str[name_len - 2] != '.' || str[name_len - 1] != 's')
		return (print_error(FILE_TYPE_INVALID));
	info->file_name = ft_strndup(str, name_len - 2);
	info->fd = open(str, O_RDONLY);
	tokenize(str, info, 0);
	return (TRUE);
}

/*
**
**	Params:		info struct
**
**	Return:		TRUE or FALSE depending on validity
**
**	called by:	main()
*/

static int		lexicon_valid(t_asm *info)
{
	t_token		*curr;

	curr = info->token_head;
	while (curr)
	{
		if (valid_token(curr) == FALSE)
		{
			ft_putendl_fd("Invalid token", 2);
			exit (1);
		}
		curr = curr->next;
	}
	return (TRUE);
}

int				main(int argc, char **argv)
{
	t_asm		asm_obj;

	ft_bzero(&asm_obj, sizeof(asm_obj));
	if (read_file(argc, argv, &asm_obj) == FALSE) // were here
		return (1);
	lexicon_valid(&asm_obj);
	valid_syntax(&asm_obj);
	// create_and_write_file(&asm_obj);
	// instructions_valid();
	// params_valid();
	// parse_assembly();
	return (0);
}
