/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yana <yana@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:07:50 by yalechin          #+#    #+#             */
/*   Updated: 2024/07/08 15:46:31 by yana             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _GNU_SOURCE
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

int	exit_status;

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

#endif