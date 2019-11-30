/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_oct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhugo <bhugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 19:04:56 by bhugo             #+#    #+#             */
/*   Updated: 2019/11/20 20:36:32 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

void	printf_hash(char *s, t_printf *p)
{
	if (p->specifier == 'o' && p->flag_hash == 1 && s[0] == '0' && s[1] == '\0')
		p->flag_hash = 0;
	if (p->specifier == 'x' && p->flag_hash == 1 && s[0] == '0' && s[1] == '\0')
		p->flag_hash = 0;
	if (p->specifier == 'X' && p->flag_hash == 1 && s[0] == '0' && s[1] == '\0')
		p->flag_hash = 0;
	if (p->flag_hash == 1 && s != '\0')
	{
		p->specifier == 'o' ? write_buffer("0", 0, p) : 0;
		p->specifier == 'x' ? ft_putstr_buffer("0x", p) : 0;
		p->specifier == 'X' ? ft_putstr_buffer("0X", p) : 0;
	}
}

void	print_oct(char *s, t_printf *p)
{
	int sign;
	int i;

	i = 0;
	sign = check_sign(&s, p);
	reload_output_with_precision(&s, p);
	if (p->flag_zero == 1)
	{
		printf_hash(s, p);
		printf_width(s, p, sign);
		while (s[i] != '\0')
			write_buffer(&s[i++], 0, p);
	}
	else if (p->flag_minus == 1)
	{
		printf_hash(s, p);
		while (s[i] != '\0')
			write_buffer(&s[i++], 0, p);
		printf_width(s, p, sign);
	}
	else
	{
		printf_width(s, p, sign);
		printf_hash(s, p);
		while (s[i] != '\0')
			write_buffer(&s[i++], 0, p);
	}
	free(s);
}

int		format_oct(t_printf *p)
{
	char					*s;
	unsigned long long int	u;

	u = va_arg(p->arg_ptr, unsigned long long int);
	p->length_h == 1 ? s = ft_itoa_base((unsigned short)u, 8) : 0;
	p->length_hh == 1 ? s = ft_itoa_base((unsigned char)u, 8) : 0;
	p->length_l == 1 ? s = ft_itoa_base_long((unsigned long int)u, 8) : 0;
	p->length_ll == 1 ? s = ft_itoa_base_long((unsigned long long int)u, 8) : 0;
	p->length_h + p->length_hh + p->length_l + p->length_ll == 0 ?
		s = ft_itoa_base(u, 8) : 0;
	if (p->flag_minus == 1 || p->precision > -1)
		p->flag_zero = 0;
	print_oct(s, p);
	return (1);
}
