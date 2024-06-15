/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:03:10 by yalechin          #+#    #+#             */
/*   Updated: 2024/01/20 11:03:10 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
scan n bytes of memory pointed to by s
return a pointer to the first instance of c
if c not found return NULL

*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	int				x;
	unsigned char	*str;
	unsigned char	ch;

	x = 0;
	str = (unsigned char *)s;
	ch = (unsigned char)c;
	while (n > 0)
	{
		if (str[x] == ch)
			return ((char *)str + x);
		x++;
		n--;
	}
	return (NULL);
}
