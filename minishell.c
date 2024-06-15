/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:31:55 by yalechin          #+#    #+#             */
/*   Updated: 2024/06/15 12:11:11 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_token
{
	char			*token_str;
	int				token_type;

	struct s_token	*prev;
	struct s_token	*next;

}					t_token;

typedef struct s_program
{
	char			*input;
	char			*split_line;
	t_token			*first;

}					t_program;

int	ft_is_in_str(const char *str, int ch)
{
	int	x;

	x = 0;
	if (!str)
		return (1);
	while (str[x])
	{
		if (str[x] == ch)
			return (0);
		x += 1;
	}
	return (1);
}

// check for valid quote matching
int	ft_check_quotes(t_program *program)
{
	int		x;
	bool	q1;
	bool	q2;

	x = 0;
	q1 = false;
	q2 = false;
	while (program->input[x])
	{
		if (program->input[x] == SINGLE_QUOTE)
			q1 = !q1;
		if (program->input[x] == DOUBLE_QUOTE)
			q2 = !q2;
		x++;
	}
	if (!q1 && !q2)
	{
		printf("ALL GOOD - QUOTES MATCH\n");
		return (0);
	}
	printf("NOT GOOD - QUOTES DO NOT MATCH\n");
	return (1);
}

bool	ft_check_for_special(int c)
{
	if (c == RED_IN)
		return (true);
	if (c == RED_OUT)
		return (true);
	if (c == D_SIGN)
		return (true);
	if (c == PIPE)
		return (true);
	return (false);
}

bool	ft_check_for_double(int c1, int c2)
{
	if (c1 == RED_IN && c2 == RED_IN)
		return (true);
	if (c1 == RED_OUT && c2 == RED_OUT)
		return (true);
	return (false);
}

// allocate memory, create new line and add spaces for better tokenization
// consider special chars

// handle $ somehow????
char	*ft_prepare_line(t_program *program)
{
	char	*new_line;
	int		x;
	int		y;
	int		count;
	bool	quote;

	x = 0;
	y = 0;
	count = 0;
	quote = false;
	while (program->input[x] == ' ')
		x++;
	while (program->input[x])
	{
		if (program->input[x] == SINGLE_QUOTE
			|| program->input[x] == DOUBLE_QUOTE)
			quote = !quote;
		if (ft_check_for_special(program->input[x]) == true && !quote)
			count++;
		x++;
	}
	new_line = malloc(sizeof(char) * (x + 2 * count + 1));
	x = 0;
	while (program->input[x] == ' ')
		x++;
	while (program->input[x])
	{
		if (program->input[x] == SINGLE_QUOTE
			|| program->input[x] == DOUBLE_QUOTE)
			quote = !quote;
		if (ft_check_for_special(program->input[x]) == true && !quote)
		{
			if (ft_check_for_double(program->input[x], program->input[x
					+ 1]) == true)
			{
				new_line[y++] = ' ';
				new_line[y++] = program->input[x++];
				new_line[y++] = program->input[x++];
				new_line[y++] = ' ';
			}
			else
			{
				new_line[y++] = ' ';
				new_line[y++] = program->input[x++];
			}
		}
		else
			new_line[y++] = program->input[x++];
	}
	new_line[y] = '\0';
	// clean input?
	return (new_line);
}

int	ft_alloc(char *line, int x)
{
	int	count;

	count = 0;
	while (line[x] != ' ' && line[x])
	{
		x++;
		count++;
	}
	printf("COUNT is %d\n", count);
	return (count);
}

t_token	*new_token(char *new_line, int *x)
{
	t_token	*new_token;
	int		y;

	y = 0;
	// printf("CHECK Len is %d\n", len);
	// printf("CHECK X is %d\n", x);
	// printf("CHECK P is %d\n", p);
	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		exit(1);
	new_token->token_str = (char *)malloc(sizeof(ft_alloc(new_line, *x) + 1));
	if (!new_token->token_str)
		exit(1);
	while (new_line[*x] && new_line[*x] != ' ')
	{
		new_token->token_str[y++] = new_line[(*x)++];
	}
	new_token->token_str[y] = '\0';
	return (new_token);
}

t_token	*ft_tokenization(t_program *program)
{
	t_token	*prev;
	t_token	*head;
	t_token	*next;
	int		x;
	int		len;
	bool	in_quote;

	in_quote = false;
	prev = NULL;
	head = NULL;
	next = NULL;
	x = 0;
	len = 0;
	while (program->split_line[x])
	{
		len = 0;
		while (program->split_line[x] == ' ' && program->split_line[x])
			x++;
		next = new_token(program->split_line, &x);
		next->prev = prev;
		if (prev)
			prev->next = next;
		else
			head = next;
		prev = next;
	}
	if (prev)
		prev->next = NULL;
	return (head);
}

// organize tokens into logical groups based on possible commands
// consider adding types to tokens here a before
// before exec check the lists of tokens again

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	t_program *program;

	program = malloc(sizeof(t_program));

	while (1)
	{
		program->input = readline("minishell> ");
		if (!program->input)
		{
			break ;
		}
		add_history(program->input);
		ft_check_quotes(program);
		program->split_line = ft_prepare_line(program);
		printf("Final line: %s\n", program->split_line);
		program->first = ft_tokenization(program);

		while (program->first != NULL)
		{
			printf("TOKEN is: %s\n", program->first->token_str);
			program->first = program->first->next;
		}

		// ft_execute(program);
		// ft_debug(program);
		// free_program(program);
	}
	return (0);
}