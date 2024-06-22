#include "minishell.h"

int	cmd_env(t_data *data)
{
	t_vlst	*temp;

	temp = data->envp_lst;
	while (temp != NULL)
	{
		if (temp->is_exported)
			printf("%s=%s\n", temp->var_name, temp->var_value);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}