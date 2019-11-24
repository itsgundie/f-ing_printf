/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhugo <bhugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 21:31:40 by bhugo             #+#    #+#             */
/*   Updated: 2019/11/20 20:54:04 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

int	write_buffer(char *s, int end, t_printf *p)
{
	static char	to_write[BUFF];
	static int	idx;

	if (end)
	{
		p->count += write(1, to_write, idx);
		idx = 0;
		return (1);
	}
	to_write[idx++] = *s;
	if (idx >= BUFF)
	{
		p->count += write(1, to_write, idx);
		idx = 0;
		return (1);
	}
	return (0);
}
