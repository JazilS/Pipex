/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 09:25:17 by jsabound          #+#    #+#             */
/*   Updated: 2023/04/28 19:20:28 by jsabound         ###   ########.fr       */
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
	char			*path;
	int				check;
	struct s_pipe	*next;
}					t_pipe;

typedef struct s_data
{
	int				fd[2];
	int				prev_fd;
	int				nb;
	int				i;
	int				ac;
	char			**av;
	int				end;
	char			**path_start;
	int				start;
	int				f1;
	int				f2;
	int				here_doc;
	char			*limiter;
	int				nb_cmd;
	int				temp;
	pid_t			pid;
	struct s_pipe	*pipe;

}					t_data;

void				pipex(t_data *data, char **envp);
int					check_cmd(t_data *data, t_pipe *pipe);
char				**get_path(char **envp);
void				infile(t_data *data);
void				cmd(t_data *data);
void				pipex(t_data *data, char **envp);
void				outfile(t_data *data);
void				free_char(char **temp);
void				ft_free(t_data *data);
void				free_pipe(t_pipe *pipe);
void				get_pipe(t_data *data);
int					here_doc(t_data *data);
void				main_process(t_data *data);
int					check_cmd2(t_data *data, char *tmp2, t_pipe *pipe);
void				init(t_data *data, int j);

#endif