/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhugo <bhugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 19:11:01 by bhugo             #+#    #+#             */
/*   Updated: 2019/11/20 19:27:41 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

/*
** i have changed type of n for itoa(base) long
*/

static int	ft_order(unsigned long long int n, int base)
{
	int		order;

	order = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / base;
		order++;
	}
	return (order);
}

char		*ft_itoa_base_long(unsigned long long int n, int base)
{
	char	*p;
	char	*tab_base;
	int		count;

	if ((tab_base = ft_strdup("0123456789abcdef")) == NULL)
		return (NULL);
	count = ft_order(n, base);
	if ((p = ft_strnew(count)) == NULL)
		return (NULL);
	if (n == 0)
		p[0] = '0';
	while (n)
	{
		p[--count] = tab_base[n % base];
		n = n / base;
	}
	free(tab_base);
	return (p);
}

char		*ft_itoa_base(unsigned int n, int base)
{
	char	*p;
	char	*tab_base;
	int		count;

	if ((tab_base = ft_strdup("0123456789abcdef")) == NULL)
		return (NULL);
	count = ft_order(n, base);
	if ((p = ft_strnew(count)) == NULL)
		return (NULL);
	if (n == 0)
		p[0] = '0';
	while (n)
	{
		p[--count] = tab_base[n % base];
		n = n / base;
	}
	free(tab_base);
	return (p);
}

char		*ft_itoa_base_capital_long(unsigned long long int n, int base)
{
	char	*p;
	char	*tab_base;
	int		count;

	if ((tab_base = ft_strdup("0123456789ABCDEF")) == NULL)
		return (NULL);
	count = ft_order(n, base);
	if ((p = ft_strnew(count)) == NULL)
		return (NULL);
	if (n == 0)
		p[0] = '0';
	while (n)
	{
		p[--count] = tab_base[n % base];
		n = n / base;
	}
	free(tab_base);
	return (p);
}

char		*ft_itoa_base_capital(unsigned int n, int base)
{
	char	*p;
	char	*tab_base;
	int		count;

	if ((tab_base = ft_strdup("0123456789ABCDEF")) == NULL)
		return (NULL);
	count = ft_order(n, base);
	if ((p = ft_strnew(count)) == NULL)
		return (NULL);
	if (n == 0)
		p[0] = '0';
	while (n)
	{
		p[--count] = tab_base[n % base];
		n = n / base;
	}
	free(tab_base);
	return (p);
}
