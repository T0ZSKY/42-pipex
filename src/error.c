/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:32:47 by tomlimon          #+#    #+#             */
/*   Updated: 2024/12/11 14:33:26 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exit_with_error(char *message)
{
	perror(message);
	exit(1);
}

void	close_fds(t_pipex *pipex)
{
	close(pipex->infile_fd);
	close(pipex->outfile_fd);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}
