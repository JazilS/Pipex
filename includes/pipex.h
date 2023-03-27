/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 09:25:17 by jsabound          #+#    #+#             */
/*   Updated: 2023/03/27 23:34:40 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include "unistd.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipe
{
	char			**arg;
	char			*cmd;
	int				pip;
	struct s_pipe	*next;
}					t_pipe;

typedef struct s_data
{
	int				fd[2];
	int				prev_fd;
	int				nb;
	int				end;
	char			**path;
	int				start;
	int				f1;
	int				f2;
	char			*outfile;
	struct s_pipe	*pipe;
}					t_data;

void				pipex(t_data *data, char **envp, int ac);

#endif