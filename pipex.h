/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:27:14 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/26 21:30:04 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>  // for open
# include <unistd.h> // for dup2, pipe, fork, execve
# include <stdlib.h> // for exit
# include <sys/wait.h> // for pid_t
# include <errno.h>
# include <stdio.h>

# include "./libft/libft.h"

typedef struct s_pipex
{
	int		pipes[2];
	pid_t	pid[2];
	int		fd[2];
}	t_pipex;

void	first_process(t_pipex *pipex, char **av, char **envp);
void	second_process(t_pipex *pipex, char **av, char **envp);
void	execute(t_pipex *pipex, char **av, char **envp, int in_out);
void	close_stack(t_pipex *pipex);
void	error(t_pipex *pipex, char *str, int no);
void	free_error(t_pipex *pipex, char *str, int no, char **arr);

#endif
