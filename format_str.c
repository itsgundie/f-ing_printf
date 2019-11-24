/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhugo <bhugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 19:07:14 by bhugo             #+#    #+#             */
/*   Updated: 2019/11/20 20:34:47 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

/*
** отрабатываем равнение по левому (flag '-')
**и правому краю (the minimum field-width), точность (precision)
** для отработки точности модифицирована функция strdup -> strndup
** отработка отсутствия аргумента ("(null)")
*/

void	print_str(char *s, t_printf *p)
{
	int		d;

	d = p->width - ft_strlen(s);
	if (p->flag_minus != 1)
	{
		while (d-- > 0)
			ft_putchar_buffer(' ', p);
	}
	ft_putstr_buffer(s, p);
	if (p->flag_minus == 1)
	{
		while (d-- > 0)
			ft_putchar_buffer(' ', p);
	}
}

int		format_str(t_printf *p)
{
	char	*s;

	s = va_arg(p->arg_ptr, char *);
	if (p->precision > -1 && s)
		(!(s = ft_strndup(p->precision, s))) ? exit(-1) : 0;
	else if (p->precision == -1 && s)
		(!(s = ft_strndup(ft_strlen(s), s))) ? exit(-1) : 0;
	else if (p->precision > -1 && !s)
		(!(s = ft_strndup(p->precision, "(null)"))) ? exit(-1) : 0;
	else if (p->precision == -1 && !s)
		(!(s = ft_strdup("(null)"))) ? exit(-1) : 0;
	print_str(s, p);
	free(s);
	return (1);
}
