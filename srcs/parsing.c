/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 03:51:35 by jsabound          #+#    #+#             */
/*   Updated: 2023/03/11 03:55:01 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	check_parsing(char **str)
{
	int	i;

	i = 0;
	while (++i < 5)
	{
		if (!str[i][0])
			return (i);
	}
	return (0);
}

char	**get_path(char **envp)
{
	int		i;
	char	**path;

	path = NULL;
	i = -1;
	if (!envp)
		return (NULL);
	while (envp[++i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T'
			&& envp[i][3] == 'H' && envp[i][4] == '=')
		{
			path = ft_split(envp[i] + 5, ':');
			return (path);
		}
	}
	return (path);
}

int	check_cmd(t_data *data, int cmd)
{
	int		i;
	char	*tmp;

	i = -1;
	if (!access(data->pipe->cmd, F_OK))
		return (1);
	while (data->path[++i])
	{
		tmp = ft_strjoin(data->path[i], data->pipe->cmd);
		if (!access(tmp, F_OK))
		{
			free(data->pipe->cmd);
			data->pipe->cmd = tmp;
			return (1);
		}
		free(tmp);
	}
	return (0);
}

int	check_file(char *file)
{
	int	fd;

	fd = open(file, __O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (-2);
	}
	return (access(file, R_OK));
}