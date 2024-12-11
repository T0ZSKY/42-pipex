/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:08:19 by tomlimon          #+#    #+#             */
/*   Updated: 2024/12/11 01:46:19 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	pid_t pid;
	int fd[2];
	int infile_fd;
	int outfile_fd;

	if (argc != 5)
	{
		perror("Error arguments : ./pipex file1 cmd1 cmd2 file2\n");
		return (-1);
	}
	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd == -1)
	{
		perror("Error with file1 \n");
		return (-1);
	}
	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
	{
		perror("Error with file2\n");
		close(infile_fd);
		return (-1);
	}
	if (pipe(fd) == -1)
	{
		perror("Error pipe\n");
		close(infile_fd);
		close(outfile_fd);
		return (-1);
	}
	pid = fork();
	if (pid == -1)
		perror("Error fork\n");
	else if (pid == 0)
	{
		// Processus enfant : cmd1
		close(fd[0]);
		if (dup2(infile_fd, STDIN_FILENO) == -1)
		{
			perror("Error dup2 infile");
			exit(1);
		}
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("Error dup2 pipe write");
			exit(1);
		}
		close(infile_fd);
		close(fd[1]);
		close(outfile_fd);
		if (execve("/bin/sh", (char *[]) {"/bin/sh", "-c", argv[2], NULL}, envp) == -1)
		{
			perror("Error execve cmd1");
			exit(1);
		}
	}
	else
	{
		// Processus parent : cmd2
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			perror("Error dup2 pipe read");
			exit(1);
		}
		if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		{
			perror("Error dup2 outfile");
			exit(1);
		}
		close(outfile_fd);
		close(fd[0]);
		close(infile_fd);
		if (execve("/bin/sh", (char *[]) {"/bin/sh", "-c", argv[3], NULL}, envp) == -1)
		{
			perror("Error execve cmd2");
			exit(1);
		}
	}
	close(infile_fd);
	close(outfile_fd);
	return (0);
}
