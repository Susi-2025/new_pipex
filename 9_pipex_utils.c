/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_pipex_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:53:13 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/24 20:48:51 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_stack(t_pipex *pipex)
{
	if (pipex && pipex->fd_in != -1)
		close(pipex->fd_in);
	if (pipex && pipex->fd_out != -1)
		close(pipex->fd_out);
	if (pipex && pipex->pipefd[0])
		close(pipex->pipefd[0]);
	if (pipex && pipex->pipefd[1])
		close(pipex->pipefd[1]);
}

void	error(t_pipex *pipex, int no)
{
	close_stack(pipex);
	write(2, "Error\n", 6);
	exit(no);
}
