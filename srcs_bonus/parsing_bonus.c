/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 03:51:35 by jsabound          #+#    #+#             */
/*   Updated: 2023/05/04 00:16:55 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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
	tmp2 = ft_strjoin("/", pipe->arg[0]);
	if (!check_cmd2(data, tmp2, pipe))
	{
		free(tmp2);
		return (0);
	}
	free(tmp2);
	return (1);
}

int	check_cmd2(t_data *data, char *tmp2, t_pipe *pipe)
{
	int		i;
	char	*tmp;

	i = -1;
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
	return (1);
}

void	check_f2(t_data *data)
{
	data->f2 = open(data->av[data->ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->f2 == -1)
	{
		close(data->fd[0]);
		perror(data->av[data->ac - 1]);
		exit(EXIT_FAILURE);
	}
}

void	check_f1(t_data *data)
{
	if (data->here_doc)
		data->f1 = open(".here_doc_tmp", O_RDWR);
	else
		data->f1 = open(data->av[1], O_RDWR);
	if (data->f1 == -1)
	{
		close(data->fd[1]);
		ft_free(data);
		free_pipe(data);
		perror(data->av[1]);
		exit(EXIT_FAILURE);
	}
}
