#include "minishell.h"

int	cmd_pwd(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (cwd == NULL)
	{
		perror("minishell:");
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (EXIT_SUCCESS);
}