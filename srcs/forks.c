/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 19:06:01 by jsabound          #+#    #+#             */
/*   Updated: 2023/05/04 00:17:12 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	infile(t_data *data)
{
	close(data->fd[0]);
	if (dup2(data->f1, STDIN_FILENO) == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

void	cmd(t_data *data)
{
	close(data->fd[0]);
	if (dup2(data->prev_fd, STDIN_FILENO) == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

void	outfile(t_data *data)
{
	close(data->fd[1]);
	check_f2(data);
	if (dup2(data->fd[0], STDIN_FILENO) == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	if (dup2(data->f2, STDOUT_FILENO) == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}
