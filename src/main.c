/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:08:19 by tomlimon          #+#    #+#             */
/*   Updated: 2024/12/10 14:28:03 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv)
{
	pid_t pid;
	int fd[2];

	if (argc != 5)
	{
		perror("Error arguments : ./pipex file1 cmd1 cmd2 file2\n");
		exit(-1);
	}
	if (pipe(fd) == -1)
	{
		perror("Error pipe\n");
		exit(1);
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
		//ecrit dans le output
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		printf("Je suis le parent\n");
		//lit le fichier et execute la commande
		close(fd[0]);
	}
	
}