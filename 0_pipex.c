/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_pipex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 08:59:06 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/24 15:40:51 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	open_file(t_stack *pipex, int in_out);

int	main(int ac, char **av, char **envp)
{
	t_stack	pipex;
	int	pipefd[2];
	pid_t pid1;
	pid_t pid2;

	if (ac != 5)
		return (0);
	pipex.ac = ac;
	pipex.av = av;
	pipex.envp = envp;
	if(pipe(pipefd) == -1)
		error(&pipex, EXIT_FAILURE);
	
	pid1 = fork();
	if (pid1 == -1)
		error(&pipex, EXIT_FAILURE);
	else if (pid1 == 0)
		first_process(&pipex, pipefd);
	
	pid2 = fork();
	if (pid2 == -1)
		error(&pipex, EXIT_FAILURE);
	else if (pid2 == 0)
		second_process(&pipex, pipefd);

	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	free_stack(pipex);
	return (0);
}

void	child_process(t_stack *pipex, int *pipefd)
{
	int	fd;
	
	fd = open_file(pipex, 0);
	dup2(fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(fd);
	close(pipefd[0]);
	close(pipefd[1]);
	execute(pipex);
}

void	second_process(t_stack *pipex, int *pipefd)
{
	int	fd;

	fd = open_file(pipex, 1);
	dup2(fd, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(fd);
	close(pipefd[1]);
	close(pipefd[0]);
	execute(pipex);
}

static int	open_file(t_stack *pipex, int in_out)
{	
	int	fd;

	if (in_out == 0)
		fd = open(pipex->av[1], O_RDONLY);
	else if (in_out == 1)
		fd = open(pipex->av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error(pipex, EXIT_FAILURE);
	return (fd);
}

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
