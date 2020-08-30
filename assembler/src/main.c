/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/08/30 12:21:57 by macbook       ########   odam.nl         */
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
		return (FALSE);
	str = argv[1];
	name_len = ft_strlen(str);
	if (name_len <= 2 || str[name_len - 2] != '.' || str[name_len - 1] != 's')
		return (FALSE);
	info->file_name = ft_strndup(str, name_len - 2);
	info->fd = open(str, O_RDONLY);
	tokenize(str, info);
	print_asm_obj(info);
	return (TRUE);
}


int				main(int argc, char **argv)
{
	t_asm		asm_obj;

	ft_bzero(&asm_obj, sizeof(asm_obj));
	if (read_file(argc, argv, &asm_obj) == FALSE)
		return (1);
	create_and_write_file(&asm_obj);
	// lexicon_valid(&asm_obj);
	// syntax_valid();
	// instructions_valid();
	// params_valid();
	// parse_assembly();
	return (0);
}









/*
**			REVIEW BELOW FUNCTIONS WITH FLAVIO
**			REVIEW BELOW FUNCTIONS WITH FLAVIO
**			REVIEW BELOW FUNCTIONS WITH FLAVIO
**			REVIEW BELOW FUNCTIONS WITH FLAVIO
**			REVIEW BELOW FUNCTIONS WITH FLAVIO
**			REVIEW BELOW FUNCTIONS WITH FLAVIO
*/





/*
**	Finds quotation marks in a larger string and returns substring.
**
**	Params:
**			char *str	==> contains "... <to_return> ..."
**
**	Return:
**			isolated string "<to_return>"
**
**	Called by:	none
*/

static char		*get_name_comment(char *str)
{
	char		*start;
	char		*end;
	char		*name;

	start = ft_strchr(str, '"') + 1;
	end = ft_strchr(start, '"');
	name = ft_memdup(start, end - start);
	name[end - start - 1] = '\n';
	return (name);
}


/*
**	Validates string by checking each char against list of legal chars
**
**	Params:
**			char *str	==> string from a LABEL type token
**
**	Return:
**			FALSE (0)= invalid str
*			TRUE (1) = valid str
**
**	Called by:	none
*/

static int		only_label_chars(char *str)
{
	while (str)
	{
		if (ft_strchr(LABEL_CHARS, *str) == NULL)
			return (FALSE);
		++str;
	}
	return (TRUE);
}

/*
**	If the lexicon is valid this function stores info->name and info->comment
**
**	Params:		info struct
**	Return:		TRUE or FALSE depending on validity
**	called by:	main()
*/

// static int	lexicon_valid(t_asm *info)
// {
// 	t_list	*curr;

// 	curr = info->file_content;
// 	while (curr)
// 	{
// 		// Skip comment
// 		if (curr->content[0] == COMMENT_CHAR || curr->content[0] == ';')
// 			;
// 		// Check that only .name and .comment start with '.'
// 		// Store name and content in info.
// 		// TODO:
// 		// .name and .comment at the top of the file, order doesn't matter.
// 		// can have empty lines in between .name and .comment
// 		else if (curr->content[0] == '.')
// 		{
// 			if (ft_memcmp(curr->content, NAME_CMD_STRING, 5) == 0)
// 				info->name = get_name_comment(curr->content);
// 			else if (ft_memcmp(curr->content, COMMENT_CMD_STRING, 8) == 0)
// 				info->comment = get_name_comment(curr->content);
// 			else
// 				return (FALSE);
// 		}
// 		// Check that LABELS and INSTRUCTIONS only contain LABEL_CHARS
// 		else if (is_label(curr->content) || is_instruction(curr->content))
// 			if (only_label_chars(curr->content) == FALSE)
// 				return (FALSE);
// 		curr = curr->next;
// 	}
// }

static int		lexicon_valid(t_asm *info)
{
	t_token		*curr;

	curr = info->token_head;
	while (curr)
	{
		// if (curr->type == 51)
		// 	ft_printf("{%d}, {'nl'}\n", curr->type); // remove
		// else
		// 	ft_printf("{%d}, {%s}\n", curr->type, curr->string); // remove
		if (valid_token(curr) == FALSE)
		{
			ft_putendl_fd("Invalid token", 2);
			exit (1);
		}
		curr = curr->next;
	}
	return (TRUE);
}

//	********* DO NOT DELETE, COMMENTED OUT FOR COMPILATION ******
// static int	syntax_valid(t_asm *asm_obj)
// {
// 	t_token	*curr;

// 	curr = asm_obj->token_head;
// 	while (curr)
// 	{
// 		// if (curr->type == 51)
// 		// 	ft_printf("{%d}, {'nl'}\n", curr->type); // remove
// 		// else
// 		// 	ft_printf("{%d}, {%s}\n", curr->type, curr->string); // remove
// 		if (valid_syntax(curr) == FALSE)
// 		{
// 			ft_putendl_fd("Invalid syntax", 2);
// 			exit (1);
// 		}
// 		curr = curr->next;
// 	}
// 	return (TRUE);
// }
