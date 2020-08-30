/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_islower.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/11 15:00:58 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/19 17:37:59 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_islower(int c)
{
	if (c >= 'a' && c <= 'z')
		return (TRUE);
	return (FALSE);
}
