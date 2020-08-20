/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hashtable.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl...>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 21:33:05 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/04/10 17:09:24 by moana         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H

# define HASHTABLE_H

# include "libft.h"

# define PERTURB_SHIFT 5

typedef struct	s_slot
{
	char			*key;
	void			*val;
}				t_slot;

typedef struct	s_hmap
{
	t_slot			**slots;
	unsigned int	len;
	unsigned int	n;
}				t_hmap;

t_hmap			*hmap_new(int n);
void			hmap_clear(t_hmap **hmap);

int				hmap_set(t_hmap *hmap, char *key, void *value);
void			*hmap_get(t_hmap *hmap, char *key);
void			hmap_del_slot(t_hmap *hmap, char *key);
void			hmap_del_map(t_hmap **hmap);

unsigned long	hmap_hash(char *key, int n);

#endif
