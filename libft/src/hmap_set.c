/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hmap_set.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl...>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/09 21:08:55 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/04/10 17:29:35 by moana         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

static int	store_value(t_hmap *hmap, t_slot **slot, char *key, void *value)
{
	(*slot) = (t_slot*)ft_memalloc(sizeof(t_slot));
	if ((*slot) == NULL)
		return (-1);
	(*slot)->key = ft_strdup(key);
	if ((*slot)->key == NULL)
	{
		ft_memdel((void**)slot);
		return (-1);
	}
	(*slot)->val = value;
	hmap->len += 1;
	return (0);
}

/*
**	params:	pointer to hmap struct, key and value to store.
**	return:	0 if key didn't exist yet, 1 if value for key was replaced.
**			-1 if hmap is full or an error has occured
*/

int			hmap_set(t_hmap *hmap, char *key, void *value)
{
	unsigned long	hash;
	unsigned int	checked;
	int				i;

	hash = hmap_hash(key, hmap->n);
	i = hash % hmap->n;
	checked = 0;
	if (key == NULL)
		return (-1);
	while (hmap->slots[i] != NULL &&
		!ft_strequ(hmap->slots[i]->key, key) && hmap->len < hmap->n)
	{
		i = (((5 * i) + 1) + hash) % hmap->n;
		hash >>= PERTURB_SHIFT;
		if (hash == 0)
			checked++;
	}
	if (hmap->slots[i] == NULL)
		return (store_value(hmap, &(hmap->slots[i]), key, value));
	else if (ft_strequ(hmap->slots[i]->key, key))
	{
		hmap->slots[i]->val = value;
		return (1);
	}
	return (-1);
}
