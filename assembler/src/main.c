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

/*
**	Checks if file is valid, reads into t_info.
**	Stores file_name and file_content.
**	file_name is needed to name final assembly output, ie <file_name>.cor
**
**	params: argc, argv, struct with general info for assembler
**	return: TRUE or FALSE, depending on validity
*/

static int	read_file(int argc, char **argv, t_info *info)
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
	info->file_name = ft_memdup(str, name_len - 1);
	info->file_name[name_len - 1] = '\0';
	fd = open(str, O_RDONLY);
	while (get_next_line(fd, *str) > 0)
		ft_lstappend(info->file_content, *str);
	return (TRUE);
}

/*
**	Finds quotation marks in a larger string and returns substring.
**
**	Params: str that contains "<to_return>"
**	Return: isolated string <to_return>
*/

static char *get_name_comment(char *str)
{
	char	*start;
	char	*end;

	start = ft_strchr(str, '"') + 1;
	end = ft_strchr(start, '"');
	name = ft_memdup(start, end - start);
	name[end - start - 1] = '\n';
	return (name);
}

/*
** Validates a string by checking each char against list of legal chars
**
** Params: str to check
** Return: TRUE or FALSE
*/

static int	only_label_chars(char *str)
{
	while (str)
	{
		i = 0;
		while (i < N_LABEL_CHARS)
		{
			if (*str == LABEL_CHARS[i])
				break ;
			i++;
		}
		if (i > N_LABEL_CHARS)
			return (FALSE);
	}
	return (TRUE);
}

/*
**	If the lexicon is valid this function stores info->name and info->comment
**
**	Params: info struct
**	Return: TRUE or FALSE depending on validity
*/

static int	lexicon_valid(t_info *info)
{
	char	*curr;

	curr = info->file_content;
	while (curr)
	{
		// Skip comment
		if (curr->content[0] == COMMENT_CHAR)
			;
		// Check that only .name and .comment start with '.'
		// Store name and content in info.
		// TODO:
		// .name and .comment allowed anywhere but top?
		// check macros in op.h for relevant constants
		// check if name and comment are set at the end
		// check if they were set already. Is that allowed?
		else if (curr->content[0] == '.')
		{
			if (ft_memcmp(curr->content, NAME_CMD_STRING, 5) == 0)
				info->name = get_name_comment(curr->content);
			else if (ft_memcmp(curr->content, COMMENT_CMD_STRING, 8") == 0)
				info->comment = get_name_comment(curr->content);
			else
				return (FALSE);
		}
		// Check that LABELS and INSTRUCTIONS only contain LABEL_CHARS
		else if (is_label(curr->content) || is_instruction(curr->content))
			if (only_label_chars(curr->content) == FALSE)
				return (FALSE);
		curr = curr->next;
	}
}

int			main(int argc, char **argv)
{
	// char *str = "Assembler main";
	// ft_printf("%s\n", str);
	read_file(argc, argv, info);
	if (read_file(argc, argv, info) == FALSE)
		return (1);
	lexicon_valid(info);
	syntax_valid();
	instructions_valid();
	params_valid();
	parse_assembly();
	return (0);
}
