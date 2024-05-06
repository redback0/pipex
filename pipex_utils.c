/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:02:42 by njackson          #+#    #+#             */
/*   Updated: 2024/05/06 19:21:09 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	run_command_child(char *cmd, int *pfd, int infd, char **path)
{
	char	**args;

	dup2(infd, 0);
	close(infd);
	dup2(pfd[1], 1);
	close(pfd[0]);
	close(pfd[1]);
	args = ft_split(cmd, ' ');
	cmd = find_command(args[0], path);
	execve(cmd, args, NULL);
	perror(args[0]);
	exit(1);
}

char	**get_path(char **ep)
{
	char	**path;
	char	*tmp;
	int		i;

	i = -1;
	while (ep[++i])
	{
		if (ft_strncmp(ep[i], "PATH=", 5) == 0)
		{
			path = ft_split(ep[i], ':');
			tmp = ft_substr(path[0], 5, ft_strlen(path[0]) - 5);
			free(path[0]);
			path[0] = tmp;
			return (path);
		}
	}
	return (0);
}
