/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hmap_get.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl...>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/09 21:18:24 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/04/10 17:10:51 by moana         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

/*
**	params:	pointer to hmap, key of requested value.
**	return:	Value stored for input key.
*/

void	*hmap_get(t_hmap *hmap, char *key)
{
	unsigned long	hash;
	unsigned int	checked;
	int				i;

	hash = hmap_hash(key, hmap->n);
	i = hash % hmap->n;
	checked = 0;
	while (hmap->slots[i] != NULL && !ft_strequ(hmap->slots[i]->key, key)
		&& checked <= hmap->n)
	{
		i = (((5 * i) + 1) + hash) % hmap->n;
		hash >>= PERTURB_SHIFT;
		if (hash == 0)
			checked++;
	}
	if (!(hmap->slots[i]) || !ft_strequ(hmap->slots[i]->key, key))
		return (NULL);
	return (hmap->slots[i]->val);
}
