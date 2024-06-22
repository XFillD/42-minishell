#include "minishell.h"

static int	print_perror_msg(char *path)
{
	char	*error_msg;	

	error_msg = ft_strjoin("minishell: cd: ", path);
	perror(error_msg);
	free(error_msg);
	return (EXIT_FAILURE);
}

static void	update_pwd(t_data *data)
{
	char	cwd[PATH_MAX];
	char	*updated_var;

	getcwd(cwd, PATH_MAX);
	updated_var = ft_strjoin("PWD=", cwd);
	save_user_vars(updated_var, &data->envp_lst, true);
	free(updated_var);
}

static void	update_oldpwd(char *temp, t_data *data)
{
	char	*oldpwd;

	oldpwd = ft_strjoin("OLDPWD=", temp);
	save_user_vars(oldpwd, &data->envp_lst, true);
	free(oldpwd);
}

static int	cd_oldpwd(char *temp, t_data *data)
{
	char	*oldpwd;

	oldpwd = get_fromvlst("OLDPWD", &data->envp_lst);
	if (!oldpwd)
	{	
		ft_putendl_fd(OLDPWD_NOT_SET, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (chdir(oldpwd) == SUCCESS)
	{
		ft_putendl_fd(oldpwd, STDOUT_FILENO);
		update_oldpwd(&temp[0], data);
		update_pwd(data);
		return (EXIT_SUCCESS);
	}
	return (print_perror_msg(oldpwd));
}

int	cmd_cd(char *path, t_data *data)
{
	char	temp[PATH_MAX];

	getcwd(temp, PATH_MAX);
	if (path == NULL || ft_streq(path, "~"))
	{
		update_oldpwd(&temp[0], data);
		chdir(getenv("HOME"));
		update_pwd(data);
		return (EXIT_SUCCESS);
	}
	if (ft_streq(path, "-"))
		return (cd_oldpwd(&temp[0], data));
	if (chdir(path) == SUCCESS)
	{
		update_oldpwd(&temp[0], data);
		update_pwd(data);
		return (EXIT_SUCCESS);
	}
	return (print_perror_msg(path));
}