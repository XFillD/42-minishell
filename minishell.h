/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhauba <fhauba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:07:50 by yalechin          #+#    #+#             */
/*   Updated: 2024/07/14 12:10:09 by fhauba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define PIPE_T 1
# define INPUT 2
# define OUTPUT 3
# define INPUT_D 4
# define OUTPUT_D 5
# define D_SIGN_T 6
# define STR 7
# define EMPTY 8
# define CMD 9

# define DOUBLE_QUOTE '\"'
# define SINGLE_QUOTE '\''

# define RED_IN '<'
# define RED_OUT '>'
# define PIPE '|'
# define D_SIGN '$'

# define PIPE_ERR "minishell: pipe() failed"
# define FORK_ERR "minishell: fork() failed"

typedef struct s_envp
{
	char			*var_name;
	char			*var_value;
	struct s_envp	*next;
}					t_envp;

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
	char			**envp_origin;
	t_envp *envp; 
	//char			**paths;

}					t_program;

void execute_pipe(t_program *program, t_token *token);
void ft_execute_complex(t_program *program, t_token *token);

#endif