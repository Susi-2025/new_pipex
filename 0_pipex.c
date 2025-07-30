/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_pipex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 08:59:06 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/30 14:25:42 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	initial(t_stack *pipex);
static void	parent_close(t_stack *pipex);

int	main(int ac, char **av, char **envp)
{
	t_stack	pipex;

	if (ac != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	initial(&pipex);
	if (pipe(pipex.pipefd) == -1)
		err_exit("pipe err", 1);
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
	int		status;
	int		exit_code;
	pid_t	pid;

	exit_code = 1;
	close_stack(pipex);
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == pipex->pid[1])
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else
				exit_code = 1;
		}
		pid = wait(&status);
	}
	exit (exit_code);
}
