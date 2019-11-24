/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhugo <bhugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 17:39:28 by bhugo             #+#    #+#             */
/*   Updated: 2019/11/20 20:30:14 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

/*
** отрабатываем равнение по левому (flag '-') или
** правому краю (the minimum field-width)
** i минусуем сразу на размер символа
*/

int	format_char(t_printf *p)
{
	int		d;
	int		i;
	char	s;

	d = va_arg(p->arg_ptr, int);
	s = d;
	i = p->width;
	if (p->flag_minus != 1)
	{
		while (--i > 0)
			write_buffer(" ", 0, p);
	}
	write_buffer(&s, 0, p);
	if (p->flag_minus == 1)
	{
		while (--i > 0)
			write_buffer(" ", 0, p);
	}
	return (1);
}
