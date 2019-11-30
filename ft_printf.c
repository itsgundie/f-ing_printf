/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhugo <bhugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 19:11:24 by bhugo             #+#    #+#             */
/*   Updated: 2019/11/20 20:53:50 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

/*
** в зависимости от флага идет отработка в соотстветствующей функции
*/

int		check_conversions(t_printf *p)
{
	p->specifier == 'c' ? format_char(p) : 0;
	p->specifier == 'p' ? format_pointer(p) : 0;
	p->specifier == 's' ? format_str(p) : 0;
	p->specifier == 'd' || p->specifier == 'i' ? format_int(p) : 0;
	p->specifier == 'o' ? format_oct(p) : 0;
	p->specifier == 'u' ? format_unsigned_int(p) : 0;
	p->specifier == 'x' ? format_hex(p) : 0;
	p->specifier == 'X' ? format_upper_hex(p) : 0;
	p->specifier == 'f' ? format_float(p) : 0;
	p->specifier == '%' ? format_percent(p) : 0;
	return (1);
}

int		look_for_specifier(char c)
{
	char	*str;

	str = "cpsdiouxXf%";
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

/*
** запись флагов, ширины, точности, длины и спецификатора в структуру
*/

int		look_for_all_parameters(t_printf *p)
{
	while (*p->format && *p->format != '\n')
	{
		(ft_isdigit(*p->format) && *p->format != '0' && (*p->format - 1) != '.')
			? p->width = ft_atoi_parser(&p->format) : 0;
		*p->format == '.' ? p->precision = ft_atoi_parser(&p->format) : 0;
		*p->format == '-' ? p->flag_minus = 1 : 0;
		*p->format == '+' ? p->flag_plus = 1 : 0;
		*p->format == '0' ? p->flag_zero = 1 : 0;
		*p->format == '#' ? p->flag_hash = 1 : 0;
		*p->format == ' ' ? p->flag_space = 1 : 0;
		(*p->format == 'l' && *(p->format + 1) != 'l' &&
			*(p->format - 1) != 'l') ? p->length_l = 1 : 0;
		(*p->format == 'l' && *(p->format + 1) == 'l') ? p->length_ll = 1 : 0;
		*p->format == 'L' ? p->length_capital_l = 1 : 0;
		(*p->format == 'h' && *(p->format + 1) != 'h' &&
			*(p->format - 1) != 'h') ? p->length_h = 1 : 0;
		(*p->format == 'h' && *(p->format + 1) == 'h') ? p->length_hh = 1 : 0;
		(look_for_specifier(*p->format)) ? p->specifier = *p->format : 0;
		if (p->specifier != 0)
			return (check_conversions(p));
		++p->format;
	}
	return (0);
}

/*
** очищение структуры после обработки переменной
** для дальнейшей работы со следующей перерменной,
** иначе флаги сохраняются и функция работает некорректно
*/

void	clean(t_printf *p)
{
	p->flag_minus = 0;
	p->flag_plus = 0;
	p->flag_zero = 0;
	p->flag_hash = 0;
	p->flag_space = 0;
	p->width = 0;
	p->precision = -1;
	p->length_l = 0;
	p->length_ll = 0;
	p->length_capital_l = 0;
	p->length_h = 0;
	p->length_hh = 0;
	p->specifier = 0;
}

/*
** Макрос va_start предназначен для установки аргумента arg_ptr
** на начало списка необязательных параметров.
** указатель arg_prt должен быть объявлен с типом va_list
** Макрос va_end используется по окончании обработки всех параметров функции
** и устанавливает указатель списка необязательных параметров на ноль (NULL).
*/

int		ft_printf(const char *format, ...)
{
	t_printf	p;

	if (format == NULL || (format[0] == '%' && format[1] == '\0'))
		return (0);
	ft_bzero(&p, sizeof(p));
	p.format = (char *)format;
	p.precision = -1;
	va_start(p.arg_ptr, format);
	while (*p.format)
	{
		if (*p.format == '%')
		{
			++p.format;
			look_for_all_parameters(&p);
			clean(&p);
			if (*p.format == '\0')
				break ;
		}
		else
			write_buffer(&(*p.format), 0, &p);
		++p.format;
	}
	write_buffer(NULL, 1, &p);
	va_end(p.arg_ptr);
	return (p.count);
}
