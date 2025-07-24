/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_pipex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 08:59:06 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/24 20:47:39 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
		error(&pipex, 1);
	if (pipe(pipex.pipefd) == -1)
		error(&pipex, 1);
	child_process(&pipex, av, envp);
	parent_close(&pipex);
	return (0);
}

static void	child_process(t_pipex *pipex, char **av, char **envp)
{
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
		error(pipex, EXIT_FAILURE);
	else if (pipex->pid1 == 0)
		first_process(pipex, av, envp);
	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
		error(pipex, EXIT_FAILURE);
	else if (pipex->pid2 == 0)
		second_process(&pipex, av, envp);
}

static void	parent_close(t_pipex *pipex)
{
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	waitpid(pipex->pid1, status, 0);
	waitpid(pipex->pid2, status, 0);
	finish(pipex, status);
	return (0);
}
