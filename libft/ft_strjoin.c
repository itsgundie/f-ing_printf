/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhugo <bhugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 23:33:26 by bhugo             #+#    #+#             */
/*   Updated: 2019/11/18 13:24:14 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *p;

	if (s1 == NULL || s2 == NULL)
		exit(-1);
	p = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (p == NULL)
		exit(-1);
	ft_strcpy(p, s1);
	ft_strcat(p, s2);
	return (p);
}
