/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/13 18:59:41 by bprado         #+#    #+#                */
/*   Updated: 2019/12/06 23:58:27 by bprado        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <math.h>

int		main(void)
{
	float f = 156489753252.0368168;
	f = 0;

	f = ft_pow(2.0, 8.0);
	// passing 1203 A test
	// printf(" <--%d \n", ft_printf("%.0f", 1.6));
	// printf(" <--%d \n", printf("%.0f", 1.6));

	// printf(" <--%d ft_printf\n", ft_printf("%f", -3.85));
	// printf(" <--%d printf\n", printf("%f", -3.85));
	// printf("\n");

	// printf(" <--%d ft_printf\n", ft_printf("%f", 5665.9999999));
	// printf(" <--%d printf\n", printf("%f", 5665.9999999));
	// printf("\n");

	printf(" <--%d ft_printf\n", ft_printf("%0*.*d", -5, -7, 42));
	printf(" <--%d printf\n", printf("%0*.*d", -5, -7, 42));
	printf("\n");
	// int64_t ulng = -1;
	// printf(" <--%d end \n", printf("%llu", ulng));
	// printf(" <--%d end \n", printf("pow %Lf", ft_pow(2.0, 3.0)));

	// printf(" <--%d end \n", ft_printf("%#.x %#.0x", 0, 0));
	// printf(" <--%d end \n", printf("%#.x %#.0x", 0, 0));
	// printf(" <--%d end \n", ft_printf("%#.p %.p", 0, 0));
	// printf(" <--%d end \n", printf("%#.p %.p", 0, 0));
	// printf("\n");

	// printf(" <--%d end \n", ft_printf("%15X", 0));
	// printf(" <--%d end \n", printf("%15X", 0));
	// printf("\n");

	// char *yo = "yo";
	// printf(" <--%d end \n", ft_printf("%#18.15p", yo));
	// printf(" <--%d end \n", printf("%#18.15p", yo));
	// printf("\n");

	// printf(" <--%d end \n", ft_printf("%18p", yo));
	// printf(" <--%d end \n", printf("%18p", yo));
	// printf("\n");

	// printf(" <--%d end \n", ft_printf("%p", yo));
	// printf(" <--%d end \n", printf("%p", yo));
	// printf("\n");

	// printf(" <--%d end \n", ft_printf("%.15p", yo));
	// printf(" <--%d end \n", printf("%.15p", yo));
	// printf("\n");

	// printf(" <--%d end \n", ft_printf("%#u", 34));
	// printf(" <--%d end \n", printf("%#u", 34));
	// printf("\n");

	// printf(" <--%d end \n", ft_printf("%0+5d", 42));
	// printf(" <--%d end \n", printf("%0+5d", 42));
	// printf("\n");


	// printf(" <--%d end \n", ft_printf("%05d", -42));
	// printf(" <--%d end \n", printf("%05d", -42));
	// printf("\n");


	// printf(" <--%d end \n", ft_printf("%0+5d", -42));
	// printf(" <--%d end \n", printf("%0+5d", -42));
	// printf("\n");


	// printf(" <--%d end \n", ft_printf("%6.5i", -84735555));
	// printf(" <--%d end \n", printf("%6.5i", -84735555));
	// printf("\n");

	// printf(" <--%d end \n", ft_printf("%08.6i", -8473));
	// printf(" <--%d end \n", printf("%08.6i", -8473));
	// printf("\n");

	// printf(" <--%d end \n", ft_printf("%10.5i", -216));
	// printf(" <--%d end \n", printf("%10.5i", -216));
	// printf("\n");

	// printf(" <--%d end \n", ft_printf("%03.2d", -1));
	// printf(" <--%d end \n", printf("%03.2d", -1));
	// printf("\n");

  	// printf(" <--%d end \n", ft_printf("%5d", -42));
  	// printf(" <--%d end \n", printf("%5d", -42));
	// printf("\n");

  	// printf(" <--%d end \n", ft_printf("%-5d", -42));
  	// printf(" <--%d end \n", printf("%-5d", -42));
	// printf("\n");

  	// printf(" <--%d end \n", ft_printf("%-05d", -42));
  	// printf(" <--%d end \n", printf("%-05d", -42));
	// printf("\n");

  	// printf(" <--%d end \n", ft_printf("%03.2d", 0));
  	// printf(" <--%d end \n", printf("%03.2d", 0));
	// printf("\n");

  	// printf(" <--%d end \n", ft_printf("%+03.2d", 1));
  	// printf(" <--%d end \n", printf("%+03.2d", 1));
	// printf("\n");

	// printf(" <--%d end \n", ft_printf("%+5i", 35));
	// printf(" <--%d end \n", printf("%+5i", 35));
	// printf("\n");

	// printf(" <--%d d\n", ft_printf("%5d", -42));
	// printf(" <--%d d\n", printf("%5d", -42));
	// printf("\n");

	// printf(" <--%d d\n", ft_printf("%-5d", -42));
	// printf(" <--%d d\n", printf("%-5d", -42));
	// printf("\n");
	
	// printf(" <--%d d\n", ft_printf("%-05d", -42));
	// printf(" <--%d d\n", printf("%-05d", -42));
	// printf("\n");



	// printf(" <--%d d\n", ft_printf("%+10.5d", 42));
	// printf(" <--%d d\n", printf("%+10.5d", 42));
	// printf("\n");

	// printf(" <--%d d\n", ft_printf("%lld", -9223372036854775808));
	// printf(" <--%d d\n", printf("%lld", -9223372036854775808));
	// printf("\n");

	// printf(" <--%d d\n", ft_printf("%+10.5d", 4242));
	// printf(" <--%d d\n", printf("%+10.5d", 4242));
	// printf("\n");

	// printf(" <--%d d\n", ft_printf("%0+5d", 42));
	// printf(" <--%d d\n", printf("%0+5d", 42));
	// printf("\n");

	// printf(" <--%d d\n", ft_printf("%+5d", 0));
	// printf(" <--%d d\n", printf("%+5d", 0));
	// printf("\n");
	
	// printf(" <--%d d\n", ft_printf("%-+10.5d", 4242));
	// printf(" <--%d d\n", printf("%-+10.5d", 4242));
	// printf("\n");
	
	// printf(" <--%d d\n", ft_printf("%lu", -42));
	// printf(" <--%d d\n", printf("%lu", -42));
	// printf("\n");

	// printf(" <--%d c\n", ft_printf("% c", 0));
	// printf(" <--%d c\n", printf("% c", 0));
	// printf("\n");

	// printf(" <--%d s\n", ft_printf("%.12s", NULL));
	// printf(" <--%d s\n", printf("%.12s", NULL));
	// printf("\n");

	// printf(" <--%d d\n", ft_printf("%+5.4d", 42));
	// printf(" <--%d d\n", printf("%+5.4d", 42));
	// printf("\n");

	// printf(" <--%d d\n", ft_printf("% d", -42));
	// printf(" <--%d d\n", printf("% d", -42));
	// printf("\n");

	// printf(" <--%d d\n", ft_printf("%0+5d", -42));
	// printf(" <--%d d\n", printf("%0+5d", -42));
	// printf("\n");

	// printf(" <--%d d\n", ft_printf("% 10.15d", 4242));
	// printf(" <--%d d\n", printf("% 10.15d", 4242));
	// printf("\n");

	// printf(" <--%d d\n", ft_printf("% 10.5d", 4242));
	// printf(" <--%d d\n", printf("% 10.5d", 4242));
	// printf("\n");

	// printf(" <--%d d\n", ft_printf("%+10.15d", -42));
	// printf(" <--%d d\n", printf("%+10.15d", -42));
	// printf("\n");

	// printf(" <--%d d\n", ft_printf("%+10.5d", -42));
	// printf(" <--%d d\n", printf("%+10.5d", -42));
	// printf("\n");

	// printf(" <--%d d\n", ft_printf("%03.2d", 0));
	// printf(" <--%d d\n", printf("%03.2d", 0));
	// printf("\n");

	// printf(" <--%d d\n", ft_printf("%03.2d", 1));
	// printf(" <--%d d\n", printf("%03.2d", 1));
	// printf("\n");

	// printf(" <--%d d\n", ft_printf("%3.2d", 1));
	// printf(" <--%d d\n", printf("%3.2d", 1));
	// printf("\n");

	// printf(" <--%d d\n", ft_printf("@moulitest: %.10d", -42));
	// printf(" <--%d d\n", printf("@moulitest: %.10d", -42));
	// printf("\n");

	// printf(" <--%d x\n", ft_printf("%#08x", 42));
	// printf(" <--%d x\n", printf("%#08x", 42));
	// printf("\n");
	// printf(" <--%d o\n", ft_printf("%#.0o", 0));
	// printf(" <--%d o\n", printf("%#.0o", 0));
	// printf("\n");
	// printf(" <--%d p\n", ft_printf("%025p", 42));
	// printf(" <--%d p\n", printf("%025p", 42));
	// printf("\n");
	// printf(" <--%d X\n", ft_printf("%-5.20X", 42));
	// printf(" <--%d X\n", printf("%-5.20X", 42));
	// printf("\n");
	// printf(" <--%d\n", printf("%#05x", 42));


	return (0);
}
