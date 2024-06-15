/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:38:13 by yalechin          #+#    #+#             */
/*   Updated: 2024/01/20 11:38:14 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// s - string from which substring is created
// start - index of the substring in s
// len - max length of substring
// return substring or NULL if alloc. fails

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	x;
	char	*ptr;

	x = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	ptr = (char *)malloc(len + 1);
	if (!ptr)
		return (NULL);
	while (x < len)
	{
		ptr[x] = s[start + x];
		x++;
	}
	ptr[x] = '\0';
	return (ptr);
}
