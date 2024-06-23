/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:31:55 by yalechin          #+#    #+#             */
/*   Updated: 2024/06/22 13:53:52 by yalechin         ###   ########.fr       */
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
	char			**envp;
	char			**paths;

}					t_program;

// compare strings
int	ft_strcmp(char *s1, char *s2)
{
	int	x;

	x = 0;
	while (s1[x])
	{
		if (s1[x] != s2[x])
			return (s1[x] - s2[x]);
		x++;
	}
	return (0);
}

// check if character is in the string
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
		if (program->input[x] == SINGLE_QUOTE && !q2)
			q1 = !q1;
		if (program->input[x] == DOUBLE_QUOTE && !q1)
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

// check is special character
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

// check if character has a double
bool	ft_check_for_double(int c1, int c2)
{
	if (c1 == RED_IN && c2 == RED_IN)
		return (true);
	if (c1 == RED_OUT && c2 == RED_OUT)
		return (true);
	return (false);
}

// check ig command
int	ft_check_for_cmd(char *token_str)
{
	if (ft_strcmp(token_str, "echo") == 0)
		return (0);
	else if (ft_strcmp(token_str, "pwd") == 0)
		return (0);
	else if (ft_strcmp(token_str, "unset") == 0)
		return (0);
	else if (ft_strcmp(token_str, "cd") == 0)
		return (0);
	else if (ft_strcmp(token_str, "exit") == 0)
		return (0);
	else if (ft_strcmp(token_str, "export") == 0)
		return (0);
	else
		return (1);
}

// add token types to the token list
void	ft_token_type(t_program *program)
{
	t_token	*temp;
	t_token	*head;

	temp = program->first;
	head = temp;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->token_str, "") == 0)
			temp->token_type = EMPTY;
		else if (ft_strcmp(temp->token_str, "|") == 0)
			temp->token_type = PIPE_T;
		else if (ft_strcmp(temp->token_str, "<") == 0)
			temp->token_type = INPUT;
		else if (ft_strcmp(temp->token_str, ">") == 0)
			temp->token_type = OUTPUT;
		else if (ft_strcmp(temp->token_str, "<<") == 0)
			temp->token_type = INPUT_D;
		else if (ft_strcmp(temp->token_str, ">>") == 0)
			temp->token_type = OUTPUT_D;
		else if (ft_strcmp(temp->token_str, "$") == 0)
			temp->token_type = D_SIGN_T;
		else if (ft_check_for_cmd(temp->token_str) == 0)
			temp->token_type = CMD;
		else
			temp->token_type = STR;
		temp = temp->next;
	}
	program->first = head;
}

// create a new line with spaces for the subsequent tokenization
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
				new_line[y++] = ' ';
			}
		}
		else
			new_line[y++] = program->input[x++];
	}
	new_line[y] = '\0';
	// clean input?
	return (new_line);
}

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

// create a token from the line
t_token	*new_token(char *new_line, int *x)
{
	t_token	*new_token;
	int		y;
	bool	in_quote;
	char	c;

	c = '?';
	in_quote = false;
	y = 0;
	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		exit(1);
	new_token->token_str = (char *)malloc(sizeof(ft_alloc(new_line, *x) + 1));
	if (!new_token->token_str)
		exit(1);
	while ((new_line[*x] && new_line[*x] != ' ') || (new_line[*x]
			&& new_line[*x] == ' ' && in_quote))
	{
		if (new_line[*x] == DOUBLE_QUOTE && c != SINGLE_QUOTE)
		{
			if (c == DOUBLE_QUOTE)
				c = '?';
			else
				c = DOUBLE_QUOTE;
			in_quote = !in_quote;
		}
		if (new_line[*x] == SINGLE_QUOTE && c != DOUBLE_QUOTE)
		{
			if (c == SINGLE_QUOTE)
				c = '?';
			else
				c = SINGLE_QUOTE;
			in_quote = !in_quote;
		}
		new_token->token_str[y++] = new_line[(*x)++];
	}
	new_token->token_str[y] = '\0';
	return (new_token);
}

// create the list of tokens
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

// check if redirection symbol
int	is_redirection_operator(t_token *token)
{
	return (ft_strcmp(token->token_str, ">") == 0 || ft_strcmp(token->token_str,
			">>") == 0 || ft_strcmp(token->token_str, "<") == 0
		|| ft_strcmp(token->token_str, "<<") == 0);
}

// check if pipe symbol
int	is_pipe(t_token *token)
{
	return (ft_strcmp(token->token_str, "|") == 0);
}

// check if variable symbol
int	is_variable(t_token *token)
{
	return (token->token_str[0] == '$');
}

// this is probably unnecessary as there are too many - delete later
int	is_valid_variable_name(char *str)
{
	if (ft_strcmp(str, "home") == 0)
		return (1);
	if (ft_strcmp(str, "user") == 0)
		return (1);
	return (0);
}

