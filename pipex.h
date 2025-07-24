/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:27:14 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/24 14:58:45 by vinguyen         ###   ########.fr       */
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

typedef struct s_stack
{
	int	ac;
	char	**av;
	char	**envp;

}	t_stack;

#endif
