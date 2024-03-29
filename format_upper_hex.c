/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_upper_hex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 19:10:12 by bhugo             #+#    #+#             */
/*   Updated: 2019/11/18 12:10:01 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

int	format_upper_hex(t_printf *p)
{
	char					*s;
	unsigned long long int	u;

	u = va_arg(p->arg_ptr, unsigned long long int);
	p->length_h == 1 ? s = ft_itoa_base_capital((unsigned short)u, 16) : 0;
	p->length_hh == 1 ? s = ft_itoa_base_capital((unsigned char)u, 16) : 0;
	p->length_l == 1 ?
		s = ft_itoa_base_capital_long((unsigned long int)u, 16) : 0;
	p->length_ll == 1 ?
		s = ft_itoa_base_capital_long((unsigned long long int)u, 16) : 0;
	p->length_h + p->length_hh + p->length_l + p->length_ll == 0 ?
		s = ft_itoa_base_capital(u, 16) : 0;
	if (p->flag_minus == 1 || p->precision > -1)
		p->flag_zero = 0;
	if (s[0] == '0' && s[1] == '\0')
		p->flag_hash = 0;
	print_oct(s, p);
	return (1);
}
