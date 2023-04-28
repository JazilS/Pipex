/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 09:11:29 by jsabound          #+#    #+#             */
/*   Updated: 2023/04/28 21:07:06 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	get_pipe(t_data *data)
{
	data->prev_fd = data->fd[0];
	if (data->i < data->nb_cmd - 1)
	{
		if (pipe(data->fd))
			return (perror("Pipe "));
	}
	else
		close(data->fd[1]);
	data->pid = fork();
	if (data->pid < 0)
	{
		perror("Fork ");
		return ;
	}
}

void	main_process(t_data *data)
{
	if (data->pipe->check)
	{
		ft_printf("%s: command not found\n", data->pipe->arg[0]);
		exit(EXIT_FAILURE);
	}
	if (data->i == 0)
		infile(data);
	else if (data->i == data->nb_cmd - 1)
		outfile(data);
	else
		cmd(data);
}
