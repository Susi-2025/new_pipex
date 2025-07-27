/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_pipex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 08:59:06 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/27 20:35:56 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	first_child_run(t_stack *pipex, char **av, char **envp);
static void	second_child_run(t_stack *pipex, char **av, char **envp);
static void	parent_close(t_stack *pipex);
static void	redirect_pipe(t_stack *pipex, int in, int out);

int	main(int ac, char **av, char **envp)
{
	t_stack	pipex;

	if (ac != 5)
		err_msg("Usage: ./pipex file1 cmd1 cmd2 file2\n", 1);
	if (pipe(pipex.pipefd) == -1)
		err_exit("pipe", 1);
	for (int i = 0; i < ac; i++)
    	fprintf(stderr, "arg[%d] = %s\n", i, av[i]);
	first_child_run(&pipex, av, envp);
	second_child_run(&pipex, av, envp);
	parent_close(&pipex);
	return (0);
}

static	void	first_child_run(t_stack *pipex, char **av, char **envp)
{
	pipex->pid[0] = fork();
	if (pipex->pid[0] == -1)
		err_clean_exit(pipex, "fork", 1);
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

static	void	second_child_run(t_stack *pipex, char **av, char **envp)
{
	pipex->pid[1] = fork();
	if (pipex->pid[1] == -1)
		err_clean_exit(pipex, "fork", 1);
	else if (pipex->pid[1] == 0)
	{
		close(pipex->pipefd[1]);
		pipex->fd[1] = open(av[4], O_WRONLY);
		if (pipex->fd[1] == -1)
			err_clean_exit(pipex, av[1], 1);
		redirect_pipe(pipex, pipex->pipefd[0], pipex->fd[1]);
		run_command(pipex, av[3], envp);
	}
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

static	void	redirect_pipe(t_stack *pipex, int in, int out)
{
	if (dup2(in, STDIN_FILENO) == -1)
		err_clean_exit(pipex, "Dup2 error", 1);
	if (dup2(out, STDOUT_FILENO) == -1)
		err_clean_exit(pipex, "Dup2 error", 1);
	close(in);
	close(out);
}
