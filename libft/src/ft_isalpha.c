/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/11 14:51:36 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/11 15:00:37 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (ft_isupper(c) == TRUE || ft_islower(c) == TRUE)
		return (TRUE);
	return (FALSE);
}
