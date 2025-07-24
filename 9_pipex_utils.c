/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_pipex_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:53:13 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/24 12:41:08 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_stack(t_stack *pipex)
{
	if (pipex && pipex->av)
		free_triptr(&pipex->av);
	if (pipex && pipex->envp)
		free_triptr(&pipex->envp);
}

void	error(t_stack *pipex, int no)
{
	free_stack(pipex);
	write(2, "Error\n", 6);
	exit(no);
}
