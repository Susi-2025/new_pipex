/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_execute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 08:59:06 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/25 20:38:52 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	char	**split_command(t_pipex *pipex, char *av);
static	char	*build_path(char **command, char **envp);
static	char	**find_path(char **envp);
static	char	*find_path_cmd(char **out_path, char *command);

void	execute(t_pipex *pipex, char **av, char **envp, int in_out)
{
	char	**command;
	char	*cmd_path;

	command = NULL;
	if (in_out == 1)
		command = split_command(pipex, av[2]);
	else if (in_out == 2)
		command = split_command(pipex, av[3]);
	cmd_path = build_path(command, envp);
	ft_free_triptr(&command);
	if (!cmd_path)
		error(pipex, "Get path for command error", 1);
	execve(cmd_path, command, envp);
}

static	char	**split_command(t_pipex *pipex, char *av)
{
	char	**out_cmd;

	out_cmd = ft_split(av, ' ');
	if (!out_cmd)
		error(pipex, "Split error", 1);
	return (out_cmd);
}

static	char	*build_path(char **command, char **envp)
{
	char	**out_path;
	char	*path;

	out_path = find_path(envp);
	if (!out_path)
		return (NULL);
	path = find_path_cmd(out_path, command[0]);
	if (!path)
		return (NULL);
	return (path);
}

static	char	**find_path(char **envp)
{
	char	**out_path;
	char	*path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
			path = envp[i] + 5;
		i++;
	}
	if (!path)
		return (NULL);
	out_path = ft_split(path, ':');
	if (!out_path)
		return (NULL);
	return (out_path);
}

static	char	*find_path_cmd(char **out_path, char *command)
{
	int		i;
	char	*path;
	char	*temp;

	i = 0;
	path = NULL;
	while (out_path[i])
	{
		temp = ft_strjoin(out_path[i], "/");
		if (!temp)
			return (NULL);
		path = ft_strjoin(temp, command);
		if (!path)
			return (NULL);
		free(temp);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (path);
}
