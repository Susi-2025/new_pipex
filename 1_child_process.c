/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_child_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 08:59:06 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/25 20:41:33 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	open_file(t_pipex *pipex, char **av, int in_out);

void	first_process(t_pipex *pipex, char **av, char **envp)
{
	close(pipex->pipe_fd[0]);
	open_file(pipex, av, 0);
	if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
		error(pipex, "Pipe input error", 1);
	if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
		error(pipex, "Pipe output error", 1);
	execute(pipex, av, envp, 1);
	close_stack(pipex);
}

void	second_process(t_pipex *pipex, char **av, char **envp)
{
	close(pipex->pipe_fd[1]);
	open_file(pipex, av, 1);
	if (dup2(pipex->fd_out, STDOUT_FILENO) == -1)
		error(pipex, "Pipe output error", 1);
	if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
		error(pipex, "Pipe input error", 1);
	execute(pipex, av, envp, 2);
	close_stack(pipex);
}

static void	open_file(t_pipex *pipex, char **av, int in_out)
{
	if (in_out == 0)
	{
		pipex->fd_in = open(av[1], O_RDONLY);
		if (pipex->fd_in == -1)
			error(pipex, "Open input file error", 1);
	}
	else if (in_out == 1)
	{
		pipex->fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->fd_out == -1)
			error(pipex, "Open output file error", 1);
	}
}
