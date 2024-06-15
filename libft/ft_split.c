/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:26:50 by yalechin          #+#    #+#             */
/*   Updated: 2024/01/20 11:26:59 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// s - string to be split
// c - delimiter
// return the array of new strings resulting from the split
// NULL if it fails

static int	count_word(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] == 9 || s[i] == 32 || s[i] == '\n')
		i++;
	while (s[i] && i < (int)ft_strlen(s))
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		if (s[i] == c)
			i++;
	}
	return (count);
}

static char	*ft_word(const char *s, int st, int en)
{
	char	*word;
	int		x;

	x = 0;
	word = malloc((en - st + 1) * sizeof(char));
	while (st < en)
		word[x++] = s[st++];
	word[x] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**strings;
	int		i;
	int		x;
	int		len;

	strings = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!strings)
		return (NULL);
	i = 0;
	x = 0;
	len = -1;
	while (i <= (int)ft_strlen(s))
	{
		if (s[i] != c && len < 0)
			len = i;
		else if ((s[i] == c || i == (int)ft_strlen(s)) && len >= 0)
		{
			strings[x++] = ft_word(s, len, i);
			len = -1;
		}
		i++;
	}
	strings[x] = NULL;
	return (strings);
}
