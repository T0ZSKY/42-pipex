/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:08:19 by tomlimon          #+#    #+#             */
/*   Updated: 2024/12/11 14:34:45 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	open_files(int argc, char **argv, t_pipex *pipex)
{
	if (argc != 5)
	{
		perror("Error arguments : ./pipex file1 cmd1 cmd2 file2\n");
		return (-1);
	}
	pipex->infile_fd = open(argv[1], O_RDONLY);
	if (pipex->infile_fd == -1)
	{
		perror("Error with file1 \n");
		return (-1);
	}
	pipex->outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile_fd == -1)
	{
		perror("Error with file2\n");
		close(pipex->infile_fd);
		return (-1);
	}
	return (0);
}

int	create_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("Error pipe\n");
		return (-1);
	}
	return (0);
}

void	dup_fds(t_pipex *pipex, int is_child)
{
	if (is_child)
	{
		if (dup2(pipex->infile_fd, STDIN_FILENO) == -1)
			exit_with_error("Error dup2 infile");
		if (dup2(pipex->fd[1], STDOUT_FILENO) == -1)
			exit_with_error("Error dup2 pipe write");
	}
	else
	{
		if (dup2(pipex->fd[0], STDIN_FILENO) == -1)
			exit_with_error("Error dup2 pipe read");
		if (dup2(pipex->outfile_fd, STDOUT_FILENO) == -1)
			exit_with_error("Error dup2 outfile");
	}
}

void	ft_cmd(char *cmd, t_pipex *pipex, int is_child)
{
	dup_fds(pipex, is_child);
	close_fds(pipex);
	if (execve("/bin/sh", (char *[]){"/bin/sh", "-c", cmd,
			NULL}, pipex->envp) == -1)
		exit_with_error("Error execve cmd");
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	t_pipex	pipex;

	pipex.envp = envp;
	if (open_files(argc, argv, &pipex) == -1)
		return (-1);
	if (create_pipe(pipex.fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		perror("Error fork\n");
		return (-1);
	}
	else if (pid == 0)
	{
		ft_cmd(argv[2], &pipex, 1);
	}
	else
	{
		ft_cmd(argv[3], &pipex, 0);
	}
	return (0);
}
