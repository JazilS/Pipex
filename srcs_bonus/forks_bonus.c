/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 19:06:01 by jsabound          #+#    #+#             */
/*   Updated: 2023/04/30 19:39:02 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	infile(t_data *data)
{
	close(data->fd[0]);
	if (data->here_doc)
		data->f1 = open(".here_doc_tmp", O_RDWR);
	else
		data->f1 = open(data->av[1], O_RDWR);
	if (data->f1 == -1)
	{
		close(data->fd[1]);
		perror(data->av[1]);
		exit(EXIT_FAILURE);
	}
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
	data->f2 = open(data->av[data->ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->f2 == -1)
	{
		close(data->fd[0]);
		perror(data->av[data->ac - 1]);
		exit(EXIT_FAILURE);
	}
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
