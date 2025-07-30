/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_run_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:21:11 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/30 17:43:32 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	char	**cmd_parse(char *commands);
static	int	check_path_envp(char **envp);
static	char	*check_cmd_only(t_stack *pipex, char *cmd, char **cmd_argvs);

void	run_command(t_stack *pipex, char *command, char **envp)
{
	char	*cmd_path;
	char	**cmd_argvs;

	cmd_argvs = cmd_parse(command);
	if (!cmd_argvs)
		handle_command_error(pipex, 127);
	cmd_path = check_cmd_only(pipex, cmd_argvs[0], cmd_argvs);
	if (!cmd_path)
	{
		if (check_path_envp(envp) == 0)
			handle_envp_error(pipex, cmd_argvs, 127);
		cmd_path = get_path(envp, cmd_argvs[0]);
		if (!cmd_path)
		{
			print_error(cmd_argvs[0], NULL);
			ft_free_triptr(&cmd_argvs);
			handle_cmd_path_err(pipex, NULL, 127);
		}
	}
	execve(cmd_path, cmd_argvs, envp);
	handle_exec_error(pipex, cmd_path, cmd_argvs);
}

static	char	**cmd_parse(char *commands)
{
	char	**out;

	if (!commands)
		return (NULL);
	while (*commands == ' ' || *commands == '\t')
		commands++;
	if (*commands == '\0')
		return (NULL);
	out = ft_split(commands, ' ');
	if (!out || !out[0] || out[0][0] == '\0')
	{
		ft_free_triptr(&out);
		return (NULL);
	}
	return (out);
}

static	char	*check_cmd_only(t_stack *pipex, char *cmd, char **cmd_argvs)
{
	char	*out;

	if (!cmd)
		return (NULL);
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, X_OK) == 0)
		{
			out = ft_strdup(cmd);
			if (!out)
				return (NULL);
			return (out);
		}
		else if (access(cmd, F_OK) == 0)
		{
			out = ft_strdup(cmd);
			if (!out)
				return (NULL);
			return (out);
		}
		handle_no_file(pipex, cmd_argvs);
	}
	return (NULL);
}

static	int	check_path_envp(char **envp)
{
	int	out;
	int	i;

	if (!envp)
		return (0);
	i = 0;
	out = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
		{
			out = 1;
			break ;
		}
		i++;
	}
	return (out);
}
