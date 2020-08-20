/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 16:31:43 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/23 17:01:17 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*link;
	char	*cont_copy;

	if (content == NULL)
		content_size = 0;
	link = (t_list *)malloc(sizeof(t_list));
	if (link == NULL)
		return (NULL);
	if (content_size > 0)
		cont_copy = ft_memdup((char *)content, content_size);
	else
		cont_copy = NULL;
	link->content = cont_copy;
	link->content_size = content_size;
	link->next = NULL;
	return (link);
}
