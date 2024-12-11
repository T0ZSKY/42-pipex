/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:08:19 by tomlimon          #+#    #+#             */
/*   Updated: 2024/12/11 02:10:58 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int open_files(int argc, char **argv, int *infile_fd, int *outfile_fd)
{
    if (argc != 5)
    {
        perror("Error arguments : ./pipex file1 cmd1 cmd2 file2\n");
        return (-1);
    }
    *infile_fd = open(argv[1], O_RDONLY);
    if (*infile_fd == -1)
    {
        perror("Error with file1 \n");
        return (-1);
    }
    *outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (*outfile_fd == -1)
    {
        perror("Error with file2\n");
        close(*infile_fd);
        return (-1);
    }
    return (0);
}

int create_pipe(int *fd)
{
    if (pipe(fd) == -1)
    {
        perror("Error pipe\n");
        return (-1);
    }
    return (0);
}

void execute_cmd(char *cmd, char **envp, int *fd, int infile_fd, int outfile_fd, int is_child)
{
    if (is_child)
    {
        close(fd[0]);
        if (dup2(infile_fd, STDIN_FILENO) == -1)
            exit_with_error("Error dup2 infile");
        if (dup2(fd[1], STDOUT_FILENO) == -1)
            exit_with_error("Error dup2 pipe write");
    }
    else
    {
        close(fd[1]);
        if (dup2(fd[0], STDIN_FILENO) == -1)
            exit_with_error("Error dup2 pipe read");
        if (dup2(outfile_fd, STDOUT_FILENO) == -1)
            exit_with_error("Error dup2 outfile");
    }
    close(infile_fd);
    close(outfile_fd);
    close(fd[0]);
    close(fd[1]);
    if (execve("/bin/sh", (char *[]) {"/bin/sh", "-c", cmd, NULL}, envp) == -1)
        exit_with_error("Error execve cmd");
}

void exit_with_error(char *message)
{
    perror(message);
    exit(1);
}

int main(int argc, char **argv, char **envp)
{
    pid_t pid;
    int fd[2];
    int infile_fd;
    int outfile_fd;

    if (open_files(argc, argv, &infile_fd, &outfile_fd) == -1)
        return (-1);
    if (create_pipe(fd) == -1)
        return (-1);
    pid = fork();
    if (pid == -1)
    {
        perror("Error fork\n");
        return (-1);
    }
    else if (pid == 0)
    {
        execute_cmd(argv[2], envp, fd, infile_fd, outfile_fd, 1);
    }
    else
    {
        execute_cmd(argv[3], envp, fd, infile_fd, outfile_fd, 0);
    }
    return (0);
}
