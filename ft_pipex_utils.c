/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrivas- <anrivas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:22:38 by anrivas-          #+#    #+#             */
/*   Updated: 2023/10/16 13:14:14 by anrivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **args)
{
	int	cont;

	cont = 0;
	while (args[cont])
	{
		free(args[cont]);
		cont++;
	}
	free(args);
}

char	*get_command(char **path, char *token)
{
	int		cont;
	char	*path_complete;

	cont = 0;
	token = ft_strjoin("/", token);
	while (path[cont])
	{
		path_complete = ft_strjoin(path[cont], token);
		if (access(path_complete, F_OK) == 0)
		{
			return (path_complete);
		}
		free(path_complete);
		cont++;
	}
	return (NULL);
}

char	**ft_find_path(char **env)
{
	int		cont;
	char	*path_env;
	char	**path;

	cont = 0;
	path = NULL;
	path_env = NULL;
	while (env[cont])
	{
		if (ft_strncmp(env[cont], "PATH=", 5) == 0)
		{
			path_env = env[cont] + 5;
			break ;
		}
		cont++;
	}
	if (path_env)
		path = ft_split(path_env, ':');
	if (!path)
		return (NULL);
	return (path);
}
