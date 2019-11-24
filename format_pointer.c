/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhugo <bhugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 19:06:05 by bhugo             #+#    #+#             */
/*   Updated: 2019/11/20 20:31:38 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

/*
** узакатель, 16ричная система исчисления
** отрабатываем равнение по левому (flag '-')
** и правому краю (the minimum field-width), точность (precision)
*/

char	*ft_itoa_base_ptr(unsigned long n, int base)
{
	char			*s;
	unsigned long	nb;
	int				len;

	len = 1;
	nb = n;
	while (nb >= (unsigned)base)
	{
		nb /= base;
		++len;
	}
	if ((s = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		exit(-1);
	s[len] = '\0';
	while (n >= (unsigned)base)
	{
		s[--len] = n % base < 10 ? (n % base) + 48 : (n % base) + 87;
		n /= base;
	}
	s[--len] = n % base < 10 ? (n % base) + 48 : (n % base) + 87;
	return (s);
}

int		format_pointer(t_printf *p)
{
	unsigned long	ptr;
	char			*s;
	int				d;

	ptr = va_arg(p->arg_ptr, unsigned long);
	s = ft_itoa_base_ptr(ptr, 16);
	d = p->width - ft_strlen(s) - 2;
	reload_output_with_precision(&s, p);
	if (p->flag_minus != 1)
	{
		while (d-- > 0)
			write_buffer(" ", 0, p);
	}
	ft_putstr_buffer("0x", p);
	ft_putstr_buffer(s, p);
	if (p->flag_minus == 1)
	{
		while (d-- > 0)
			write_buffer(" ", 0, p);
	}
	free(s);
	return (1);
}
