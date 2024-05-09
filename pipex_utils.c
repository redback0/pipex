/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:02:42 by njackson          #+#    #+#             */
/*   Updated: 2024/05/09 15:06:54 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_command_child(char *cmd, int *pfd, int infd, char **path)
{
	char	**args;

	dup2(infd, 0);
	close(infd);
	dup2(pfd[1], 1);
	close(pfd[0]);
	close(pfd[1]);
	args = ft_split(cmd, ' ');
	cmd = find_command(args[0], path);
	if (!cmd)
	{
		ft_printf_fd(2, "%s: command not found\n", args[0]);
		rcc_exit(args, path);
	}
	if (access(cmd, X_OK) != 0)
	{
		perror(args[0]);
		rcc_exit(args, path);
	}
	execve(cmd, args, NULL);
	ft_log(3, "execve failed\n");
	perror(args[0]);
	rcc_exit(args, path);
}

void	rcc_exit(char **args, char **path)
{
	ft_split_free(args, free);
	ft_split_free(path, free);
	exit(1);
}

void	get_file_fds(int *pfds, char *infile, char *outfile)
{
	pfds[0] = open(infile, O_RDONLY);
	if (pfds[0] < 0)
		perror(infile);
	pfds[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (pfds[1] < 0)
		perror(outfile);
}

void	get_here_doc_fds(int *pfds, char *limiter, char *outfile)
{
	int		pipefd[2];
	int		len;
	char	*line;

	pipe(pipefd);
	if (fork() == 0)
	{
		close(pipefd[0]);
		len = ft_strlen(limiter);
		line = get_next_line(0);
		while (line)
		{
			if (ft_strncmp(line, limiter, len) == 0 && line[len] == '\n')
			{
				free(line);
				exit(0);
			}
			ft_printf_fd(pipefd[1], line);
			free(line);
			line = get_next_line(0);
		}
		exit(1);
	}
	close(pipefd[1]);
	pfds[0] = pipefd[0];
	pfds[1] = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (pfds[1] < 0)
		perror(outfile);
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
