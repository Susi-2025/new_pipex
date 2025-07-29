/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_err_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 10:47:50 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/29 18:49:19 by vinguyen         ###   ########.fr       */
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
	exit(exit_code);
}

void	err_clean_exit(t_stack *pipex, char *msg, int exit_code)
{
	close_stack(pipex);
	err_exit(msg, exit_code);
}

void	err_cmd_clean_exit(t_stack *pipex, char *msg, int exit_code)
{
	close_stack(pipex);
	if (errno == EACCES)
		print_error(msg, "Permission denied");
	else if (errno == ENOENT)
		print_error(msg, "Command not found");
	else
		print_error(msg, strerror(errno));
	exit(exit_code);
}

void	print_error(char *str, char *msg)
{
	if (str)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
		ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}
