/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/08/21 12:41:01 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	Checks if file is valid, populates t_asm.
**	Stores file_name and file_content.
**	file_name is needed to name final assembly output, ie <file_name>.cor
**
**	Params: 	argc, argv, struct with general info for assembler
**	Return: 	TRUE or FALSE, depending on validity
**	called by:	main()
*/

static int	read_file(int argc, char **argv, t_asm *info)
{
	char 	*str;
	int		name_len;
	int		fd;

	if (argc != 2)
		return (FALSE);
	str = argv[1];
	name_len = ft_strlen(str);
	if (name_len <= 2 || str[name_len - 2] != '.' || str[name_len - 1] != 's')
		return (FALSE);
	info->file_name = ft_strndup(str, name_len);
	fd = open(str, O_RDONLY);
	while (gnl_with_newline(fd, &str) > 0)
		tokenize(str, info);
	return (TRUE);
}

/*
**	Finds quotation marks in a larger string and returns substring.
**
**	Params:		str that contains "... <to_return> ..."
**	Return:		isolated string "<to_return>""
**	called by:
*/

// static char *get_name_comment(char *str)
// {
// 	char	*start;
// 	char	*end;
// 	char	*name;

// 	start = ft_strchr(str, '"') + 1;
// 	end = ft_strchr(start, '"');
// 	name = ft_memdup(start, end - start);
// 	name[end - start - 1] = '\n';
// 	return (name);
// }

/*
**	Validates a string by checking each char against list of legal chars
**
**	Params:		str to check
**	Return:		TRUE or FALSE
**	called by:
*/

static int	only_label_chars(char *str)
{
	while (str)
	{
		if (ft_strchr(LABEL_CHARS, *str) == NULL)
			return (FALSE);
		++str;
	}
	return (TRUE);
}

/* bprado
	simplified func() through use of ft_strchr
	original below:
*/

// static int	only_label_chars(char *str)
// {
// 	int		i;
//
// 	i = 0;
// 	while (str)
// 	{
// 		i = 0;
// 		while (i < N_LABEL_CHARS)
// 		{
// 			if (*str == LABEL_CHARS[i])
// 				break ;
// 			i++;
// 		}
// 		if (i > N_LABEL_CHARS)
// 			return (FALSE);
// 	}
// 	return (TRUE);
// }

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

static int	lexicon_valid(t_asm *info)
{
	t_token	*curr;

	curr = info->token_head;
	while (curr)
	{
		ft_printf("{%d}, {%s}\n", curr->type, curr->string);
		curr = curr->next;
	}
	return (TRUE);
}

int			main(int argc, char **argv)
{
	t_asm	asm_obj;

	ft_bzero(&asm_obj, sizeof(asm_obj));
	// read_file(argc, argv, &asm_obj);
	if (read_file(argc, argv, &asm_obj) == FALSE)
		return (1);
	lexicon_valid(&asm_obj);
	// syntax_valid();
	// instructions_valid();
	// params_valid();
	// parse_assembly();
	return (0);
}

// static int	lexicon_valid(t_asm *info);

static int	only_label_chars(char *str);

static char *get_name_comment(char *str);

static int	read_file(int argc, char **argv, t_asm *info);
