/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_run_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:21:11 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/26 22:03:34 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_command(t_pipex *pipex, char *command, char **envp)
{
	char	*path;
	char	**argv;
	char	*file;

	path = find_path_in_envp(pipex, envp);
	if (!path)
		error(pipex, "ENVP", 1);
	argv = make_argv_array(command);
}

static	char	*find_path_in_envp(t_pipex *pipex, char **envp)
{
	char	*temp;
	
	while (envp != NULL && *envp != NULL)
	{
		temp = ft_strchr(*envp, '=');
		if (temp == NULL)
			error(pipex, "ENVP", 1);
		if (ft_strncmp(*envp, "PATH", temp - *envp) == 0)
			return (temp + 1);
		envp++;
	}
	return (NULL);
}

static	char	**make_argv_array(t_pipex *pipex, char *command)
{
	char	**out;
	int		count_words;

	count_words = split_command(pipex, command);
	out = malloc((count_words + 1) *sizeof(char *));
	if (out)
	{
		free
}
