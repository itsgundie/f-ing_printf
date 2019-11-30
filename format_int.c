/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhugo <bhugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 19:02:30 by bhugo             #+#    #+#             */
/*   Updated: 2019/11/20 20:59:51 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

int	free_memory(char **s)
{
	free(*s);
	exit(-1);
}

/*
** проверка знака: избавляемся от него (нужно для отработки флага '0')
*/

int	check_sign(char **s, t_printf *p)
{
	char *tmp;

	if (*s[0] == '-')
	{
		(!(tmp = ft_strdup(*s + 1))) ? free_memory(&(*s)) : 0;
		free(*s);
		*s = tmp;
		p->flag_plus = 0;
		p->flag_space = 0;
		return (-1);
	}
	else if (p->flag_plus == 1)
	{
		p->flag_space = 0;
		return (1);
	}
	return (0);
}

void		ft_put_space(char *s, t_printf *p, int sign)
{
	int		count;

	count = 0;
	if (p->flag_hash == 1)
	{
		p->specifier == 'o' ? p->width-- : 0;
		p->specifier == 'x' || p->specifier == 'X' ?
				p->width -= 2 : 0;
	}
	(p->flag_plus == 1 || sign != 0 || p->flag_space == 1) ? p->width-- : 0;
	if (p->width > (int)ft_strlen(s))
	{
		count = p->width - (int)ft_strlen(s);
		while (--count >= 0)
			write_buffer(" ", 0, p);
	}
}

void		ft_put_space_zero(char *s, t_printf *p, int sign)
{
	int count;
	int	len;

	count = 0;
	len = ((int)ft_strlen(s) > p->precision ? (int)ft_strlen(s) : p->precision);
	if (p->flag_hash == 1)
	{
		p->specifier == 'o' ? p->width-- : 0;
		p->specifier == 'x' || p->specifier == 'X' ? p->width -= 2 : 0;
	}
	(p->flag_plus == 1 || sign != 0 || p->flag_space == 1) ? p->width-- : 0;
	if (p->width > (int)ft_strlen(s))
	{
		count = p->width - (int)ft_strlen(s);
		while (--count >= 0)
			write_buffer("0", 0, p);
	}
}

void	printf_sign(t_printf *p, int sign)
{
	if (sign == 1 || p->flag_space == 1)
	{
		if (p->flag_plus == 1)
			write_buffer("+", 0, p);
		else
			write_buffer(" ", 0, p);
	}
	else if (sign == -1)
		write_buffer("-", 0, p);
}

void	reload_output_with_precision(char **s, t_printf *p)
{
	char	*tmp;
	char	*res;
	int		len;
	int		i;

	len = ft_strlen(*s);
	p->specifier == 'o' && p->flag_hash == 1 && p->precision > 0 ?
		p->precision-- : 0;
	if (p->precision == 0 && *s[0] == '0')
		*s[0] = '\0';
	if (p->precision > len)
	{
		i = p->precision - len;
		(!(tmp = ft_strnew(i))) ? free_memory(&(*s)) : 0;
		while (i-- > 0)
			tmp[i] = '0';
		(!(res = ft_strjoin(tmp, *s))) ? free_memory(&(*s)) : 0;
		free(tmp);
		free(*s);
		*s = res;
	}
}

void	printf_width(char *s, t_printf *p, int sign)
{
	if (p->width >= 0 && p->flag_zero == 0)
		ft_put_space(s, p, sign);
	if (p->width >= 0 && p->flag_zero == 1)
		ft_put_space_zero(s, p, sign);
}

/*
** печать с обработкой флагов
*/

void	print_int(char *s, t_printf *p)
{
	int sign;
	int i;

	i = 0;
	sign = check_sign(&s, p);
	reload_output_with_precision(&s, p);
	if (p->flag_zero == 1)
	{
		printf_sign(p, sign);
		printf_width(s, p, sign);
		while (s[i] != '\0')
			write_buffer(&s[i++], 0, p);
	}
	else if (p->flag_minus == 1)
	{
		printf_sign(p, sign);
		while (s[i] != '\0')
			write_buffer(&s[i++], 0, p);
		printf_width(s, p, sign);
	}
	else
	{
		printf_width(s, p, sign);
		printf_sign(p, sign);
		while (s[i] != '\0')
			write_buffer(&s[i++], 0, p);
	}
	free(s);
}

/*
** отрабатываем длину переменной типа int
** и перекравающие друг друга параметры
*/

int	format_int(t_printf *p)
{
	long long	d;
	char		*s;

	d = va_arg(p->arg_ptr, long long);
	if ((d == LLONG_MIN || d == LONG_MIN) &&
		p->length_l != 1 && p->length_ll != 1)
			(!(s = ft_strdup("0"))) ? exit(-1) : 0;
	else if (p->length_hh == 1)
		(!(s = ft_itoa((char)d))) ? exit(-1) : 0;
	else if (p->length_h == 1)
		(!(s = ft_itoa((short)d))) ? exit(-1) : 0;
	else if (p->length_l == 1 || p->length_ll == 1)
	{
		if (d == LLONG_MIN || d == LONG_MIN)
			(!(s = ft_strdup("-9223372036854775808"))) ? exit(-1) : 0;
		else
			(!(s = ft_long_itoa((long)d))) ? exit(-1) : 0;
	}
	else
		(!(s = ft_itoa((int)d))) ? exit(-1) : 0;
	if (p->flag_minus == 1)
		p->flag_zero = 0;
	if (p->precision > -1)
		p->flag_zero = 0;
	print_int(s, p);
	return (1);
}
