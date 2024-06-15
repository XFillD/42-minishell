/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:37:23 by yalechin          #+#    #+#             */
/*   Updated: 2024/01/20 11:37:24 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// s1 - string to be trimmed
// set - characters
// return trimmed string
static int	check_for_char(char c, char const *set)
{
	int	x;

	x = 0;
	while (set[x])
	{
		if (set[x] == c)
			return (1);
		x++;
	}
	return (0);
}

static char	*ft_str(const char *s1, size_t s, size_t len)
{
	size_t	x;
	char	*ptr;

	x = 0;
	ptr = (char *)malloc(len + 1);
	if (!ptr)
		return (NULL);
	while (x < len)
	{
		ptr[x] = s1[s++];
		x++;
	}
	ptr[x] = '\0';
	return (ptr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	count_start;
	int	count_end;

	count_start = 0;
	count_end = ft_strlen(s1) - 1;
	while (s1[count_start] && check_for_char(s1[count_start], set))
		count_start++;
	while ((count_end > count_start) && check_for_char(s1[count_end], set))
		count_end--;
	return (ft_str(s1, count_start, count_end - count_start + 1));
}
