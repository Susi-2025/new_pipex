/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_cmd_err_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 10:47:50 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/31 13:04:38 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "stdio.h"

void	handle_no_file(t_stack *pipex, char **cmd_argvs)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd_argvs[0], 2);
	ft_putstr_fd(":No such file or directory\n", 2);
	ft_free_triptr(&cmd_argvs);
	close_stack(pipex);
	exit(127);
}

void	handle_command_error(t_stack *pipex, int exit_code)
{
	ft_putstr_fd(" ", 2);
	ft_putstr_fd(":", 2);
	ft_putstr_fd(" command not found\n", 2);
	close_stack(pipex);
	exit(exit_code);
}

void	handle_cmd_path_err(t_stack *pipex, char *msg, int exit_code)
{
	int	temp_errno;

	temp_errno = errno;
	close_stack(pipex);
	if (temp_errno == EACCES)
		print_error(msg, "Permission denied");
	else if (temp_errno == ENOENT)
		print_error(msg, "command not found");
	else
		print_error(msg, strerror(temp_errno));
	ft_putstr_fd("\n", 2);
	exit(exit_code);
}

void	handle_exec_error(t_stack *pipex, char *cmd_path, char **cmd_argvs)
{
	int	exit_code;
	int	save_errno;

	save_errno = errno;
	ft_free_triptr(&cmd_argvs);
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
	free(cmd_path);
	close_stack(pipex);
	exit(exit_code);
}
