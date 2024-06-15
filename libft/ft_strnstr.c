/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:35:46 by yalechin          #+#    #+#             */
/*   Updated: 2024/01/20 11:35:51 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// if s2-little is is empty s1-big is returned
// if little is not found - NULL is returned
// only len characters are searched
// if l is found - return pointer to the first character of l in b

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	x;
	size_t	y;
	size_t	l;

	x = 0;
	y = 0;
	if (s2[0] == '\0')
		return ((char *)s1);
	l = ft_strlen(s2);
	while (s1[x] && x < len)
	{
		y = 0;
		while (s1[x + y] && s2[y] && s1[x + y] == s2[y] && x + y < len)
			y++;
		if (y == l)
			return ((char *)s1 + x);
		x++;
	}
	return (NULL);
}
