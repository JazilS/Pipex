/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 09:11:27 by jsabound          #+#    #+#             */
/*   Updated: 2023/03/02 15:49:33 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void end(int *fdpipe, char *outfile, char **av, int i, char **envp)
{
	pid_t pid2;
	int fd;
	
	pid2 = fork();
	if(pid2 == 0)
	{
		close(fdpipe[1]);
		fd = open(outfile, O_WRONLY);
		if (fd == -1)
			dprintf(1, "test\n");
		if (dup2(fdpipe[0], STDIN_FILENO) == -1)
			dprintf(1, "test\n");
		if (dup2(fd, STDOUT_FILENO) == -1)
			dprintf(1, "test\n");
		execve(get_path(av[i]), get_cmd(av[i]), envp);
	}	
	waitpid(pid2, NULL, 0);
}
void pipex(char **av, char **envp, int i, char *infile)
{
	int fdpipe[2];
	pid_t pid;
	int fd;

	if (pipe(fdpipe) == -1)
			dprintf(1, "test\n");
	pid = fork();
	if (pid == 0)
	{
		close(fdpipe[0]);
		fd = open(infile, O_RDONLY);
		if (fd == -1)
			dprintf(1, "test\n");
		if (dup2(fd, STDIN_FILENO) == -1)
			dprintf(1, "test\n");
		if (dup2(fdpipe[1], STDOUT_FILENO) == -1)
			dprintf(1, "test\n");
		execve(get_path(av[i]), get_cmd(av[i]), envp);
	}
	close(fdpipe[0]);
	close(fdpipe[1]);
	waitpid(pid, NULL, 0);
}

char **get_cmd(char *av)
{
	char **cmd;

	cmd = ft_split(av, ' ');
	return (cmd);
}

char *get_path(char *av)
{
	char *path;

	path = ft_strjoin("/usr/bin/", *get_cmd(av));
	printf("path = %s\n", path);
	return (path);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	int i = 0;

	while (i < ac -3)
	{
		printf("%d\n", i);
		pipex(av, envp, i, av[1]);
		i++;
	}
	return (0);
}