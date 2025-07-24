/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:27:14 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/24 20:18:08 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>  // for open
# include <unistd.h> // for dup2, pipe, fork, execve
# include <stdlib.h> // for exit
# include <sys/types.h> // for pid_t
# include <limits.h>
# include <stdio.h>

# include "./libft/libft.h"

typedef struct s_pipex
{
	int	pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		fd_in;
	int		fd_out;
}	t_pipex;

void	first_process(t_pipex *pipex, char **av, char **envp);
void	second_process(t_pipex *pipex, char **av, char **envp);

#endif
