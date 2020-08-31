/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/03 16:49:27 by bprado        #+#    #+#                 */
/*   Updated: 2020/06/26 16:00:36 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

/*
**	# define HASH 			1 << 0
**	# define ZERO_F 		1 << 1
**	# define MINUS_F 		1 << 2
**	# define SPACE 			1 << 3
**	# define PLUS 			1 << 4
**	# define H_F 			1 << 5
**	# define L_F 			1 << 6
**	# define HH_F 			1 << 7
**	# define LL_F 			1 << 8
**	# define SIGNED_F		1 << 9
**	# define CAP_L_F		1 << 10
**	# define PRECISN		1 << 11
**	# define WIDTH			1 << 12
**	# define STRNG			1 << 13
**	# define PRTSIGN		1 << 14
**	# define FLOATEXCP		1 << 15
**	# define NZERO			0x8000
**	# define INF			0x7FFF
**	# define NINF			0xFFFF
*/

# define HASH 			1
# define ZERO_F 		2
# define MINUS_F 		4
# define SPACE 			8
# define PLUS 			16
# define H_F 			32
# define L_F 			64
# define HH_F 			128
# define LL_F 			256
# define SIGNED_F		512
# define CAP_L_F		1024
# define PRECISN		2048
# define WIDTH			4096
# define STRNG			8192
# define PRTSIGN		16384
# define FLOATEXCP		32768
# define NZERO			0x8000
# define INF			0x7FFF
# define NINF			0xFFFF

typedef union			u_union_output
{
	u_int64_t			ull;
	long long			llong;
	long double			lngd;
	u_int16_t			sh[5];
	void				*ptr;
}						t_union_output;

typedef struct			s_pf_sect
{
	const char			*str;
	short				fl;
	char				spc;
	int					len;
	t_union_output		v;
	int					i;
	int					width;
	int					prcs;
	int					length;
	va_list				ap;
	int					ret;
	char				*temp;
	char				*temp2;
	int					fd;
}						t_pf_sect;

typedef void			(*t_func_pointer)(t_pf_sect *);

int						ft_vdprintf(int fd, const char *format, va_list ap);
int						ft_printf(const char *format, ...);
int						ft_dprintf(int fd, const char *format, ...);
void					print_character(char c, t_pf_sect *s);
void					print_n(t_pf_sect *s);
int						length_of_float(t_pf_sect *s);
void					putfloat(t_pf_sect *s, int i, int str_i);
char					get_base(char format_specifier);
int						length_of_number(t_pf_sect *s);
int						length_of_unsigned(t_pf_sect *s);
void					ft_putnbr_signed(long long n, int base, t_pf_sect *s);
void					ft_putnbr_unsigned(u_int64_t n, int base, t_pf_sect *s);
void					populate_func_array(t_func_pointer arrpointer[128]);
void					parse_format_string(t_pf_sect *s);
void					print_sign(t_pf_sect *s);
void					sign_float(t_pf_sect *s);
void					print_hash_flag(t_pf_sect *s);
void					print_padding(t_pf_sect *s, int length_of_output,
										char character, char flip);
void					print_string(t_pf_sect *s);
void					print_dioupxxc(t_pf_sect *s);
void					print_str(t_pf_sect *s);
void					print_f(t_pf_sect *s);
void					putnbr_signed_exception(t_pf_sect *s);
void					parse_length(t_pf_sect *s);

#endif
