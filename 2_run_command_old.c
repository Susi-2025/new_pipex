/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_run_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:21:11 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/29 18:48:19 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	char	**cmd_parse(char *commands);
static	char	*check_cmd_only(char *cmd);
static	void	handle_error(t_stack *pipex, char *cmd_path, char **cmd_argvs);

void	run_command(t_stack *pipex, char *command, char **envp)
{
	char	*cmd_path;
	char	**cmd_argvs;

	cmd_argvs = cmd_parse(command);
	if (!cmd_argvs)
		err_clean_exit(pipex, "Command not found", 127);
	cmd_path = check_cmd_only(cmd_argvs[0]);
	if (!cmd_path)
	{
		cmd_path = get_path(envp, cmd_argvs[0]);
		if (!cmd_path)
		{
			ft_free_triptr(&cmd_argvs);
			err_cmd_clean_exit(pipex, NULL, 127);
		}
	}
	execve(cmd_path, cmd_argvs, envp);
	handle_error(pipex, cmd_path, cmd_argvs);
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

static	void	handle_error(t_stack *pipex, char *cmd_path, char **cmd_argvs)
// {
// 	int	exit_code;

// 	ft_free_triptr(&cmd_argvs);
// 	free(cmd_path);
// 	if (errno == EACCES)
// 		exit_code = 126;
// 	else if (errno == ENOENT)
// 		exit_code = 127;
// 	else
// 		exit_code = 1;
// 	err_clean_exit(pipex, NULL, exit_code);
// }
{
	int	exit_code;
	int	save_errno;

	save_errno = errno;
	ft_free_triptr(&cmd_argvs);
	free(cmd_path);
	if (save_errno == EACCES)
	{
		exit_code = 126;
		print_error(cmd_path, "Permission denied");
	}
	else if (save_errno == ENOENT)
	{
		exit_code = 127;
		print_error(cmd_path, "No such file or directory");
	}
	else
	{
		exit_code = 1;
		print_error(cmd_path, strerror(save_errno));
	}
	close_stack(pipex);
	exit(exit_code);
}
