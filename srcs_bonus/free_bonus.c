/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:39:18 by jsabound          #+#    #+#             */
/*   Updated: 2023/05/04 00:17:29 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	free_pipe(t_data *data)
{
	t_pipe	*temp;

	if (data && data->pipe->arg)
		free_char(data->pipe->arg);
	if (data && data->pipe->path)
		free(data->pipe->path);
	temp = data->pipe->next;
	if (data && data->pipe)
		free(data->pipe);
	data->pipe = temp;
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
}
