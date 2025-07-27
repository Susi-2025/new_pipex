/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_err_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 10:47:50 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/27 13:56:22 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	err_msg(char *str, int exit_code)
{
	ft_putstr_fd(str, 2);
	exit(exit_code);
}

void	err_exit(char *msg, int exit_code)
{
	perror(msg);
	exit(exit_code);
}

void	err_clean_exit(t_stack *pipex, char *filename, int exit_code)
{
	free_stack(pipex);
	err_exit(filename, exit_code);
}
