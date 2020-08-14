/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/14 19:54:14 by bprado        #+#    #+#                 */
/*   Updated: 2019/02/14 21:00:37 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		join_and_read(char **str, char **h, char buf[], int fd)
{
	*str = *h;
	*h = ft_strjoin(*str, buf);
	(str) ? ft_strdel(&*str) : str;
	buf[read(fd, buf, BUFF_SIZE)] = '\0';
}

static int		join_and_return(char **line, char **str, char **h, char buf[])
{
	*line = (!*str) ? ft_strjoin(*h, buf) : NULL;
	(!*str) ? ft_strdel(&*h) : h;
	if (!*str)
		return (1);
	**str = '\0';
	*line = ft_strjoin(*h, buf);
	(*h) ? ft_strdel(&*h) : h;
	*h = (ft_strlen(*str + 1)) ? ft_strdup(*str + 1) : NULL;
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static char		*h[1024];
	char			buf[BUFF_SIZE + 1];
	char			*str;

	if (read(fd, buf, 0) < 0 || fd < 0 || !line || fd > 1024)
		return (-1);
	ft_bzero(buf, BUFF_SIZE + 1);
	h[fd] ? ft_memcpy(buf, h[fd], BUFF_SIZE) : (void*)read(fd, buf, BUFF_SIZE);
	ft_strdel(&h[fd]);
	h[fd] = ft_strnew(0);
	while (*buf > 0 && !(ft_strchr(buf, '\n')))
		join_and_read(&str, &h[fd], buf, fd);
	str = ft_strchr(buf, '\n');
	if (str || ((ft_strlen(buf) < BUFF_SIZE) && (h[fd][0] != '\0')))
		return (join_and_return(line, &str, &h[fd], buf));
	*line = h[fd];
	(h[fd]) ? ft_strdel(&h[fd]) : h;
	if (!h[fd] && *buf == '\0')
		*line = NULL;
	return (0);
}
