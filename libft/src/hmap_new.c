/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hmap_new.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl...>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/09 20:03:13 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/07/28 14:31:29 by mmarcell      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include <stdlib.h>

static unsigned int	find_pow2(int n)
{
	int m;

	m = 1;
	while (m < n)
		m <<= 1;
	return (m);
}

/*
**	params:	number of expected keys, pointer to deletion function for values.
**	return:	Pointer to newly allocated hmap struct.
*/

t_hmap				*hmap_new(int n)
{
	t_hmap	*hmap;

	if (n <= 0)
		return (NULL);
	hmap = (t_hmap*)ft_memalloc(sizeof(t_hmap));
	if (!hmap)
		return (NULL);
	hmap->n = find_pow2((n * 3) / 2);
	hmap->slots = (t_slot**)ft_memalloc(sizeof(t_slot*) * (hmap->n));
	if (!(hmap->slots))
	{
		free(hmap);
		return (NULL);
	}
	hmap->len = 0;
	return (hmap);
}
