/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexical_analysis_helpers.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/19 13:56:19 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/09/18 13:02:26 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	A command can only be ".name" or ".comment"
**
**	Called by:	valid_token()
*/

int			valid_cmd_tkn(char *str)
{
	if (!ft_strequ(str, NAME_CMD_STRING) &&
		!ft_strequ(str, COMMENT_CMD_STRING))
		return (FALSE);
	return (TRUE);
}

/*
**	Direct arguments must begin '%' followed by only number characters
**
**	Called by:	valid_token()
*/

int			valid_dir_tkn(char *str)
{
	int		i;
	long	int_max;
	long	int_min;

	int_min = -2147483648;
	int_max = 2147483647;
	i = 0;
	if (*str != DIRECT_CHAR)
		return (FALSE);
	str++;
	if (str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (FALSE);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		return (FALSE);
	if (i > 10)
		return (FALSE);
	if (ft_atol(str) > int_max || ft_atol(str) > int_min)
		return (FALSE);
	return (TRUE);
}

/*
**	A register must be 'r1' or 'r2'... thru to 'r99', 'r0' and 'r00' are invalid
**
**	Called by:	valid_token()
*/

int			valid_reg_tkn(char *str)
{
	if (*str != REGISTRY_CHAR)
		return (FALSE);
	str++;
	if (*str == 0 || ft_strlen(str) > 2)
		return (FALSE);
	if (ft_atoi(str) == 0 || ft_atoi(str) > 99)
		return (FALSE);
	if (!ft_isdigit(str[0]))
		return (FALSE);
	if (ft_strlen(str) == 2 && !ft_isdigit(str[1]))
		return (FALSE);
	return (TRUE);
}

/*
**	Indirect labels begin with ':', followed by LABEL_CHARS
**
**	Called by:	valid_token()
*/

int			valid_ilbl_tkn(char *str)
{
	if (*str != LABEL_CHAR)
		return (FALSE);
	str++;
	while (*str)
	{
		if (!ft_strchr(LABEL_CHARS, *str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

/*
**	An indirect token will only be a positive or negative number
**
**	Called by:	valid_token()
*/

int			valid_ind_tkn(char *str)
{
	int		i;
	long	int_max;
	long	int_min;

	int_min = -2147483648;
	int_max = 2147483647;
	i = 0;
	if (str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (FALSE);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		return (FALSE);
	if (i > 10)
		return (FALSE);
	if (ft_atol(str) > int_max || ft_atol(str) > int_min)
		return (FALSE);
	return (TRUE);
}
