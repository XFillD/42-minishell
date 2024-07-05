/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:31:55 by yalechin          #+#    #+#             */
/*   Updated: 2024/06/23 20:21:05 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_program(t_program *program) {
    //clear_token_list(program);
	t_envp *current = program->envp;
    t_envp *next;

    // Clear the token linked list
    while (current != NULL) {
        next = current->next;
        free(current->var_name);  
        free(current);
        current = next;
    }

    free(program->input);
    free(program->split_line); 

    free(program);
}

t_envp	*v_new_node(char *var_name, char *var_value)
{
	t_envp	*new_node;

	new_node = malloc(sizeof(t_envp));
	new_node->var_name = var_name;
	new_node->var_value = var_value;
	new_node->next = NULL;
	return (new_node);
}

int	save_user_vars(char *statement, t_envp **head)
{
	char	**line;

	line = split_envp(statement);
	//if (get_exported_state(line[0], head))
		//to_export = true;
	unset_var(line[0], head);
	v_lstadd_back(head, v_new_node(line[0], line[1]));
	free(line);
	return (EXIT_SUCCESS);
}

/*// find PATH in envp
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
}*/

char	*get_fromvlst(char *var_name, t_envp **head)
{
	t_envp	*temp;

	temp = *head;
	while (temp != NULL)
	{
		if (streq(var_name, temp->var_name))
			return (temp->var_value);
		temp = temp->next;
	}
	return (NULL);
}

static int	call_cmd_cd(char *dest, t_program *program)
{
	return (cmd_cd(dest, program));
}

void	ft_putendl_fd(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	write(fd, "\n", 1);
}

void	ft_execute(t_program *program)
{
	t_token	*temp;
	int		x;

	temp = program->first;
	x = 0;
	while (temp != NULL)
	{
		if (temp->token_type == CMD)
		{
			if (ft_strcmp(temp->token_str, "cd") == 0)
			{
				//printf("CD COMMAND FOUND\n");
				call_cmd_cd(temp->next->token_str, program);
			}
			else if (ft_strcmp(temp->token_str, "echo") == 0)
			{
				printf("ECHO COMMAND FOUND\n");
			}
			else if (ft_strcmp(temp->token_str, "pwd") == 0)
			{
				//printf("PWD COMMAND FOUND\n");
				cmd_pwd();
			}
			else if (ft_strcmp(temp->token_str, "export") == 0)
			{
				printf("EXPORT COMMAND FOUND\n");
			}
			else if (ft_strcmp(temp->token_str, "unset") == 0)
			{
				printf("UNSET COMMAND FOUND\n");
			}
			else if (ft_strcmp(temp->token_str, "env") == 0)
			{
				printf("ENV COMMAND FOUND\n");
			}
			else if (ft_strcmp(temp->token_str, "exit") == 0)
			{
				printf("EXIT COMMAND FOUND\n");
			}
		}
		temp = temp->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp; 
	t_program *program;

	if (ac != 1 || av[1])
	{
		printf("ERROR: wrong number of arguments!");
		exit(0);
	}

	program = malloc(sizeof(t_program));
	if(!program)
		exit(1);
	program->input = NULL;
	program->split_line = NULL; 
	program->first = NULL; 
	program->envp = NULL; 
	program->envp = ft_init_envp_list(envp);


	//program->envp = NULL;

	//program->envp = ft_store_envp(envp);
	//int x = 0;
	//while (program->envp[x])
	//{
	//	printf("%s\n", program->envp[x]);
	//	x++;
	//}
	//char *path = ft_find_path(program);
	// printf("PATH FOUND: %s\n", path);

	//ft_create_paths(program);

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

		//t_token *temp = program->first;
		ft_token_type(program);

		/*while (temp != NULL)
		{
			printf("TOKEN is: [%s] token type is [%d]\n", temp->token_str,
				temp->token_type);
			temp = temp->next;
		}

		if (ft_check_tokens(program))
			printf("ALL TOKEN GOOD!\n");*/

		ft_execute(program);
		clear_token_list(program->first);
		program->first = NULL;
		
	}
	ft_free_program(program);
	return (0);
}