#include "minishell.h"

// allocate memory for token str
int	ft_alloc(char *line, int x)
{
	int		count;
	bool	in_quote;
	char	c;

	count = 0;
	c = '?';
	in_quote = false;
	while ((line[x] != ' ' && line[x]) || (line[x] == ' ' && in_quote == 1
			&& line[x]))
	{
		if (line[x] == DOUBLE_QUOTE && c != SINGLE_QUOTE)
		{
			if (c == DOUBLE_QUOTE)
				c = '?';
			else
				c = DOUBLE_QUOTE;
			in_quote = !in_quote;
		}
		if (line[x] == SINGLE_QUOTE && c != DOUBLE_QUOTE)
		{
			if (c == SINGLE_QUOTE)
				c = '?';
			else
				c = SINGLE_QUOTE;
			in_quote = !in_quote;
		}
		x++;
		count++;
	}
	printf("COUNT is %d\n", count);
	return (count);
}