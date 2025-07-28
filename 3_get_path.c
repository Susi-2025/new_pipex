/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_get_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:21:11 by vinguyen          #+#    #+#             */
/*   Updated: 2025/07/28 13:09:43 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	char	*find_path_envp(char **envp);
static	char	*check_execution(char **path_parts, char *cmd);

char	*get_path(char **envp, char *cmd)
{
	char	*out;
	char	*path_envp;
	char	**path_parts;

	path_envp = find_path_envp(envp);
	if (!path_envp)
		return (NULL);
	path_parts = ft_split(path_envp, ':');
	free(path_envp);
	if (!path_parts)
		return (NULL);
	out = check_execution(path_parts, cmd);
	ft_free_triptr(&path_parts);
	return (out);
}

static	char	*find_path_envp(char **envp)
{
	char	*out;
	int		i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
		{
			out = ft_strdup(envp[i] + 5);
			if (out && out[0] == '\0')
			{
				free(out);
				return (NULL);
			}
			return (out);
		}
		i++;
	}
	return (NULL);
}

static	char	*check_execution(char **path_parts, char *cmd)
{
	int		i;
	char	*temp_path;
	char	*out_path;

	i = 0;
	if (!cmd)
		return (NULL);
	while (path_parts[i])
	{
		temp_path = ft_strjoin(path_parts[i], "/");
		if (!temp_path)
			return (NULL);
		out_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (!out_path)
			return (NULL);
		if (access(out_path, X_OK) == 0)
			return (out_path);
		free(out_path);
		i++;
	}
	return (NULL);
}
