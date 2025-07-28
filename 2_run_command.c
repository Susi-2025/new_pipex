/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_run_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:21:11 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/27 20:44:13 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	char	**cmd_parse(char *commands);
static	char	*check_cmd_only(char *cmd);

void	run_command(t_stack *pipex, char *command, char **envp)
{
	char	*cmd_path;
	char	**cmd_argvs;

	cmd_argvs = cmd_parse(command);
	if (!cmd_argvs)
		err_clean_exit(pipex, "command error", 127);
	cmd_path = check_cmd_only(cmd_argvs[0]);
	if (!cmd_path)
	{
		cmd_path = get_path(envp, cmd_argvs[0]);
		if (!cmd_path)
		{
			ft_free_triptr(&cmd_argvs);
			err_clean_exit(pipex, "no path", 127);
		}
	}
	execve(cmd_path, cmd_argvs, envp);
	perror("execve");
	ft_free_triptr(&cmd_argvs);
	free(cmd_path);
	if (access(cmd_argvs[0], F_OK) == 0 && access(cmd_argvs[0], X_OK) != 0)
		err_clean_exit(pipex, "permission denied", 126);
	err_clean_exit(pipex, "execution error", 1);
}

// this function will parse the commands-av[2]. For example: av[2] = 'ls -la'
// First, we ignore any space or tabs after checking empty commands.
// If the commands only have space, NULL will be return.
// Next we use the split to remove space in the commands and return out.
// If error, we will free out, and return NULL;
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
	if (!out || !out[0])
	{
		ft_free_triptr(&out);
		return (NULL);
	}
	return (out);
}

static	char	*check_cmd_only(char *cmd)
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
		return (NULL);
	}
	return (NULL);
}
