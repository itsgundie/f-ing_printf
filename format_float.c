/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cspare <cspare@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:21:19 by bhugo             #+#    #+#             */
/*   Updated: 2019/11/24 17:19:12 by cspare           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

typedef	union		u_valya
{
	double			flo;
	struct
	{
		uint32_t	vepx;
		uint32_t	niz;
	}				u32;
}					s_valya;



typedef struct		s_bignum
{
	uint32_t		drob[128];
	int32_t			niz;
	int32_t			vepx;
}					t_bg;

void	we_all_float_here(char *flostr, int pre, double flo)
{
	s_valya	poka;
	poka.flo = flo;
	int32_t expa;
	uint64_t mando;

	if ((pola.u32.vepx << 1) >= 0xffe00000)
	{
		if (((poka.u32.vepx & 0x000fffff) | poka.u32.niz) != 0)
			write(1, "It's NaN, man\n", 14);
		else
			write(1, "To INFINITY and stuff\n", 22);
	}
	else
	{
		expa = (poka.u32.vepx >> 20) & 0x7ff;
		mando = poka.u32.vepx & 0xffffff;
		if (expa == 0)
			expa++;
		else
			mando |= 0x100000;
		expa -= 1043;
		if (poka.u32.niz)
		{
			expa -=32;
			mando = (mando << 32) | poka.u32.niz;
		}
	}
	t_bg	decima;
	
}




int		format_float(t_printf *p)
{
	char	float2str[1076];
	double	flo;
	
	p->specifier = 'F';
	if (p->precision == -1)
		p->precision = 6;
	flo = va_arg(p->arg_ptr, double);
	we_all_float_here(float2str, p->precision, flo);
	
	
	

	
	
	ft_putstr_buffer( *float, *p)
	return (1);
}
