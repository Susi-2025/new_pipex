/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_children.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 08:59:06 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/30 13:13:16 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	redirect_pipe(t_stack *pipex, int in, int out);

void	first_child_run(t_stack *pipex, char **av, char **envp)
{
	pipex->pid[0] = fork();
	if (pipex->pid[0] == -1)
		err_clean_exit(pipex, "fork1 error", 1);
	else if (pipex->pid[0] == 0)
	{
		close(pipex->pipefd[0]);
		pipex->fd[0] = open(av[1], O_RDONLY);
		if (pipex->fd[0] == -1)
			err_clean_exit(pipex, av[1], 1);
		redirect_pipe(pipex, pipex->fd[0], pipex->pipefd[1]);
		run_command(pipex, av[2], envp);
	}
}

void	second_child_run(t_stack *pipex, char **av, char **envp)
{
	pipex->pid[1] = fork();
	if (pipex->pid[1] == -1)
		err_clean_exit(pipex, "fork2 error", 1);
	else if (pipex->pid[1] == 0)
	{
		close(pipex->pipefd[1]);
		pipex->fd[1] = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->fd[1] == -1)
			err_clean_exit(pipex, av[4], 1);
		redirect_pipe(pipex, pipex->pipefd[0], pipex->fd[1]);
		run_command(pipex, av[3], envp);
	}
}

static	void	redirect_pipe(t_stack *pipex, int in, int out)
{
	if (dup2(in, STDIN_FILENO) == -1)
		err_clean_exit(pipex, "Dup2 error", 1);
	if (dup2(out, STDOUT_FILENO) == -1)
		err_clean_exit(pipex, "Dup2 error", 1);
	close(in);
	close(out);
}
