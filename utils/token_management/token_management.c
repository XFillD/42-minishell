#include "minishell.h"

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

void clear_token_list(t_token *head) {
    t_token *current = head;
    t_token *next;

    // Clear the token linked list
    while (current != NULL) {
        next = current->next;
        free(current->token_str);  
        free(current);
        current = next;
    }

}

