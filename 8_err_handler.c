/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_err_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 10:47:50 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/28 18:41:28 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "stdio.h"

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

void	err_clean_exit_2(t_stack *pipex, int exit_code)
{
	free_stack(pipex);
	exit(exit_code);
}
