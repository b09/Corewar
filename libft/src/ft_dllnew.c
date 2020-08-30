/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dllnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl...>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/26 15:07:13 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/06/26 15:07:13 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dll	*ft_dllnew(void const *content, size_t content_size)
{
	t_dll	*link;
	char	*cont_copy;

	if (content == NULL)
		content_size = 0;
	link = (t_dll *)malloc(sizeof(t_dll));
	if (link == NULL)
		return (NULL);
	if (content_size > 0)
		cont_copy = ft_memdup((char *)content, content_size);
	else
		cont_copy = NULL;
	link->content = cont_copy;
	link->content_size = content_size;
	link->next = NULL;
	link->previous = NULL;
	return (link);
}
