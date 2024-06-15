/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:37:13 by yalechin          #+#    #+#             */
/*   Updated: 2024/01/20 11:37:14 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// searches for the last occurrence of the character c in s

char	*ft_strrchr(const char *s, int c)
{
	int	x;
	int	p;

	x = 0;
	p = -1;
	while (s[x])
	{
		if (s[x] == (char)c)
		{
			p = x;
		}
		x++;
	}
	if (s[x] == (char)c)
		return ((char *)s + x);
	if (p == -1)
		return (NULL);
	return ((char *)s + p);
}
