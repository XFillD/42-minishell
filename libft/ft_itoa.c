/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:02:59 by yalechin          #+#    #+#             */
/*   Updated: 2024/01/20 11:03:00 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int to str - return str
// handle negative numbers
static int	ft_intlen(int n)
{
	int	x;

	x = 0;
	if (n <= 0)
	{
		n *= -1;
		x++;
	}
	while (n > 0)
	{
		n = n / 10;
		x++;
	}
	return (x);
}

char	*ft_itoa(int n)
{
	int		x;
	int		nbr;
	char	*arr;
	int		len;

	len = ft_intlen(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	x = 0;
	nbr = n;
	if (n < 0)
		nbr *= -1;
	arr = (char *)malloc(len + 1);
	if (!arr)
		return (NULL);
	arr[len] = '\0';
	while (len > 0)
	{
		arr[len - 1] = (nbr % 10) + '0';
		nbr = nbr / 10;
		len--;
	}
	if (n < 0)
		arr[x] = '-';
	return (arr);
}
