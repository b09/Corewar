/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/03 16:49:27 by bprado         #+#    #+#                */
/*   Updated: 2019/12/07 01:11:37 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF

# define FT_PRINTF

# include <stdio.h> //for testing printf
# include <stdarg.h>
# include "libft.h"

# define HASH_F 		1 << 0
# define ZERO_F 		1 << 1
# define MINUS_F 		1 << 2
# define SPACE_F 		1 << 3
# define PLUS_F 		1 << 4
# define H_F 			1 << 5
# define L_F 			1 << 6
# define HH_F 			1 << 7
# define LL_F 			1 << 8
# define SIGNED_F		1 << 9
# define CAP_L_F		1 << 10
# define PRECISN		1 << 11
# define WIDTH			1 << 12
# define STRNG			1 << 13
# define PRTSIGN		1 << 14
# define NZERO			0x8000
# define INF			0x7FFF
# define NINF			0xFFFF
typedef union	u_union_output
{
	u_int64_t			ll;
	long long			llong;
	long double			lngdbl;
	short				shdbl[5];
	void*				ptr;
		
}				union_output;

typedef struct	s_pf_object
{
	const char*			str;
	short				flags;
	char				buffer[32];
	char				spc;
	int					i;
	union_output		val;
	int					i_str;
	int					width;
	int					prcs;
	int					length;
	va_list				ap;
	int					ret;
	int					fd;
}				t_pf_object;

typedef void (*func_pointer)(t_pf_object *);

int				ft_printf(const char * restrict format, ...);
void			parse_flags(t_pf_object *obj);
void			parse_width_precision(t_pf_object *obj);
void			parse_length(t_pf_object *obj);
void			parse_specifier(func_pointer arrpointer[128]);
void			parse_general(t_pf_object *obj);
char			get_base(char format_specifier);
int				length_of_number(t_pf_object *obj);
void			ft_putnbr_signed(long long n, int base, t_pf_object *obj);
void			print_sign(t_pf_object *obj);
void			print_hash_flag(t_pf_object *obj);
void			print_padding(t_pf_object *obj, int length_of_output, char character, char flip);
void			print_character(char c, t_pf_object *obj);
void			print_string(t_pf_object *obj);
void			print_d(t_pf_object *obj);
void			print_o(t_pf_object *obj);
void			print_str(t_pf_object *obj);
void			print_f(t_pf_object *obj);

int				length_of_float(t_pf_object *obj);
void			putfloat(t_pf_object *obj, int i, int str_i);
int				float_exception(t_pf_object *obj);
void			print_sign_float(t_pf_object *obj);
int				length_of_unsigned(t_pf_object *obj);
void			ft_putnbr_unsigned(u_int64_t n, int base, t_pf_object *obj);
void			clean_struct(t_pf_object *obj);
long double		ft_pow(float a, float b);
void			no_minus_flag(t_pf_object *obj);
void			print_dioupxxc(t_pf_object *obj);
int				ft_dprintf(int fd, const char* restrict format, ...);

#endif