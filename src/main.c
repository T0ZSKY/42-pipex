/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:08:19 by tomlimon          #+#    #+#             */
/*   Updated: 2024/12/10 15:25:11 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv)
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
		return (-1);
	}
	if (pipe(fd) == -1)
	{
		perror("Error pipe\n");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error fork\n");
	}
	else if (pid == 0)
	{
		close(fd[0]);
		printf("Je suis enfant\n");
		
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		printf("Je suis le parent\n");

		close(fd[0]);
	}
	close(infile_fd);
	close(outfile_fd);
}