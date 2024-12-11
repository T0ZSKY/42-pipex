/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:08:43 by tomlimon          #+#    #+#             */
/*   Updated: 2024/12/11 02:12:16 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H


/*include*/

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

/*prototype*/


void exit_with_error(char *message);
void execute_cmd(char *cmd, char **envp, int *fd, int infile_fd, int outfile_fd, int is_child);
int create_pipe(int *fd);
int open_files(int argc, char **argv, int *infile_fd, int *outfile_fd);


#endif
