/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_pipex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 08:59:06 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/28 21:10:29 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	initial(t_stack *pipex);
static void	parent_close(t_stack *pipex);

int	main(int ac, char **av, char **envp)
{
	t_stack	pipex;

	if (ac != 5)
		err_msg("Usage: ./pipex file1 cmd1 cmd2 file2\n", 1);
	initial(&pipex);
	if (pipe(pipex.pipefd) == -1)
		err_exit("pipe", 1);
	first_child_run(&pipex, av, envp);
	second_child_run(&pipex, av, envp);
	parent_close(&pipex);
	return (0);
}

static	void	initial(t_stack *pipex)
{
	pipex->pipefd[0] = -1;
	pipex->pipefd[1] = -1;
	pipex->pid[0] = -1;
	pipex->pid[1] = -1;
	pipex->fd[0] = -1;
	pipex->fd[1] = -1;
}

static	void	parent_close(t_stack *pipex)
{
	int	status1;
	int	status2;

	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	waitpid(pipex->pid[0], &status1, 0);
	waitpid(pipex->pid[1], &status2, 0);
	if (WIFEXITED(status2))
		exit(WEXITSTATUS(status2));
	else
		exit(1);
}
