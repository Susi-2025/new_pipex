/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_child_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 08:59:06 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/26 14:09:31 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	open_file(t_pipex *pipex, char **av, int in_out);
static	void	redirect_pipe(t_pipex *pipex, int in_fd, int out_pipe);

void	first_process(t_pipex *pipex, char **av, char **envp)
{
	int	code;

	close(pipex->pipe_fd[0]);
	open_file(pipex, av, 1);
	redirect_pipe(pipex, pipex->fd_in, pipex->pipe_fd[1]);
	/*
	if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
		error(pipex, "Pipe input error", 1);
	if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
		error(pipex, "Pipe output error", 1);
	*/
	close(pipex->fd_in);
	close(pipex->pipe_fd[1]);
	execute(pipex, av[2], envp);
//	close_stack(pipex);
}

void	second_process(t_pipex *pipex, char **av, char **envp)
{
	close(pipex->pipe_fd[1]);
	open_file(pipex, av, 2);
	redirect_pipe(pipex, pipex->pipefd[0], pipex->fd_out);
	/*
	if (dup2(pipex->fd_out, STDOUT_FILENO) == -1)
		error(pipex, "Pipe output error", 1);
	if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
		error(pipex, "Pipe input error", 1);
	*/
	close(pipe->fd_out);
	close(pipe->pipe_fd[0]);
	execute(pipex, av[3], envp);
//	close_stack(pipex);
}

static void	open_file(t_pipex *pipex, char **av, int in_out)
{
	if (in_out == 1)
	{
		pipex->fd_in = open(av[1], O_RDONLY);
		if (pipex->fd_in == -1)
			error(pipex, "Open input file error", 1);
	}
	else if (in_out == 2)
	{
		pipex->fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->fd_out == -1)
			error(pipex, "Open output file error", 1);
	}
}

static	void	redirect_pipe(t_pipex *pipex, int in_fd, int out_pipe)
{
	if (dup2(in_fd, STDIN_FILENO) == -1)
			error(pipex, "Pipe input error", 1);
	if (dup2(out_pipe, STDOUT_FILENO) == -1)
			error(pipex, "Pipe output error", 1);
/*
	if (in_out == 1)
	{
		if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
			error(pipex, "Pipe input error", 1);
		if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
			error(pipex, "Pipe output error", 1);
	}
	if (in_out == 2)
	{
		if (dup2(pipex->fd_out, STDOUT_FILENO) == -1)
			error(pipex, "Pipe output error", 1);
		if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
			error(pipex, "Pipe input error", 1);
	}
*/
}
