/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:31:30 by yalechin          #+#    #+#             */
/*   Updated: 2024/01/20 11:31:31 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// appends src to dest
// NULL terminated
// returns the combined length of both src and dest not counting NULL

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	x;
	size_t	s;
	size_t	len_dst;
	size_t	len_src;
	size_t	len;

	x = 0;
	s = ft_strlen(dst);
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	len = len_dst + len_src;
	if (size <= len_dst)
		return (len_src + size);
	while (src[x] && (len_dst + x) < (size - 1))
	{
		dst[s] = src[x];
		x++;
		s++;
	}
	dst[s] = '\0';
	return (len);
}
