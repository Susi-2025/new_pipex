/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_pipex_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:53:13 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/25 20:40:14 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_stack(t_pipex *pipex)
{
	if (pipex && pipex->fd_in != -1)
		close(pipex->fd_in);
	if (pipex && pipex->fd_out != -1)
		close(pipex->fd_out);
	if (pipex && pipex->pipe_fd[0])
		close(pipex->pipe_fd[0]);
	if (pipex && pipex->pipe_fd[1])
		close(pipex->pipe_fd[1]);
	if (pipex && pipex->p_id1)
		close(pipex->p_id1);
	if (pipex && pipex->p_id2)
		close(pipex->p_id2);
}

void	error(t_pipex *pipex, char *str, int no)
{
	close_stack(pipex);
	perror(str);
	exit(no);
}

void	free_error(t_pipex *pipex, char *str, int no, char **arr)
{
	ft_free_triptr(&arr);
	error(pipex, str, no);
}
