/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 09:11:27 by jsabound          #+#    #+#             */
/*   Updated: 2023/04/03 15:34:24 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void infile (t_data *data)
{
	close(data->fd[0]);
	data->f1 = open(data->inf, O_RDWR);
	if (data->f1 == -1)
		return ;
	if (dup2(data->f1, STDIN_FILENO) == -1);
		exit(-1);
	if (dup2(data->fd[1], STDOUT_FILENO) == -1);
		exit(-1);
	data->infile++;
}

void outfile (t_data *data)
{
	close(data->fd[1]);
	data->f2 = open(data->outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->f2 == -1)
		perror("Outfile ");
	if (dup2(data->fd[0], STDIN_FILENO) == -1);
		exit(-1);
	if (dup2(data->f2, STDOUT_FILENO) == -1);
		exit(-1);
	data->infile++;
}

void cmd (t_data *data)
{
	close(data->fd[0]);
	if (dup2(data->prev_fd, STDIN_FILENO) == -1);
		exit(-1);
	if (dup2(data->fd[1], STDOUT_FILENO) == -1);
		exit(-1);
}

void	pipex(t_data *data, char **envp, int ac)
{
	int		i;
	int		status;
	pid_t	pid;

	i = -1;
	while (++i < ac - 3)
	{
		if (pipe(data->fd) && i < ac - 4)
			exit(1);
		data->prev_fd = data->fd[0];
		pid = fork();
		if (pid < 0)
			perror("Fork ");
		if (pid == 0)
		{
			if (data->infile == 0)
				infile(data);
			if (data->cmd != 1)
				cmd(data);
			if (data->out == 1)
				outfile(data);
			if (execve(data->pipe->cmd, data->pipe->arg, envp) < 0)
				exit(3);
		}
		close(data->fd[1]);
		close(data->prev_fd);
		data->pipe = data->pipe->next;
	}
	while (--i >= 0)
		wait(&status);
}

void	init(int ac, char **av, t_data *data)
{
	t_pipe	*pipe;
	int		i;
	int j = 2;
	
	i = 0;
	pipe = malloc(sizeof(pipe));
	if (!pipe)
		return ;
	data->fd[0] = -1;
	data->infile = 0;
	data->inf = av[1];
	data->outfile = av[ac];
	data->pipe = pipe;
	while (i++ < ac - 3)
	{
		pipe->arg = ft_split(av[j], ' ');
		pipe->cmd = pipe->arg[0];
		if (i == ac - 1)
			pipe->next = NULL;
		else
		{
			pipe->next = malloc(sizeof(t_pipe));
			if (!pipe->next)
				return ;
			pipe = pipe->next;
		}
		j++;
	}
}
int	main(int ac, char **av, char **envp)
{
	t_data data;

	init(ac, av, &data);
	pipex(&data, envp, ac);
	return (0);
}