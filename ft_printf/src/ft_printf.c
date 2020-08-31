/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/03 16:49:24 by bprado        #+#    #+#                 */
/*   Updated: 2019/12/14 17:37:26 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		clean_struct(t_pf_sect *s)
{
	s->fl = 0;
	s->spc = 0;
	s->len = 0;
	s->v.ull = 0;
	s->width = 0;
	s->prcs = 0;
	++s->i;
}

int				ft_vdprintf(int fd, const char *format, va_list ap)
{
	t_pf_sect		s;
	t_func_pointer	arrpointer[128];

	ft_bzero(&s, sizeof(s));
	s.fd = fd;
	s.str = format;
	va_copy(s.ap, ap);
	populate_func_array(arrpointer);
	while (s.str[s.i] != 0)
	{
		if (s.str[s.i] == '%' && s.str[s.i + 1] == 0)
			break ;
		if (s.str[s.i] == '%')
		{
			++s.i;
			parse_format_string(&s);
			arrpointer[(int)s.spc](&s);
			clean_struct(&s);
		}
		if (s.str[s.i] != 0 && s.str[s.i] != '%')
			print_character(s.str[s.i], &s);
		s.i += s.str[s.i] && s.str[s.i] != '%' ? 1 : 0;
	}
	va_end(s.ap);
	return (s.ret);
}

int				ft_printf(const char *format, ...)
{
	int				i;
	va_list			ap;

	va_start(ap, format);
	i = ft_vdprintf(1, format, ap);
	va_end(ap);
	return (i);
}

int				ft_dprintf(int fd, const char *format, ...)
{
	int				i;
	va_list			ap;

	va_start(ap, format);
	i = ft_vdprintf(fd, format, ap);
	va_end(ap);
	return (i);
}

void			print_n(t_pf_sect *s)
{
	int				*n;

	n = va_arg(s->ap, void*);
	*n = s->ret;
}
