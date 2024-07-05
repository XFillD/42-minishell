/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:07:50 by yalechin          #+#    #+#             */
/*   Updated: 2024/06/16 14:01:59 by yalechin         ###   ########.fr       */
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
	//char			**envp;
	t_envp *envp; 
	//char			**paths;

}					t_program;

int					cmd_echo(t_statement *statement, bool has_n);
int					cmd_pwd(void);
int					cmd_cd(char *path, t_program *program);
int					cmd_env(t_program *program);
int					cmd_export(t_statement *statement, t_program *program);
void				cmd_exit(t_statement *s, t_program *program);
int					unset_var(char *var_name, t_envp **head)
int					cmd_unset(t_statement *s, t_vlst **head);

bool				is_valid_id(char *str);

bool				is_all_digits_or_signals(char *str);

void				destroy(t_program *program)

t_statement			*p_new_node(int argc);

size_t				p_lstsize(t_statement *head);

void				p_lstclear(t_statement **head);

t_vlst				*v_new_node(char *var_name, char *var_value,
						bool is_exported);
void				v_lstadd_back(t_vlst **head, t_vlst *new);
t_vlst				*v_lstlast(t_envp *node);
size_t				v_lstsize_exported(t_vlst **head);

bool				get_exported_state(char *var_name, t_vlst **head);
char				*get_fromvlst(char *var_name, t_vlst **head);

char				*get_varvalue_fromvlst(char *var_name, t_program *program);

char				**split_envp(char *env);
int					save_user_vars(char *statement, t_envp **head, bool to_export);

#endif