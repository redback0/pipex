/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:20:53 by njackson          #+#    #+#             */
/*   Updated: 2024/05/09 17:14:26 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <fcntl.h>
# include "libft.h"

# define USAGE "USAGE: ./pipex [here_doc] {INFILE CMD [CMDS...] CMD OUTFILE}\n"
# define HERE_DOC_ERR "\nwarning: here-document delimited by end-of-file \
(wanted `%s`)\n"

char	**get_path(char **ep);
int		run_command(char *cmd, int infd, char **path);
char	*find_command(char *cmd, char **path);
void	output_to_file(int infd, int outfd);
void	run_command_child(char *cmd, int *pfd, int infd, char **path);
void	rcc_exit(char **args, char **path);
void	get_file_fds(int *pfds, char *infile, char *outfile);
void	get_here_doc_fds(int *pfds, char *limiter, char *outfile);
void	get_here_doc(int *pipefd, char *limiter);
int		run_all_commands(int ac, char **av, int pfd, char **path);

#endif
