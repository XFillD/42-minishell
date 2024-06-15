/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 10:53:11 by yalechin          #+#    #+#             */
/*   Updated: 2024/01/20 10:53:40 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
convert str into int
return the converted value
*/

int	ft_atoi(const char *nptr)
{
	int	x;
	int	n;
	int	sign;

	x = 0;
	n = 0;
	sign = 1;
	while ((nptr[x] == ' ' || (nptr[x] >= 8 && nptr[x] <= 13)) && nptr[x])
		x++;
	if (nptr[x] && (nptr[x] == '-'))
	{
		sign *= -1;
		x++;
	}
	else if (nptr[x] == '+')
		x++;
	while ((nptr[x] >= '0' && nptr[x] <= '9') && nptr[x])
	{
		n = n * 10 + (nptr[x] - '0');
		x++;
	}
	return (n * sign);
}
