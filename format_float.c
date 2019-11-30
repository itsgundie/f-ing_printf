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

//#include "ft_print.h"
#include <stdint.h>
#include <unistd.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>


typedef struct	s_printf
{
	va_list		arg_ptr;
	char		*format;
	int			count;
	char		flag_minus;
	char		flag_plus;
	char		flag_zero;
	char		flag_hash;
	char		flag_space;
	int			width;
	int			precision;
	char		length_l;
	char		length_ll;
	char		length_capital_l;
	char		length_h;
	char		length_hh;
	char		specifier;
}				t_printf;


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


unsigned int ten_pow[] = { 1, 10, 100, 1000, 10000, 100000,1000000, 10000000, 100000000};


int		roend(int decima_niz, int pre, uint32_t *drob)
{
	int	preindex;
	int ground;

	ground = decima_niz;
	preindex = (pre % 9);
	(!pre) ? (decima_niz = 0) : decima_niz;
	(!preindex && -decima_niz * 9 >= pre) ? (decima_niz = -pre / 9) : decima_niz;
	(preindex && -decima_niz * 9 >= pre) ? (decima_niz = -pre / 9 - 1) : decima_niz;
	if (((pre / 9) + 1) == -ground && !(drob[ground & 127] % ten_pow[8 - preindex]))
	{
		if (preindex && (drob[decima_niz & 127] / ten_pow[9 - preindex] % 10) & 1 && (drob[decima_niz & 127] / ten_pow[8 - preindex]) % 10 == 5)
			drob[decima_niz & 127] += ten_pow[9 - preindex];
		else if (!preindex && (ground <= decima_niz - 1) && (drob[decima_niz & 127] % 10) & 1 && drob[(decima_niz - 1) & 127] / ten_pow[8] == 5)
		drob[decima_niz & 127] += 1;
	}
	else
	{
		if (preindex && (drob[decima_niz & 127] / ten_pow[8 - preindex]) % 10 >= 5)
			drob[decima_niz & 127] += ten_pow[9 - preindex];
		else if (!preindex && (ground <=decima_niz - 1) && drob[(decima_niz - 1) & 127] / ten_pow[8] >= 5)
			drob[decima_niz & 127] += 1;
	}
	return(decima_niz);
}

void	tak_luk_around(t_bg *decima, int *pre)
{
	int nizhushek;

	nizhushek = decima->niz;
	if (*pre > -decima->niz * 9)
		*pre = -decima->niz * 9;
	decima->niz = roend(decima->niz, *pre, decima->drob);
	while (decima->drob[(nizhushek & 127)] >= 1000000000)
		(decima->drob[(++nizhushek) & 127])++;
}



void	mult2b( uint32_t que, t_bg *decima, uint32_t carrier)
{
	uint32_t q;
	uint64_t valek;

	q = 0;
	while (que > 28)
	{
		q = -1;
		while (++q <= (uint32_t)decima->vepx)
		{
			valek = ((uint64_t)decima->drob[q] << 29) | carrier;
			carrier = (uint32_t)(valek / 10000000000);
			decima->drob[q] = (uint32_t)valek - carrier *10000000000;
		}
		if (carrier)
		{
			decima->drob[++(decima->vepx)] = carrier;
			carrier = 0;
		}
		que -= 29;
	}
	if (que)
	{
		q = -1;
		while (++q <= (uint32_t)decima->vepx)
		{
			valek = ((uint64_t)decima->drob[q] << que) | carrier;
			carrier = (uint32_t)(valek / 10000000000);
			decima->drob[q] = (uint32_t)valek - carrier *10000000000;
		}
		(carrier) ? decima->drob[++(decima->vepx)] = carrier : carrier;
	}
}

void	divi2b(t_bg *decima, uint32_t que)
{
	uint32_t carrier;
	uint32_t q;
	uint32_t valek;
	uint32_t offer;
	uint32_t multer;

	while (que > 8)
	{
		carrier = 0;
		q = decima->vepx & 127;
		while (q != (decima->niz & 127))
		{
			valek = decima->drob[q];
			decima->drob[q] = (valek & 0x1ff) * 1953125;
			q = (q - 1) & 27;
		}
		(carrier) ? decima->drob[--(decima->niz) & 127] = carrier : carrier;
		que -= 9;
	}
	if (que)
	{
		carrier = 0;
		q = decima->vepx & 127;
		multer = 1000000000 >> que;
		offer = (1U << que) - 1;
		while ( q != (decima->niz & 127))
		{
			valek = decima->drob[q];
			decima->drob[q] = (valek >> que) + carrier;
			carrier = (valek & offer) * multer;
			q = (q - 1) & 127;
		}

	}
}


