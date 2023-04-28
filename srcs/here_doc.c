/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 19:05:16 by jsabound          #+#    #+#             */
/*   Updated: 2023/04/28 19:08:09 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	here_doc(t_data *data)
{
	char	*buff;
	int		fd;

	data->limiter = data->av[2];
	fd = open(".here_doc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (1);
	buff = malloc(sizeof(ft_strlen(data->limiter + 1)));
	if (!buff)
		return (1);
	while (data->temp >= 0)
	{
		data->temp = read(0, buff, ft_strlen(data->limiter));
		buff[data->temp] = '\0';
		if (!ft_strncmp(buff, data->limiter, ft_strlen(data->limiter) + 1))
		{
			free(buff);
			return (0);
		}
		else
			write(fd, buff, data->temp);
	}
	free(buff);
	close(fd);
	return (0);
}
