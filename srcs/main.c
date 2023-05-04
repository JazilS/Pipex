/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 09:11:27 by jsabound          #+#    #+#             */
/*   Updated: 2023/05/05 00:21:55 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	pipex(t_data *data, char **envp)
{
	int	status;

	data->i = -1;
	while (++data->i < data->nb_cmd)
	{
		dprintf(1, "check = %d\n", data->pipe->check);
		get_pipe(data);
		if (data->pid == 0)
		{
			main_process(data);
			if (execve(data->pipe->path, data->pipe->arg, envp) < 0)
			{
				perror(data->pipe->path);
				exit(EXIT_FAILURE);
			}
		}
		close(data->fd[1]);
		close(data->prev_fd);
		free_pipe(data);
	}
	while (--data->i >= 0)
		wait(&status);
}

void	init(t_data *data, int j)
{
	t_pipe	*temp;
	int		i;

	i = 0;
	temp = malloc(sizeof(t_pipe));
	if (!temp)
		return ;
	data->pipe = temp;
	while (i++ < data->nb_cmd)
	{
		temp->path = NULL;
		temp->arg = ft_split(data->av[j], ' ');
		temp->check = check_cmd(data, temp);
		if (i == data->nb_cmd)
			temp->next = NULL;
		else
		{
			temp->next = malloc(sizeof(t_pipe));
			if (!temp->next)
				return ;
			temp = temp->next;
		}
		j++;
	}
	data->free_pipe = temp;
}

void	init_data(t_data *data, char **av, int ac, char **envp)
{
	data->ac = ac;
	data->av = av;
	data->nb_cmd = data->ac - 3;
	data->fd[0] = -1;
	data->f1 = open(data->av[1], O_RDWR);
	if (data->f1 == -1)
	{
		if (!access(av[1], F_OK))
		{
			perror(data->av[1]);
			exit(EXIT_FAILURE);
		}
		perror(data->av[1]);
		exit(EXIT_FAILURE);
	}
	data->path_start = get_path(envp);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	int		j;

	if (ac == 5)
	{
		init_data(&data, av, ac, envp);
		j = 2;
		init(&data, j);
		pipex(&data, envp);
		ft_free(&data);
	}
	else
		ft_printf("Invalid Argument\n");
	return (0);
}
