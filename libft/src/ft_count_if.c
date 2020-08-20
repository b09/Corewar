/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_count_if.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 20:18:46 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/09 20:21:26 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_count_if(char **tab, int (*f)(char*))
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (tab[i] != 0)
	{
		if (f(&tab[i][0]) == 1)
			count++;
		i++;
	}
	return (count);
}
