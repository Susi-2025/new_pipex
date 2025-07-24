/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_child.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 08:59:06 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/24 20:19:40 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	open_file(t_pipex *pipex, int in_out);

void	first_process(t_pipex *pipex, char **av, char **envp)
{	
	open_file(pipex, av, 0);
	if (dup2(pipex->fd_in, STDIN_FILENO)== -1)
		error(pipex, 1);
	if (dup2(pipex->pipefd[1], STDOUT_FILENO) == -1)
		error(pipex, 1);
	close_stack(pipex);
	execute(pipex, av, envp);
}

void	second_process(t_pipex *pipex, int *pipefd)
{
	open_file(pipex, av, 1);
	if (dup2(pipex->fd_out, STDOUT_FILENO) ==  -1)
		error(pipex, 1);
	if (dup2(pipex->pipefd[0], STDIN_FILENO) == -1)
		error(pipex, 1);
	close_stack(pipex);
	execute(pipex, av, envp);
}

static void	open_file(t_pipex *pipex, char **av, int in_out)
{	
	if (in_out == 0)
	{
		pipex->fd_in = open(av[1], O_RDONLY);
		if (pipex->fd_in == -1)
			error(pipex, 1);
	}
	else if (in_out == 1)
	{
		pipex->fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->fd_out == -1)
			error(pipex, 1);
	}
}
/*
static	void execute(t_stack *pipex)
{
	char	**cmd;
	char	**temp_paths;
	char	*path;

	cmd = ft_split(pipex->av[2], ' ');
	temp_paths = filter_path(pipex->envp);
	path = get_path(temp_paths, cmd[0]);
	if (execve(path, cmd, pipex->envp) == -1)
		error(pipex, EXIT_FAILURE);
}
*/
