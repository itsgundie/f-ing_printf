/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_percent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhugo <bhugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 18:58:15 by bhugo             #+#    #+#             */
/*   Updated: 2019/11/20 20:32:03 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

/*
** отрабатываем равнение по левому (flag '-')
** и правому краю (the minimum field-width)
** i минусуем сразу на размер символа
*/

int	format_percent(t_printf *p)
{
	int i;

	i = p->width;
	if (p->flag_minus != 1)
	{
		while (--i > 0)
			write_buffer(" ", 0, p);
	}
	write_buffer("%", 0, p);
	if (p->flag_minus == 1)
	{
		while (--i > 0)
			write_buffer(" ", 0, p);
	}
	return (1);
}
