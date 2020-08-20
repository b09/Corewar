/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlladd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl...>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/26 15:09:48 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/06/26 15:09:49 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlladd(t_dll **alst, t_dll *new)
{
	(*alst)->previous = new;
	new->next = *alst;
	*alst = new;
}
