/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:13:44 by yalechin          #+#    #+#             */
/*   Updated: 2024/01/20 11:13:46 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
copy n bytes from src to dest
memory area may overlap
return a pointer to dest
*/

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s = src;

	d = dest;
	if (!dest && !src)
		return (NULL);
	if (src < dest)
	{
		while (n--)
		{
			*(d + n) = *(s + n);
		}
		return (dest);
	}
	while (n > 0)
	{
		*d = *s;
		d++;
		s++;
		n--;
	}
	return (dest);
}
