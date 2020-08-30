/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hmap_clear.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl...>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/09 20:18:54 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/04/10 17:30:04 by moana         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include <stdlib.h>

/*
**	params:	addr of hmap pointer
**	return:
*/

void	hmap_clear(t_hmap **hmap)
{
	unsigned int	i;
	t_hmap			*mp;

	i = 0;
	mp = *hmap;
	while (i < mp->n)
	{
		ft_strdel(&(mp->slots[i]->key));
		free(mp->slots[i]);
		mp->slots[i] = NULL;
		i++;
	}
	mp->slots = NULL;
	mp->n = 0;
	free(*hmap);
	hmap = NULL;
}
