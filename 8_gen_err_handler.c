/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_gen_err_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 10:47:50 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/30 15:54:57 by vinguyen         ###   ########.fr       */
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

void	err_clean_exit(t_stack *pipex, char *msg, int exit_code)
{
	close_stack(pipex);
	err_exit(msg, exit_code);
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
}

void	err_open_file(t_stack *pipex, char *av, int exit_code)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(av, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	close_stack(pipex);
	exit(exit_code);
}