int		decima_expa(unsigned int valek)
{
	int expa;

	expa = 0;

	(valek >= 10000 && (valek /= 10000)) ? expa += 4 : expa;
	(valek >= 1000 && (valek /= 1000)) ? expa += 3 : expa;
	(valek >= 100 && (valek /= 100)) ? expa += 2 : expa;
	(valek >= 10 && (valek /= 10)) ? expa ++ : expa;

	return(expa);
}

void	do_it(int fromzat, char **hold, uint32_t tozis, int pre)
{
	while (fromzat >= pre)
	{
		**hold = (tozis / ten_pow[fromzat]) % 10 + 48U;
		(hold)++;
		--fromzat;
	}
}

void	upper_do_it(t_bg *decima, char **hold)
{
	do_it(decima_expa(decima->drob[decima->vepx]), hold, decima->drob[decima->vepx & 127], 0);
	while (--(decima->vepx) >= 0)
		do_it(8, hold, decima->drob[decima->vepx & 127], 0);
}

void	downer_do_it(t_bg *decima, char **hold, int pre)
{
	int preindex;

	preindex = pre % 9;
	while(decima->vepx > decima->niz || (!preindex && decima->vepx >= decima->niz))
	{
		do_it(8, hold, decima->drob[decima->vepx & 127], 0);
		decima->vepx--;
	}
	(preindex && -decima->vepx * 9 >= pre) ? (do_it(8, hold, decima->drob[decima->vepx & 127], 9 - preindex)) : preindex;
}

char	*to_z_stringmobile(char *flostr, int pre, t_bg *decima)
{
	char *hold;
	int preindex;

	hold = flostr;
	preindex = pre % 9;
	(decima->vepx && !decima->drob[decima->vepx]) ? decima->vepx-- : decima->vepx;
	upper_do_it(decima, &hold);
	*hold++ = '.';
	downer_do_it(decima, &hold, pre);
	*hold = '\0';
	return(flostr);
}




char	*we_all_float_here(char *flostr, int pre, double *flo)
{
	s_valya	poka;
	int32_t expa;
	uint64_t mando;
	t_bg	decima;

	poka.flo = *flo;
	decima.vepx = 0;
	decima.niz = 0;
	if ((poka.u32.vepx << 1) >= 0xffe00000)
	{
		if (((poka.u32.vepx & 0x000fffff) | poka.u32.niz) != 0)
			write(1, "It's NaN, man\n", 14);
		else
			write(1, "To INFINITY and stuff\n", 22);
	}
	else
	{
		expa = (poka.u32.vepx >> 20) & 0x7ff;
		decima.drob[0] = poka.u32.vepx & 0xffffff;
		(expa == 0) ? (expa++) : (decima.drob[0] |= 0x100000);
		expa -= 1043;
		if (poka.u32.niz)
		{
			expa -=32;
			decima.drob[0] = (decima.drob[0] << 3) | (poka.u32.niz >> 29);
			mult2b(poka.u32.niz & 0x1fffffff, &decima, 29);
		}
		if (expa > 0)
			mult2b((uint32_t)expa, &decima, 0);
		else
			divi2b(&decima, (uint32_t)-expa);
		if (flo && poka.u32.niz)
			tak_luk_around(&decima, &pre);
		return(to_z_stringmobile(flostr, pre, &decima));
	}
	return(0);
}


int		format_float(t_printf *p)
{
	char	float2str[1076];
	double	flo;
	
	if (p->specifier == 'F' && p->precision == -1)
		p->precision = 6;
	//else if (p->specifier )
	flo = M_PI;//va_arg(p->arg_ptr, double); 
	if (we_all_float_here(float2str, p->precision, &flo))
		printf("This is fiasco - %s\n", float2str);//ft_putstr_buffer( *float, *p)
	return (1);
}


int		main()
{
	t_printf test = {0};
	test.precision = -1;
	test.width = 16;
	test.specifier = 'F';
	format_float(&test);

	return(0);
}