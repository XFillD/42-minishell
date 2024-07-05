#include "minishell.h"

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
		//printf("ALL GOOD - QUOTES MATCH\n");
		return (0);
	}
	//printf("NOT GOOD - QUOTES DO NOT MATCH\n");
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