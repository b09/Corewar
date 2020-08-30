/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hmap_hash.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl...>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/09 21:35:44 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/04/10 17:44:53 by moana         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
**	djb2, hash function for strings
**	source: http://www.cse.yorku.ca/~oz/hash.html @ March 9th, 2020
**
**	parms: key to hash
**	return: hash
*/

unsigned long	hmap_hash(char *key)
{
	unsigned long	hash;
	int				i;

	hash = 5381;
	i = 0;
	while (key[i] != '\0')
	{
		hash = ((hash << 5) + hash) + key[i];
		i++;
	}
	return (hash);
}
