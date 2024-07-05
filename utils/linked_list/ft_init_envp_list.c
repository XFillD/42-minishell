#include "minishell.h"

static void	init_oldpwd(t_envp **head)
{
	char	*temp;

	unset_var("OLDPWD", head);
	temp = ft_strjoin("OLDPWD=", getenv("HOME"));
	save_user_vars(temp, head);
	free(temp);
}

t_envp	*ft_init_envp_list(char **envp)
{
	t_envp *head; 
	t_envp *temp;

	char **line; 
	size_t	i;

	line = split_envp(envp[0]);
	head = v_new_node(line[0], line[1]);
	free(line);
	i = 1;
	temp = head;
	while (envp[i])
	{
		line = split_envp(envp[i]);
		temp->next = v_new_node(line[0], line[1]);
		free(line);
		temp = temp->next;
		i += 1;
	}
	init_oldpwd(&head);
	return (head);
}
