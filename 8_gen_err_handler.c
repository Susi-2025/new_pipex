/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_gen_err_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 10:47:50 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/30 17:08:02 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "stdio.h"

void	err_exit(char *msg, int exit_code)
{
	if (errno == EACCES)
		print_error(msg, "Permission denied");
	else if (errno == ENOENT)
		print_error(msg, "No such file or directory");
	else
		print_error(msg, strerror(errno));
	ft_putstr_fd("\n", 2);
	exit(exit_code);
}

void	err_fork_dup2(t_stack *pipex, char *msg, int exit_code)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	close_stack(pipex);
	exit(exit_code);
}

void	err_open_file(t_stack *pipex, char *av, int exit_code)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(av, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	close_stack(pipex);
	exit(exit_code);
}

void	handle_envp_error(t_stack *pipex, char **cmd_argvs, int exit_code)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd_argvs[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	ft_free_triptr(&cmd_argvs);
	close_stack(pipex);
	exit(exit_code);
}
