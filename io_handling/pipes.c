/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhauba <fhauba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:33:47 by fhauba            #+#    #+#             */
/*   Updated: 2024/07/14 13:53:35 by fhauba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void handle_left(t_token *tkn,t_program *program, int pipe_fd[2])
{
    close(STDOUT_FILENO); // Zavření standardního výstupu
    dup(pipe_fd[1]); // Duplikace konce pro zápis do standardního výstupu
    close(pipe_fd[0]); // Zavření konce pro zápis
    close(pipe_fd[1]); // Zavření konce pro čtení
    ft_execute_complex(program, tkn);
}

static void handle_right(t_token *tkn,t_program *program, int pipe_fd[2])
{
    close(STDIN_FILENO); // Zavření standardního vstupu
    dup(pipe_fd[0]); // Duplikace konce pro čtení do standardního vstupu
    close(pipe_fd[0]); // Zavření konce pro čtení
    close(pipe_fd[1]); // Zavření konce pro zápis
    ft_execute_complex(program, tkn); // Spuštění příkazu
}

void execute_pipe(t_program *program, t_token *token)
{
    pid_t	child_pid;
	int		pipedes[2];
	int		temp_status;

	token->token_type = STR;
	if (pipe(pipedes) == -1)
        printf("pipe error\n");
		//panic(program, PIPE_ERR, EXIT_FAILURE);
	child_pid = fork();
	if (child_pid == -1)
        printf("fork error\n");
		//panic(program, FORK_ERR, EXIT_FAILURE);
	if (child_pid == 0) {
        handle_left(token, program, pipedes);
    }
	handle_right(token->next, program, pipedes);
	close(pipedes[0]);
	close(pipedes[1]);
	waitpid(child_pid, &temp_status, 0);
}