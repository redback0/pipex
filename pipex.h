/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:20:53 by njackson          #+#    #+#             */
/*   Updated: 2024/05/06 19:28:55 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft.h"

char	**get_path(char **ep);
int		run_command(char *cmd, int infd, char **path);
char	*find_command(char *cmd, char **path);
void	output_to_file(int infd, char *file);
int		run_command_child(char *cmd, int *pfd, int infd, char **path);
int		run_all_commands(int ac, char **av, int pfd, char **path);

#endif
