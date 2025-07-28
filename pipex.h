/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:27:14 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/28 15:25:32 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h> 
# include <sys/wait.h>

# include "./libft/libft.h"

typedef struct s_stack
{
	int		pipefd[2];
	pid_t	pid[2];
	int		fd[2];
}	t_stack;

void	first_child_run(t_stack *pipex, char **av, char **envp);
void	second_child_run(t_stack *pipex, char **av, char **envp);
void	run_command(t_stack *pipex, char *command, char **envp);
char	*get_path(char **envp, char *cmd);

void	err_msg(char *str, int err);
void	err_exit(char *msg, int exit_code);
void	err_clean_exit(t_stack *pipex, char *filename, int exit_code);

void	close_stack(t_stack *pipex);
void	free_stack(t_stack *pipex);

#endif
