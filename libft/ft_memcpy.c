/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:07:52 by yalechin          #+#    #+#             */
/*   Updated: 2024/01/20 11:07:54 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
copy n bytes of src to dst
memory area does not overlap
return a pointer to dest
*/

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*d;

	if (!dest && !src)
		return (0);
	d = dest;
	while (n > 0)
	{
		*(char *)d = *(char *)src;
		d++;
		src++;
		n--;
	}
	return (dest);
}
