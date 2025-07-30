/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_pipex_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:53:13 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/30 16:04:33 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_stack(t_stack *pipex)
{
	if (!pipex)
		return ;
	if (pipex->pipefd[0] >= 0 && pipex->pipefd[0] != 2)
		close(pipex->pipefd[0]);
	if (pipex->pipefd[1] >= 0 && pipex->pipefd[1] != 2)
		close(pipex->pipefd[1]);
	if (pipex->fd[0] >= 0 && pipex->fd[0] != 2)
		close(pipex->fd[0]);
	if (pipex->fd[1] >= 0 && pipex->fd[1] != 2)
		close(pipex->fd[1]);
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
