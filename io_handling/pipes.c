/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhauba <fhauba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:33:47 by fhauba            #+#    #+#             */
/*   Updated: 2024/07/13 16:49:06 by fhauba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void handle_left(t_token tkn,t_program *program, int pipe_fd[2])
{
    printf("handle_left\n");
    close(STDOUT_FILENO); // Zavření standardního výstupu
    dup2(pipe_fd[1], STDOUT_FILENO); // Duplikace konce pro zápis do standardního výstupu
    close(pipe_fd[1]); // Zavření konce pro zápis
    close(pipe_fd[0]); // Zavření konce pro čtení
    ft_execute_complex(program); // Spuštění příkazu
}

static void handle_right(t_token tkn,t_program *program, int pipe_fd[2])
{
    close(STDIN_FILENO); // Zavření standardního vstupu
    dup2(pipe_fd[0], STDIN_FILENO); // Duplikace konce pro čtení do standardního vstupu
    close(pipe_fd[0]); // Zavření konce pro čtení
    close(pipe_fd[1]); // Zavření konce pro zápis
    ft_execute_complex(program); // Spuštění příkazu
}

void execute_pipe(t_program *program)
{
    t_token *temp = program->first;
    pid_t child_pid;
    int pipe_fd[2];
    int status;

    //if (pipe(pipe_fd) == -1)
    //    panic(program, PIPE_ERR, EXIT_FAILURE);
    child_pid = fork();
    //if (child_pid == -1)
    //    panic(program, FORK_ERR, EXIT_FAILURE);
    //if (child_pid == 0)
    handle_left(*temp, program, pipe_fd);
    handle_right(*temp->next, program, pipe_fd);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(child_pid, &status, 0);
    //g_exit_status = WEXITSTATUS(status);
}