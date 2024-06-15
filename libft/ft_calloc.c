/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 10:55:01 by yalechin          #+#    #+#             */
/*   Updated: 2024/01/20 10:55:03 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// allocated memory and initializes every byte to 0
// nmemb - number of blocks
// size - size of each block in bytes
// returns a pointer to the block of memory
// SIZE MAX = size_t - 1

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			x;
	size_t			s;

	s = nmemb * size;
	if ((nmemb && size) && nmemb > ((size_t)-1) / size)
		return (NULL);
	x = 0;
	ptr = (unsigned char *)malloc(s);
	if (!ptr)
		return (NULL);
	while (x < (s))
	{
		ptr[x++] = 0;
	}
	return (ptr);
}
