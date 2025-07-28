/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_pipex_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:53:13 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/28 21:11:50 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_stack(t_stack *pipex)
{
	if (!pipex)
		return ;
	if (pipex->pipefd[0] >= 0)
		close(pipex->pipefd[0]);
	if (pipex->pipefd[1] >= 0)
		close(pipex->pipefd[1]);
	if (pipex->fd[0] >= 0)
		close(pipex->fd[0]);
	if (pipex->fd[1] >= 0)
		close(pipex->fd[1]);
}

void	free_stack(t_stack *pipex)
{
	close_stack(pipex);
}
