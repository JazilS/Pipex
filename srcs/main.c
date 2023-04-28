/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 09:11:27 by jsabound          #+#    #+#             */
/*   Updated: 2023/04/28 18:52:56 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

void	pipex(t_data *data, char **envp)
{
	int		status;
	pid_t	pid;

	data->i = -1;
	while (++data->i < data->nb_cmd)
	{
		data->prev_fd = data->fd[0];
		if (data->i < data->nb_cmd - 1)
		{
			if (pipe(data->fd))
				return (perror("Pipe "));
		}
		else
			close(data->fd[1]);
		pid = fork();
		if (pid < 0)
		{
			perror("Fork ");
			return ;
		}
		if (pid == 0)
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
			if (execve(data->pipe->path, data->pipe->arg, envp) < 0)
			{
				perror(data->pipe->path);
				exit(EXIT_FAILURE);
			}
		}
		close(data->fd[1]);
		close(data->prev_fd);
		data->pipe = data->pipe->next;
	}
	while (--data->i >= 0)
		wait(&status);
}

void	init(t_data *data, char **envp)
{
	t_pipe	*temp;
	int		i;
	int		j;

	j = 2 + data->here_doc;
	i = 0;
	temp = malloc(sizeof(t_pipe));
	if (!temp)
		return ;
	data->pipe = temp;
	data->fd[0] = -1;
	data->path_start = get_path(envp);
	data->nb_cmd = data->ac - 3 - data->here_doc;
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
}

int	here_doc(t_data *data)
{
	char	*buff;
	int		fd;
	int		temp;

	data->here_doc = 1;
	data->limiter = data->av[2];
	temp = 1;
	fd = open(".here_doc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (1);
	buff = malloc(sizeof(ft_strlen(data->limiter + 1)));
	if (!buff)
		return (1);
	while (temp >= 0)
	{
		temp = read(0, buff, ft_strlen(data->limiter));
		buff[temp] = '\0';
		if (!ft_strncmp(buff, data->limiter, ft_strlen(data->limiter) + 1))
		{
			free(buff);
			return (0);
		}
		else
			write(fd, buff, temp);
	}
	free(buff);
	close(fd);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_data data;

	data.ac = ac;
	data.av = av;
	if (!ft_strncmp("here_doc", av[1], 9))
	{
		data.here_doc = 1;
		here_doc(&data);
	}
	else
		data.here_doc = 0;
	init(&data, envp);
	pipex(&data, envp);
	unlink(".here_doc_tmp");
	ft_free(&data);
	return (0);
}