/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_pipex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 08:59:06 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/25 20:44:12 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process(t_pipex *pipex, char **av, char **envp);
static void	parent_close(t_pipex *pipex);

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
		error(&pipex, "argument error", 1);
	pipex.ac = ac;
	if (pipe(pipex.pipe_fd) == -1)
		error(&pipex, "pipex: pipe", 1);
	child_process(&pipex, av, envp);
	parent_close(&pipex);
	return (0);
}

static void	child_process(t_pipex *pipex, char **av, char **envp)
{
	pipex->p_id1 = fork();
	if (pipex->p_id1 == -1)
		error(pipex, "fork error", 1);
	else if (pipex->p_id1 == 0)
		first_process(pipex, av, envp);
	pipex->p_id2 = fork();
	if (pipex->p_id2 == -1)
		error(pipex, "fork error", 1);
	else if (pipex->p_id2 == 0)
		second_process(pipex, av, envp);
}

static void	parent_close(t_pipex *pipex)
{
	int	status1;
	int	status2;

	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	waitpid(pipex->p_id1, &status1, 0);
	if (WIFEXITED(status1))
		exit(WEXITSTATUS(status1));
	waitpid(pipex->p_id2, &status2, 0);
	if (WIFEXITED(status2))
		exit(WEXITSTATUS(status2));
	else
		exit(1);
}
