/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:08:43 by tomlimon          #+#    #+#             */
/*   Updated: 2024/12/11 14:32:34 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*include*/

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

/*struct*/

typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;
	int		fd[2];
	char	**envp;
}	t_pipex;

/*prototype*/

int		open_files(int argc, char **argv, t_pipex *pipex);
int		create_pipe(int *fd);
void	close_fds(t_pipex *pipex);
void	dup_fds(t_pipex *pipex, int is_child);
void	ft_cmd(char *cmd, t_pipex *pipex, int is_child);
void	exit_with_error(char *message);

#endif
