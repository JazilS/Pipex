/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 03:51:35 by jsabound          #+#    #+#             */
/*   Updated: 2023/04/27 20:59:02 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

int	check_cmd(t_data *data, t_pipe *pipe)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	if (!pipe->arg[0])
	{
		pipe->arg[0] = "' '";
		return (1);
	}
	if (pipe->arg[0][0] == '/')
	{
		pipe->path = pipe->arg[0];
		return (0);
	}
	i = -1;
	tmp2 = ft_strjoin("/", pipe->arg[0]);
	while (data->path_start[++i])
	{
		tmp = ft_strjoin(data->path_start[i], tmp2);
		if (!access(tmp, F_OK))
		{
			free(pipe->path);
			pipe->path = tmp;
			return (0);
		}
		free(tmp);
	}
	free(tmp2);
	return (1);
}
