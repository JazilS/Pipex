/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:39:18 by jsabound          #+#    #+#             */
/*   Updated: 2023/04/28 21:07:24 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_pipe(t_pipe *pipe)
{
	t_pipe	*temp;

	temp = pipe;
	while (pipe)
	{
		temp = pipe->next;
		if (pipe->arg)
			free_char(pipe->arg);
		if (pipe->path)
			free(pipe->path);
		free(pipe);
		pipe = temp;
	}
}

void	free_char(char **temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		if (temp[i])
			free(temp[i]);
		i++;
	}
	if (temp)
		free(temp);
}

void	ft_free(t_data *data)
{
	if (data && data->path_start)
		free_char(data->path_start);
	if (data && data->pipe)
		free_pipe(data->pipe);
}
