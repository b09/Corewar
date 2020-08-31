/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extra_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/13 20:00:01 by bprado        #+#    #+#                 */
/*   Updated: 2019/12/14 17:55:39 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			print_string(t_pf_sect *s)
{
	char	*str;
	int		i;

	i = 0;
	str = "(null)";
	if (s->spc == 's' && s->v.ptr == 0)
	{
		while (*str)
		{
			print_character(*str, s);
			++str;
		}
		return ;
	}
	str = s->v.ptr;
	while (*str)
	{
		if (s->fl & PRECISN && !s->prcs && s->spc == 's')
			return ;
		print_character(*str, s);
		str++;
		s->prcs -= s->spc == 's' && s->fl & PRECISN ? 1 : 0;
	}
}

char			get_base(char format_spc)
{
	char			base;

	base = 0;
	base = format_spc == 'd' ? 10 : base;
	base = format_spc == 'b' ? 2 : base;
	base = format_spc == 'i' ? 10 : base;
	base = format_spc == 'f' ? 10 : base;
	base = format_spc == 'x' ? 16 : base;
	base = format_spc == 'X' ? 16 : base;
	base = format_spc == 'o' ? 8 : base;
	base = format_spc == 'u' ? 10 : base;
	base = format_spc == 'p' ? 16 : base;
	return (base);
}

void			putnbr_signed_exception(t_pf_sect *s)
{
	char			*stupidasslongnumber;

	stupidasslongnumber = "9223372036854775808";
	if (s->v.llong == -9223372036854775807 - 1)
	{
		s->v.ptr = stupidasslongnumber;
		print_string(s);
		return ;
	}
}

void			print_character(char c, t_pf_sect *s)
{
	ft_putchar_fd(c, s->fd);
	s->ret++;
}
