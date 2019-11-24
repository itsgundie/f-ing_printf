/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhugo <bhugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 19:11:35 by bhugo             #+#    #+#             */
/*   Updated: 2019/11/20 20:43:05 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINT_H
# define FT_PRINT_H
# include <stdarg.h>
# include "libft/libft.h"
# include <limits.h>
# define BUFF 1024

typedef struct	s_printf
{
	va_list		arg_ptr;
	char		*format;
	int			count;
	char		flag_minus;
	char		flag_plus;
	char		flag_zero;
	char		flag_hash;
	char		flag_space;
	int			width;
	int			precision;
	char		length_l;
	char		length_ll;
	char		length_capital_l;
	char		length_h;
	char		length_hh;
	char		specifier;
}				t_printf;

int				ft_printf(const char *format, ...);
char			*ft_itoa_base(unsigned int n, int base);
char			*ft_itoa_base_capital(unsigned int n, int base);
int				ft_atoi_parser(char **str);
char			*ft_strndup(int n, char *s1);
char			*ft_long_itoa(long n);
int				format_percent(t_printf *p);
int				format_upper_hex(t_printf *p);
int				format_hex(t_printf *p);
int				format_unsigned_int(t_printf *p);
int				format_oct(t_printf *p);
int				format_int(t_printf *p);
int				format_pointer(t_printf *p);
int				format_char(t_printf *p);
int				format_str(t_printf *p);
int				check_sign(char **s, t_printf *p);
void			reload_output_with_precision(char **s, t_printf *p);
void			printf_width(char *s, t_printf *p, int sign);
void			ft_put_space(char *s, t_printf *p, int sign);
void			ft_put_space_zero(char *s, t_printf *p, int sign);
char			*ft_itoa_base_long(unsigned long long int n, int base);
void			print_oct(char *s, t_printf *p);
char			*ft_itoa_base_capital_long(unsigned long long int n, int base);
int				format_float(t_printf *p);
void			print_int(char *s, t_printf *p);
int				write_buffer(char *s, int end, t_printf *p);
void			ft_putchar_buffer(char c, t_printf *p);
void			ft_putstr_buffer(char const *s, t_printf *p);

#endif
