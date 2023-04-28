/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 09:11:29 by jsabound          #+#    #+#             */
/*   Updated: 2023/04/28 18:52:49 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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