/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 09:11:27 by jsabound          #+#    #+#             */
/*   Updated: 2023/03/27 23:49:07 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// int error()
// {
// 	if ()
// }

void print_tab(char **str)
{
	int i =0;

	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

int	check_f2(t_data *data)
{
	data->f2 = open(data->outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->f2 == -1)
	{
		perror("Outfile ");
		return (1);
	}
	return (0);
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
	data->f1 = open(av[1], O_RDONLY);
	if (data->f1 == -1)
		return ;
	data->fd[0] = -1;
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

void	pipex(t_data *data, char **envp, int ac)
{
	int		i;
	int		status;
	pid_t	pid;

	i = -1;
	while (++i < ac - 3)
	{
		if (data->pipe->next)
		{
			if (pipe(data->fd))
				exit(1);
			data->prev_fd = data->fd[0];
			printf("prev_fd = %d\n", data->prev_fd);
			printf("fd[1] = %d\n", data->fd[1]);
			data->pipe->pip = 1;
		}
		pid = fork();
		if (pid < 0)
			exit(1);
		else
		{
			if (data->prev_fd != -1)
				dup2(data->prev_fd, 0);
			if (data->pipe->pip == 1)
				dup2(data->fd[1], 1);
			if (execve(data->pipe->cmd, data->pipe->arg, envp) < 0)
				exit(3);
		}
		close(data->fd[1]);
		data->pipe = data->pipe->next;
	}
	while (--i >= 0)
		wait(&status);
}

int	main(int ac, char **av, char **envp)
{
	t_data data;

	init(ac, av, &data);
	pipex(&data, envp, ac);
	return (0);
}