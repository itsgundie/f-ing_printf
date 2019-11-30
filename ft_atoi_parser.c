/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhugo <bhugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 19:10:51 by bhugo             #+#    #+#             */
/*   Updated: 2019/11/18 11:18:22 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

int		ft_atoi_parser(char **str)
{
	int number;

	number = 0;
	if (!(**str >= '0' && **str <= '9'))
		(*str)++;
	while (**str >= '0' && **str <= '9')
		number = number * 10 + *(*str)++ - '0';
	return (number);
}
