/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.o>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:37:27 by njackson          #+#    #+#             */
/*   Updated: 2024/05/02 15:57:32 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char *av[], char *ep[])
{
	int		pfd;
	int		npfd;
	int		status;
	char	**path;
	int		i;

	if (ac < 5)
		return (1); // ERROR
	path = get_path(ep);
	pfd = open(av[1], O_RDONLY);
	if (pfd < 0)
		return (1); // ERROR
	i = 2;
	while (i < ac - 1 && pfd >= 0)
	{
		npfd = run_command(av[i], pfd, path);
		close(pfd);
		pfd = npfd;
		i++;
		wait(&status);
	}
	if (pfd >= 0)
		output_to_file(pfd, av[i]);
}
/*
	while (ac-- > 1)
	{
		in_fd = run_command(av[ac], path);
		ft_putnbr_fd(1, in_fd);
		ft_putchar_fd(2, '\n');
		line = get_next_line(in_fd);
		while (line)
		{
			ft_log(0, line);
			free(line);
			line = get_next_line(in_fd);
		}
	}
*/

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

int	run_command(char *cmd, int infd, char **path)
{
	int		pipefd[2];
	char	**args;
	int		fd;
	int		signal;

	args = 0;
	pipe(pipefd);
	if (fork() == 0)
	{
		dup2(infd, 0);
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		close(pipefd[1]);
		args = ft_split(cmd, ' ');
		args[0] = find_command(args[0], path);
		execve(args[0], args, NULL);
		perror(args[0]);
		exit(1);
	}
	else
	{
		fd = dup(pipefd[0]);
		close(pipefd[1]);
		close(pipefd[0]);
		wait(&signal);
		if (signal == 0)
			return (fd);
		close(fd);
		return (-1);
	}
}

char	*find_command(char *cmd, char **path)
{
	char	*check;
	char	*tmp;
	int		i;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	tmp = ft_strjoin("/", cmd);
	i = 0;
	while (path[i])
	{
		check = ft_strjoin(path[i++], tmp);
		if (access(check, F_OK) == 0)
		{
			free(tmp);
			free(cmd);
			return (check);
		}
		free(check);
	}
	free(tmp);
	return (cmd);
}

void	output_to_file(int infd, char *file)
{
	char	*line;
	int		outfd;

	outfd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	line = get_next_line(infd);
	while (line)
	{
		write(outfd, line, ft_strlen(line));
		free(line);
		line = get_next_line(infd);
	}
}
