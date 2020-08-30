/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/06 16:20:05 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/02/06 16:20:06 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Prepares the fd_thread to be read to/from
**	Returns the correct node in list, or creates it.
*/

static t_list	*select_fd_list(int fd, t_list *fd_list, char *buff)
{
	t_list	*current;
	char	*new_content;

	current = fd_list;
	while (current->next != NULL)
	{
		if (current->FILE_DESC == (unsigned long)fd)
			break ;
		current = current->next;
	}
	if (current->FILE_DESC != (unsigned long)fd)
	{
		ft_lstappend(&current, ft_lstnew(buff, ft_strlen(buff) + 1));
		current = current->next;
		current->FILE_DESC = fd;
	}
	else
	{
		new_content = ft_strjoin(current->content, buff);
		ft_memdel(&(current->content));
		current->content = new_content;
	}
	return (current);
}

/*
**	Reads from buff.
**	If fd not used yet, creates new node.
**	If fd already used, adds buff to it.
**
**	Returns adress to line it read.
**	Returns NULL if no '\n' included in before.
*/

static char		*read_from_fd(int fd, t_list *fd_list)
{
	t_list	*fd_current;
	int		n_bytes;
	char	*new_content;
	char	buff[BUFF_SIZE + 1];

	ft_bzero(buff, BUFF_SIZE + 1);
	n_bytes = read(fd, buff, BUFF_SIZE);
	if (n_bytes == -1)
		return (NULL);
	else if (n_bytes > 0 && n_bytes < BUFF_SIZE && buff[n_bytes - 1] != '\n')
		buff[n_bytes] = '\n';
	fd_current = select_fd_list(fd, fd_list, buff);
	if (fd_current == NULL)
		return (NULL);
	if (n_bytes == 0 && ((char *)fd_current->content)[0] != '\0' &&
		ft_strchr(fd_current->content, '\n') == NULL)
	{
		new_content = ft_strjoin(fd_current->content, "\n");
		ft_memdel(&(fd_current->content));
		fd_current->content = new_content;
	}
	return (fd_current->content);
}

/*
**	Removes a line from fd_list after it was completed.
**	Stores a remainder, if any, in fd_list.
**	If nothing remains, new_line_len will be 0 and content_adress will be NULL.
**	This will trigger the current node to be unlinked and freed.
*/

static void		remove_line_from_list(\
	int fd, t_list **alst, char *nl_adress, char **line)
{
	t_list	*current;
	size_t	old_len;
	size_t	new_len;
	char	*content_adress;

	current = *alst;
	while (current->FILE_DESC != (unsigned long)fd)
		current = current->next;
	if (!nl_adress)
		*line = NULL;
	else
	{
		old_len = ft_strlen(current->content);
		new_len = 1 + old_len - (nl_adress - (char *)current->content);
		content_adress = (char *)ft_memalloc(new_len);
		ft_memcpy(content_adress, nl_adress + 1, new_len);
		ft_memdel(&(current->content));
		current->content = content_adress;
	}
	if (!nl_adress || content_adress[0] == '\0')
	{
		current = ft_lstunlink(alst, current);
		ft_memdel(&(current->content));
		ft_memdel((void**)&current);
	}
}

/*
**	Error handeling.
**	Initializes the fd_list if it's empty.
**	Returns the first chunk after reading BUFF_SIZE chars.
*/

static char		*first_call(t_list **alst, int fd, char **read_line)
{
	char	buff[0];
	int		status;

	status = read(fd, buff, 0);
	if (status < 0)
	{
		*read_line = NULL;
		return (NULL);
	}
	if (*alst == NULL)
	{
		*alst = ft_lstnew("", 1);
		(*alst)->FILE_DESC = fd;
	}
	*read_line = read_from_fd(fd, *alst);
	return (ft_strchr(*read_line, '\n'));
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*alst;
	char			*read_line;
	char			*new_line_adress;

	new_line_adress = first_call(&alst, fd, &read_line);
	if (read_line == NULL || !line)
		return (-1);
	if (*read_line == '\0')
	{
		remove_line_from_list(fd, &alst, new_line_adress, line);
		return (0);
	}
	while (new_line_adress == NULL)
	{
		read_line = read_from_fd(fd, alst);
		if (read_line == NULL)
			return (-1);
		new_line_adress = ft_strchr(read_line, '\n');
	}
	*line = ft_memdup(read_line, new_line_adress - read_line + 1);
	if (*line == NULL)
		return (-1);
	(*line)[new_line_adress - read_line] = '\0';
	remove_line_from_list(fd, &alst, new_line_adress, line);
	return (1);
}