// checks token for pipe and redirections error
int	ft_check_tokens(t_program *program)
{
	t_token	*temp;
	t_token	*head;

	temp = program->first;
	head = temp;
	while (temp != NULL)
	{
		if (is_redirection_operator(temp) && (!temp->next
				|| is_redirection_operator(temp->next)))
		{
			printf("REDIRECTION ERROR\n");
			return (0);
		}
		if (is_pipe(temp) && (!temp->prev || !temp->next || is_pipe(temp->prev)
				|| is_pipe(temp->next)))
		{
			printf("PIPE ERROR\n");
			return (0);
		}
		/* maybe not necessary??? to much to check????
		if (is_variable(temp) && !is_valid_variable_name(temp->token_str))
		{
			printf("VARIABLE ERROR\n");
			return (0);
		}*/
		// what about echo???
		temp = temp->next;
	}
	program->first = head;
	return (1);
}

void	ft_free_program(t_program *program)
{
	/*int	x;
	x = 0;
	while (program->first)
	{
		free(program->first);
		x++;
	}*/
	free(program->input);
	free(program);
}

// stores the list of envp in the program structure
char	**ft_store_envp(char **envp)
{
	int		x;
	char	**envp_arr;

	x = 0;
	while (envp[x])
	{
		x++;
	}
	envp_arr = (char **)malloc(sizeof(char *) * x + 1);
	if (!envp_arr)
		return (NULL);
	x = 0;
	while (envp[x])
	{
		envp_arr[x] = ft_strdup(envp[x]);
		x++;
	}
	// free smth?
	return (envp_arr);
}

// find PATH in envp
char	*ft_find_path(t_program *program)
{
	int	x;
	int	len;

	x = 0;
	while (program->envp[x])
	{
		if (ft_strncmp(program->envp[x], "PATH=", 5) == 0)
		{
			len = ft_strlen(program->envp[x]) - 5;
			return (ft_substr(program->envp[x], 5, len));
		}
		x++;
	}
	return (NULL);
	// not sure what to return if path not found
}

// create paths from PATH - add / when necessary
void	ft_create_paths(t_program *program)
{
	char	*path;
	char	*temp;
	int		x;
	int		len;

	x = 0;
	path = ft_find_path(program);
	program->paths = ft_split(path, ':');
	while (program->paths[x])
	{
		len = ft_strlen(program->paths[x]) - 1;
		if (program->paths[x][len] != '/')
		{
			temp = ft_strjoin(program->paths[x], "/");
			free(program->paths[x]);
			program->paths[x] = temp;
		}
		x++;
	}
	// testing print - delete later
	// x = 0;
	// while (program->paths[x])
	// {
	// 	printf("%s\n", program->paths[x]);
	// 	x++;
	// }
}

static int	call_cmd_cd(char *dest, t_program *program)
{
		return (cmd_cd(dest, program));
}

void ft_execute (t_program *program)
{
	t_token *temp = program->first;
	int x = 0;
	while (temp != NULL)
	{
		if (temp->token_type == CMD)
		{
				if ( ft_strcmp(temp->token_str, "cd") == 0)
				{ 
					printf("CD COMMAND FOUND\n");
					call_cmd_cd(temp->next->token_str, program);
				}
				else if ( ft_strcmp(temp->token_str, "echo") == 0)
				{
					printf("ECHO COMMAND FOUND\n");
				}
				else if ( ft_strcmp(temp->token_str, "pwd") == 0)
				{
					printf("PWD COMMAND FOUND\n");
				}
				else if ( ft_strcmp(temp->token_str, "export") == 0)
				{
					printf("EXPORT COMMAND FOUND\n");
				}
				else if ( ft_strcmp(temp->token_str, "unset") == 0)
				{
					printf("UNSET COMMAND FOUND\n");
				}
				else if ( ft_strcmp(temp->token_str, "env") == 0)
				{
					printf("ENV COMMAND FOUND\n");
				}
				else if ( ft_strcmp(temp->token_str, "exit") == 0)
				{
					printf("EXIT COMMAND FOUND\n");
				}
			}
		temp = temp->next;
	}
}
{

}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_program *program;

	if (ac != 1 || av[1])
	{
		printf("ERROR: wrong number of arguments!");
		exit(0);
	}

	program = malloc(sizeof(t_program));
	program->input = NULL;
	program->envp = NULL;

	program->envp = ft_store_envp(envp);
	int x = 0;
	while (program->envp[x])
	{
		printf("%s\n", program->envp[x]);
		x++;
	}
	char *path = ft_find_path(program);
	// printf("PATH FOUND: %s\n", path);

	ft_create_paths(program);

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
		// printf("Final line: %s\n", program->split_line);
		program->first = ft_tokenization(program);

		t_token *temp = program->first;
		ft_token_type(program);

		while (temp != NULL)
		{
			printf("TOKEN is: [%s] token type is [%d]\n", temp->token_str,
				temp->token_type);
			temp = temp->next;
		}

		if (ft_check_tokens(program))
			printf("ALL TOKEN GOOD!\n");

		 ft_execute(program);

		ft_free_program(program);
	}
	return (0);
}